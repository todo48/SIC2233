#include<imgui.h>
#include"player.h"
#include"Input/Input.h"
#include"Camera.h"
#include"Graphics/Graphics.h"
#include"BallManager.h"
#include"Collision.h"
#include"ProjectileStraite.h"
#include"ProjectileHoming.h"
#include"Pitcher.h"
#include"BaseBall.h"
#include"ScoreManager.h"
int Player::ScoreCount = 0;


//コンストラクタ
Player::Player()
{
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

	hiteffect = new Effect("Data/Effect/NewHit.efk");
	//モデルが大きいのでスケーリング
	scale.x = scale.y = scale.z = 0.01f;
}

//デストラクタ
Player::~Player()
{
	delete model;
	delete hiteffect;
}

//更新処理
void Player::Update(float elapsedTime)
{
	////移動処理
	//float moveSpeed = this->moveSpeed * elapsedTime;
	//position.x += moveVec.x * moveSpeed;
	//position.z += moveVec.z * moveSpeed;
	////ジャンプ入力処理
	//InputJump();
	////弾丸入力処理
	//InputProjectile();
	////弾丸更新処理
	//projectileManager.Update(elapsedTime);
	////プレイヤーと敵の衝突処理
	//CollisionPlayerVsEnemies();
	////弾丸と球の衝突処理
	//CollisionProjectilesVsEnemies();

	SwingZone = 0;
	InputMove(elapsedTime);

	//ボール発射処理
	if(LaunchReady == true)
	InputBall();
	//発射準備
	if (LaunchReady == false)
	{
		Launch_Timer--;
		if (Launch_Timer < 0)
		{
			Launch_Timer = 300;
			LaunchReady = true;
		}
	}

	if (SwingTimer < 0.1)
	{
		isSwing = false;
	}


	if (isSwing == true)
	{
		SwingTimer = 120;
		SwingTimer--;
	}

	if (ballManager.GetBallCount() > 0)
	{
		BaseBall* baseball = dynamic_cast<BaseBall*>(ballManager.GetBall(0));
		if (baseball)
		{
			//ヒット
			if (isSwing == true && PitchZone && baseball->GetPosition().z > 0 && baseball->GetPosition().z < 3)
			{
				BaseBall* baseball_2 = new BaseBall(&ballManager);
				//前方向
				DirectX::XMFLOAT3 dir_2;
				dir_2.x = sinf(angle.y);
				dir_2.y = 0.0f;
				dir_2.z = cosf(angle.y);
				//発射位置
				DirectX::XMFLOAT3 pos_2;
				pos_2.x = 0;
				pos_2.y = 0.5;
				pos_2.z = 0;
				//投げる位置(デフォルトでは　S　の位置)
				DirectX::XMFLOAT3 target_2;
				target_2.x = 0;
				target_2.y = 10;
				target_2.z = 10;
				DirectX::XMVECTOR PitchPos_2 = { 0,1.5,50 };
				DirectX::XMVECTOR ZonePos_2 = { 0,0,0 };
				DirectX::XMVECTOR V_2 = DirectX::XMVectorSubtract(ZonePos_2, PitchPos_2);
				DirectX::XMVECTOR R_2 = DirectX::XMVector3LengthSq(V_2);
				ScoreCount++;
				baseball_2->Launch(dir_2, pos_2, target_2);
				LaunchReady_2 = false;
				ScoreManager::Instance().Score++;
			}

			//ストライク
			if (SwingZone != PitchZone && baseball->GetPosition().z < -10)
			{
				ScoreManager::Instance().Strike++;
			}
		}
	}


	//ボール更新処理
	ballManager.Update(elapsedTime);


	//速度処理更新
	UpdateVelocity(elapsedTime);

	//オブジェクト行列を更新
	UpdateTransform();
	
	//モデル行列更新
	model->UpdateTransform(transform);
	
	
	

}	

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);

	//ボール描画処理
	ballManager.Render(dc, shader);

	////弾丸描画処理
	//projectileManager.Render(dc, shader);
}

void Player::DrawDebugGUI()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//位置
			ImGui::InputFloat3("Position", &position.x);
			//回転
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			//ImGui::InputFloat3("Angle", &angle.x);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y= DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);
			//スケール
			ImGui::InputFloat3("Scale", &scale.x);
		}
	}
	ImGui::End();
}

void Player::InputMove(float elapsedTime)
{
	//進行ベクトル取得
	DirectX::XMFLOAT3 moveVec = GetMoveVec();
	//移動処理
	Move(moveVec.x, moveVec.z, moveSpeed);
	//旋回処理
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);

	GamePad& gamePad = Input::Instance().GetGamePad();
	{
		if (gamePad.GetButtonDown() & GamePad::BTN_Z)
		{
			if(SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 1;
			ScoreManager::Instance().Score++;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_X)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 2;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_C)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 3;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_A)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 4;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_S)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 5;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_D)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 6;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_Q)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 7;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_W)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 8;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_E)
		{
			if (SwingTimer < 0.1)
			isSwing = true;
			SwingZone = 9;
		}
	}
}

void Player::InputBall()
{
	BaseBall* baseball = new BaseBall(&ballManager);
	//前方向
	DirectX::XMFLOAT3 dir;
	dir.x = -sinf(angle.y);
	dir.y = 0.0f;
	dir.z = -cosf(angle.y);

	//発射位置
	DirectX::XMFLOAT3 pos;
	pos.x = 0;
	pos.y = 3.3;
	pos.z = 35;

	//投げる位置(デフォルトでは　S　の位置)
	DirectX::XMFLOAT3 target;
	target.x = 0;
	target.y = 3.8;
	target.z = 0;

	//投げる位置を抽選
	//ストライク
	//int a = rand() % 10;
	int a = 1;
	//ボール球
	int b = 18;
	switch (a)
	{
	case 0:
		b = rand() % 17;
		break;
	case 1:
		target.x = 0;
		target.y = 1.50;
		target.z = -20;
		PitchZone = 1;
		break;
	case 2:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 2;
		break;
	case 3:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 3;
		break;
	case 4:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 4;
		break;
	case 5:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 5;
		break;
	case 6:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 6;
		break;
	case 7:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 7;
		break;
	case 8:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 8;
		break;
	case 9:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 9;
		break;
	}

	switch (b)
	{
	case 0:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 1:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 2:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 3:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 4:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 5:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 6:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 7:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 8:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 9:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 10:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 11:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 12:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 13:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 14:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 15:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	case 16:
		target.x = 0;
		target.y = 1.75;
		target.z = 0;
		PitchZone = 0;
		break;
	}

	DirectX::XMVECTOR PitchPos = { 0,1.5,50 };
	DirectX::XMVECTOR ZonePos = { 0,0,0 };
	DirectX::XMVECTOR V = DirectX::XMVectorSubtract(ZonePos, PitchPos);
	DirectX::XMVECTOR R = DirectX::XMVector3LengthSq(V);

	//発射
	baseball->Launch(dir, pos, target);
	LaunchReady = false;
}

DirectX::XMFLOAT3 Player::GetMoveVec()const
{
	//入力情報を取得
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	//カメラ方向とスティックの入力値によって進行方向を計算する
	Camera& camera = Camera::instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	//移動ベクトルはXZ平面に水平なベクトルになるようにする

	//カメラ方向ベクトルをXZ単位ベクトルに変換
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	if (cameraRightLength > 0.0f)
	{
		//単位ベクトル化 
		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;
		cameraRightLength /= cameraRightLength;
	}

	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
	if (cameraFrontLength > 0.0f)
	{
		//単位ベクトル化
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
		cameraFrontLength /= cameraFrontLength;
	}
	
	//スティックの水平(左右)入力値をカメラ右方向に反映し、
	cameraRightX = cameraRightX * ax;
	cameraRightZ = cameraRightZ * ax;
	//スティックの垂直(上下)入力値にカメラ前方向に反映し、
	cameraFrontX = cameraFrontX * ay;
	cameraFrontZ = cameraFrontZ * ay;
	//進行ベクトルを計算する

	DirectX::XMFLOAT3 vec;
	vec.x = cameraFrontX + cameraRightX;
	vec.z = cameraFrontZ + cameraRightZ;
	//Y軸方向には移動しない
	vec.y = 0.0f;

	return vec;
}

//前後判定で使う内積　前後判定 = 内積ではない
//左右判定で使う外積　左右判定 = 外積ではない


void Player::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバッグ球を描画
	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	//衝突判定用のデバッグ円柱を描画
	debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));

	//ボールデバッグプリミティブ
	ballManager.DrawDebugPrimitive();
}

void Player::OnLanding()
{
	jumpCount = 0;
}

//プレイヤーとエネミーの衝突処理
//void Player::CollisionPlayerVsEnemies()
//{
//	BallManager& ballManager = BallManager::Instance();
//
//	//全ての敵と総当たりで衝突処理
//	//参照回数を減らすためにint型
//	int enemyCount =ballManager.GetBallCount();
//	for (int i = 0; i < enemyCount; ++i)
//	{
//		Ball* ball = ballManager.GetBall(i);
//
//		//衝突処理
//		DirectX::XMFLOAT3 outPosition;
//		//if (Collision::IntersectSphereVsSphere(
//		//	position,radius,
//		//	enemy->GetPosition(),enemy->GetRadius(),
//		//	outPosition
//		//))	
//		if (Collision::IntersectCylinderVsCylinder
//		(
//			position, radius, height,
//			ball->GetPosition(), ball->GetRadius(), ball->GetHeight(),
//			outPosition
//		))
//		{
//			//敵の真上付近に当たったかを判定
//			DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&position);
//			DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&ball->GetPosition());
//			DirectX::XMVECTOR V = DirectX::XMVectorSubtract(P, E);
//			DirectX::XMVECTOR N = DirectX::XMVector3Normalize(V);
//			DirectX::XMFLOAT3 normal;
//			DirectX::XMStoreFloat3(&normal, N);
//
//
//			//上から踏んづけた場合は小ジャンプする
//			if (normal.y > 0.8f)
//			{
//				//小ジャンプする
//				Jump(jumpSpeed * 0.5f);
//				ball->ApplyDamage(1, 0.0f);
//				//ヒットエフェクト再生
//				{
//					DirectX::XMFLOAT3 e = ball->GetPosition();
//					e.y += ball->GetHeight() * 0.5f;
//					hiteffect->Play(e);
//				}
//			}
//			else
//			{
//				//押し出し後の位置設定
//				ball->SetPosition(outPosition); //当たったらエネミーの座標を修正
//			}
//		}
//	}
//
//}
//慣性移動　物理　外部から力がかかっていなければ止まっていたらずっと動いていたらずっと
//物理エンジンとの違い　質量の違い　質量と力で全て求める　
//ジャンプ入力処理
//void Player::InputJump()
//{
//	//ボタン入力でジャンプ(ジャンプ回数制限付き)
//	GamePad& gamePad = Input::Instance().GetGamePad();
//	if (gamePad.GetButtonDown() & GamePad::BTN_A)
//	{
//		//Jump(jumpSpeed);
//		if (jumpCount < jumpLimit)
//		{
//			++jumpCount;
//			Jump(jumpSpeed);
//		}
//		
//	}
//}
//void Player::InputProjectile()
//{
//	GamePad& gamePad = Input::Instance().GetGamePad();
//
//	//直進弾丸発射
//	if (gamePad.GetButtonDown() & GamePad::BTN_X)
//	{
//		//前方向
//		DirectX::XMFLOAT3 dir;
//		dir.x = sinf(angle.y);
//		dir.y = 0.0f;
//		dir.z = cosf(angle.y);
//		//発射位置
//		DirectX::XMFLOAT3 pos;
//		pos.x = position.x;
//		pos.y = position.y + height * 0.5f;
//		pos.z = position.z;
//		//発射
//		ProjectileStraite* projectile = new ProjectileStraite(&projectileManager);
//		projectile->Launch(dir, pos);
//		//projectileManager.Register(projectile);
//	}
//
//	//追尾弾丸発射
//	if (gamePad.GetButtonDown() & GamePad::BTN_Y)
//	{
//		//前方向
//		DirectX::XMFLOAT3 dir;
//		dir.x = sinf(angle.y);
//		dir.y = 0.0f;
//		dir.z = cosf(angle.y);
//		//発射位置
//		DirectX::XMFLOAT3 pos;
//		pos.x = position.x;
//		pos.y = position.y + height * 0.5f;
//		pos.z = position.z;
//		//ターゲット(デフォルトではプレイヤーの前方)
//		DirectX::XMFLOAT3 target;
//		target.x = pos.x + dir.x * 1000.0f;
//		target.y = pos.y + dir.y * 1000.0f;
//		target.z = pos.z + dir.z * 1000.0f;
//
//		//1番近くの敵をターゲットにする
//		BallManager& ballManager = BallManager::Instance();
//		int enemyCount = ballManager.GetBallCount();
//		float nearest = FLT_MAX;
//		for (int i = 0; i < enemyCount; ++i)
//		{
//			Ball* ball = ballManager.GetBall(i);
//			DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&position);
//			DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&ball->GetPosition());
//			DirectX::XMVECTOR V = DirectX::XMVectorSubtract(E, P);
//			DirectX::XMVECTOR R = DirectX::XMVector3LengthSq(V);
//
//			float Range;
//			DirectX::XMStoreFloat(&Range, R);
//
//			if (Range < nearest)
//			{
//				nearest = Range;
//				target = ball->GetPosition();
//				target.y += ball->GetHeight() * 0.5f;
//			}
//
//		}
//		//発射
//		ProjectileHoming* projectile = new ProjectileHoming(&projectileManager);
//		projectile->Launch(dir, pos, target);
//	}
//}
//void Player::CollisionProjectilesVsEnemies()
//{
//	BallManager& ballManager = BallManager::Instance();
//
//	//全ての弾丸と全ての敵を総当たりで衝突処理
//	int projectileCount = projectileManager.GetProjectileCount();
//	int enemyCount = ballManager.GetBallCount();
//	for (int i = 0; i < projectileCount; ++i)
//	{
//		Projectile* projectile = projectileManager.GetProjectile(i);
//
//		for (int j = 0; j < enemyCount; ++j)
//		{
//			Ball* ball = ballManager.GetBall(j);
//
//			// 敵が今無敵かどうかチェック
//			/*if (enemy->IsInvincible())
//				continue;*/
//			
//
//			//衝突処理
//			DirectX::XMFLOAT3 outPosition;
//			if (Collision::IntersectSqhereVsCylinder(
//				projectile->GetPosition(),
//				projectile->GetRadius(),
//				ball->GetPosition(),
//				ball->GetRadius(),
//				ball->GetHeight(),
//				outPosition))
//			{
//				//ダメージを与える
//				if (ball->ApplyDamage(1, 0.8f))
//				{
//					//吹き飛ばす
//					DirectX::XMFLOAT3 impulse;
//					const float power = 10.0f;
//
//					//吹き飛ばし方向の計算
//					const DirectX::XMFLOAT3& e = ball->GetPosition();
//					const DirectX::XMFLOAT3& p = projectile->GetPosition();
//					float vx = e.x - p.x;
//					float vz = e.z - p.z;
//					//正規化
//					float lengthxz = sqrtf(vx*vx+vz*vz);
//					vx /= lengthxz;
//					vz /= lengthxz;
//
//
//					//力の設定
//					impulse.x = vx * power;
//					impulse.z = vz * power;
//					impulse.y = 0.5f * power;
//
//					ball->AddImpulse(impulse);
//				}
//
//				//ヒットエフェクト再生
//				{
//					DirectX::XMFLOAT3 e = ball->GetPosition();
//					e.y += ball->GetHeight() * 0.5f;
//					hiteffect->Play(e);
//				}
//
//				//弾丸破棄
//				projectile->Destroy();
//			}
//		}
//	}
//}
