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


	BaseBall* baseball = new BaseBall(&ballManager);


	//Pitcher pitcher = Pitcher::Instance();
	
	

	if (isSwing == true && SwingZone == Pitcher::Instance().PitchZone )//&& baseball->GetPosition().z < 0);
	{
		//AddImpulse(impulse);
		baseball->Destroy();
		isSwing = false;
	}

	////移動入力処理
	InputMove(elapsedTime);

	////ジャンプ入力処理
	//InputJump();

	////弾丸入力処理
	//InputProjectile();

	//速度処理更新
	UpdateVelocity(elapsedTime);

	////弾丸更新処理
	//projectileManager.Update(elapsedTime);

	////プレイヤーと敵の衝突処理
	//CollisionPlayerVsEnemies();

	////弾丸と球の衝突処理
	//CollisionProjectilesVsEnemies();

	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform(transform);

}	

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);

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


	{
		BaseBall* baseball = new BaseBall(&ballManager);
		DirectX::XMFLOAT3 impulse;
		const float power = 10.0f;	//ここで固定になっているのは微妙						
		// 吹き飛ばし方向の計算
		const DirectX::XMFLOAT3& e = GetPosition();
		const DirectX::XMFLOAT3& p = baseball->GetPosition();
		float vx = e.x - p.x;
		float vz = e.z - p.z;
		// 単位ベクトル化
		float lengthXZ = sqrtf(vx * vx + vz * vz);
		vx /= lengthXZ;
		vz /= lengthXZ;
		// 力の設定
		impulse.x = vx * power;
		impulse.z = vz * power;
		impulse.y = power * 0.5f;	//上向きの力も追加
	}


	GamePad& gamePad = Input::Instance().GetGamePad();
	//for (int i = 0; i < 9; i++)
	//{
	//	if (gamePad.GetButtonDown() & (1<<i))//gamePad.BTN_Z)
	//	{
	//		isSwing = true;
	//		switch (i)
	//		{
	//		//Zキー
	//		case 0:
	//			SwingZone = 1;
	//			break;
	//		//Xキー
	//		case 2:
	//			SwingZone = 2;
	//			break;
	//		//Cキー
	//		case 3:
	//			SwingZone = 3;
	//			break;
	//		//BTN_LEFT(Aキー)
	//		case 4:
	//			SwingZone = 4;
	//			break;
	//		//BTN_DOWN(Sキー)
	//		case 5:
	//			SwingZone = 5;
	//			break;
	//		//BTN_RIGHT(Dキー)
	//		case 6:
	//			SwingZone = 6;
	//			break;
	//		//Qキー
	//		case 7:
	//			SwingZone = 7;
	//			break;
	//		//BTN_UP(Wキー)
	//		case 8:
	//			SwingZone = 8;
	//			break;
	//		//Eキー
	//		case 9:
	//			SwingZone = 9;
	//			break;
	//		}
	//	}
	//}


	{
		if (gamePad.GetButtonDown() & GamePad::BTN_Z)
		{
			isSwing = true;
			SwingZone = 1;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_X)
		{
			isSwing = true;
			SwingZone = 2;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_C)
		{
			isSwing = true;
			SwingZone = 3;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_A)
		{
			isSwing = true;
			SwingZone = 4;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_S)
		{
			isSwing = true;
			SwingZone = 5;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_D)
		{
			isSwing = true;
			SwingZone = 6;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_Q)
		{
			isSwing = true;
			SwingZone = 7;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_W)
		{
			isSwing = true;
			SwingZone = 8;
		}
		else if (gamePad.GetButtonDown() & GamePad::BTN_E)
		{
			isSwing = true;
			SwingZone = 9;
		}
	}
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

	////弾丸デバッグプリミティブ描画
	//projectileManager.DrawDebugPrimitive();
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

void Player::OnLanding()
{
	jumpCount = 0;
}

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
