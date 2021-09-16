#include<imgui.h>
#include <stdio.h>
#include <time.h>
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


//�R���X�g���N�^
Player::Player()
{
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

	hiteffect = new Effect("Data/Effect/NewHit.efk");
	//���f�����傫���̂ŃX�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;
	InputTimer = 60;
}

//�f�X�g���N�^
Player::~Player()
{
	delete model;
	delete hiteffect;
}

//�X�V����
void Player::Update(float elapsedTime)
{
	////�ړ�����
	//float moveSpeed = this->moveSpeed * elapsedTime;
	//position.x += moveVec.x * moveSpeed;
	//position.z += moveVec.z * moveSpeed;
	////�W�����v���͏���
	//InputJump();
	////�e�ۓ��͏���
	//InputProjectile();
	////�e�ۍX�V����
	//projectileManager.Update(elapsedTime);
	////�v���C���[�ƓG�̏Փˏ���
	//CollisionPlayerVsEnemies();
	////�e�ۂƋ��̏Փˏ���
	//CollisionProjectilesVsEnemies();


	SwingZone = 0;

	InputMove(elapsedTime);

	//�{�[�����ˏ���
	if (LaunchReady == true)
		InputBall();

	//���ˏ���
	if(Launch_Timer > 0)
	{
		Launch_Timer--;
		if (Launch_Timer == 0)
		{
			LaunchReady = true;
		}
	}

	if (PushButton == true)
	{
		InputTimer--;
		if (InputTimer == 0)
		{
			PushButton = false;
			InputTimer += 60;
		}
	}


	//if (IsSwing == true)
	//{
	//	SwingTimer = 120;
	//	SwingTimer--;
	//}

	//if (SwingTimer < 0.1)
	//{
	//	IsSwing = false;
	//}


	if (ballManager.GetBallCount() > 0)
	{
		BaseBall* baseball = dynamic_cast<BaseBall*>(ballManager.GetBall(0));
		if (baseball)
		{
			//�q�b�g
			if (SwingZone == PitchZone && baseball->GetPosition().z > position.z + 2 && baseball->GetPosition().z < position.z + 7)
			{
				BaseBall* baseball_2 = new BaseBall(&ballManager);
				HitPosition = baseball->GetPosition();
				baseball->Destroy();

				//�O����
				DirectX::XMFLOAT3 dir_2;
				dir_2.x = sinf(angle.y);
				dir_2.y = 0.0f;
				dir_2.z = cosf(angle.y);
				//���ˈʒu
				DirectX::XMFLOAT3 pos_2;
				pos_2 = HitPosition;
				//������ʒu(�f�t�H���g�ł́@S�@�̈ʒu)
				DirectX::XMFLOAT3 target_2;
				target_2.x = 0;
				target_2.y = 20;
				target_2.z = 50;

				baseball_2->Launch2(dir_2, pos_2, target_2,speed2);
				ScoreManager::Instance().Score++;

				speed2++;
				Launch_Timer += 180;
			}

			//�X�g���C�N
			if (SwingZone != PitchZone && baseball->GetPosition().z < -10 && PitchZone != 0)
			{
				ScoreManager::Instance().Strike++;
				Launch_Timer += 180;
			}
		}
	}

	//�{�[���X�V����
	ballManager.Update(elapsedTime);


	//���x�����X�V
	UpdateVelocity(elapsedTime);

	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform(transform);
}

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);

	//�{�[���`�揈��
	ballManager.Render(dc, shader);

	////�e�ە`�揈��
	//projectileManager.Render(dc, shader);
}

void Player::DrawDebugGUI()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
	{
		//�g�����X�t�H�[��
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//�ʒu
			ImGui::InputFloat3("Position", &position.x);
			//��]
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			//ImGui::InputFloat3("Angle", &angle.x);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y= DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);
			//�X�P�[��
			ImGui::InputFloat3("Scale", &scale.x);
			ImGui::InputInt("Swing", &SwingZone);
			ImGui::InputInt("Pitch", &PitchZone);

			ImGui::InputFloat("PitchTimer", &Launch_Timer);
			ImGui::InputFloat("InputTimer", &InputTimer);
		}
	}
	ImGui::End();
}

void Player::InputMove(float elapsedTime)
{
	//�i�s�x�N�g���擾
	DirectX::XMFLOAT3 moveVec = GetMoveVec();
	//�ړ�����
	//Move(moveVec.x, moveVec.z, moveSpeed);
	//���񏈗�
	//Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);

	GamePad& gamePad = Input::Instance().GetGamePad();
	{
		if (/*InputTimer == 0 || */InputTimer == 60)
		{
			if (gamePad.GetButtonDown() & GamePad::BTN_Z)
			{
				SwingZone = 1;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_X)
			{
				SwingZone = 2;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_C)
			{
				SwingZone = 3;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
			{
				SwingZone = 4;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_S)
			{
				SwingZone = 5;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_D)
			{
				SwingZone = 6;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_Q)
			{
				SwingZone = 7;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_W)
			{
				SwingZone = 8;
				PushButton = true;
			}
			if (gamePad.GetButtonDown() & GamePad::BTN_E)
			{
				SwingZone = 9;
				PushButton = true;
			}
		}
	}
}

void Player::InputBall()
{
	BaseBall* baseball = new BaseBall(&ballManager);
	//�O����
	DirectX::XMFLOAT3 dir;
	dir.x = -sinf(angle.y);
	dir.y = 0.0f;
	dir.z = -cosf(angle.y);

	//���ˈʒu
	DirectX::XMFLOAT3 pos;
	pos.x = 0;
	pos.y = 3.3;
	pos.z = 35;

	//������ʒu(�f�t�H���g�ł́@S�@�̈ʒu)
	DirectX::XMFLOAT3 target;
	target.x = 0;
	target.y = 0;
	target.z = 0;

	//������ʒu�𒊑I
	//�X�g���C�N
	srand((unsigned int)time(NULL));
	int a = rand() % 10;
	//�{�[����
	srand((unsigned int)time(NULL));
	int b = rand() % 7;
	switch (a)
	{
	case 0:
		switch (b)
		{
		case 0:
			target.x = -4.8;
			target.y = 0.15;
			target.z = -20;
			break;
		case 1:
			target.x = 4.8;
			target.y = 0.15;
			target.z = -20;
			break;
		case 2:
			target.x = -4.8;
			target.y = 1.85;
			target.z = -20;
			break;
		case 3:
			target.x = 4.8;
			target.y = 1.85;
			target.z = -20;
			break;
		case 4:
			target.x = -4.8;
			target.y = 2.55;
			target.z = -20;
			break;
		case 5:
			target.x = 4.8;
			target.y = 2.55;
			target.z = -20;
			break;
		case 6:
			target.x = 0;
			target.y = 6.55;
			target.z = -20;
			break;
		}
	case 1:
		target.x = -0.8;
		target.y = 1.15;
		target.z = -20;
		PitchZone = 1;
		break;
	case 2:
		target.x = 0;
		target.y = 1.15;
		target.z = -20;
		PitchZone = 2;
		break;
	case 3:
		target.x = 0.8;
		target.y = 1.15;
		target.z = -20;
		PitchZone = 3;
		break;
	case 4:
		target.x = -0.8;
		target.y = 1.85;
		target.z = -20;
		PitchZone = 4;
		break;
	case 5:
		target.x = 0;
		target.y = 1.85;
		target.z = -20;
		PitchZone = 5;
		break;
	case 6:
		target.x = 0.8;
		target.y = 1.85;
		target.z = -20;
		PitchZone = 6;
		break;
	case 7:
		target.x = -0.8;
		target.y = 2.55;
		target.z = -20;
		PitchZone = 7;
		break;
	case 8:
		target.x = 0;
		target.y = 2.55;
		target.z = -20;
		PitchZone = 8;
		break;
	case 9:
		target.x = 0.8;
		target.y = 2.55;
		target.z = -20;
		PitchZone = 9;
		break;
	}


	DirectX::XMVECTOR PitchPos = { 0,1.5,50 };
	DirectX::XMVECTOR ZonePos = { 0,0,0 };
	DirectX::XMVECTOR V = DirectX::XMVectorSubtract(ZonePos, PitchPos);
	DirectX::XMVECTOR R = DirectX::XMVector3LengthSq(V);

	//����
	baseball->Launch(dir, pos, target,speed);
	LaunchReady = false;
	speed++;
}

DirectX::XMFLOAT3 Player::GetMoveVec()const
{
	//���͏����擾
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	//�J���������ƃX�e�B�b�N�̓��͒l�ɂ���Đi�s�������v�Z����
	Camera& camera = Camera::instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	//�ړ��x�N�g����XZ���ʂɐ����ȃx�N�g���ɂȂ�悤�ɂ���

	//�J���������x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	if (cameraRightLength > 0.0f)
	{
		//�P�ʃx�N�g���� 
		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;
		cameraRightLength /= cameraRightLength;
	}

	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
	if (cameraFrontLength > 0.0f)
	{
		//�P�ʃx�N�g����
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
		cameraFrontLength /= cameraFrontLength;
	}
	
	//�X�e�B�b�N�̐���(���E)���͒l���J�����E�����ɔ��f���A
	cameraRightX = cameraRightX * ax;
	cameraRightZ = cameraRightZ * ax;
	//�X�e�B�b�N�̐���(�㉺)���͒l�ɃJ�����O�����ɔ��f���A
	cameraFrontX = cameraFrontX * ay;
	cameraFrontZ = cameraFrontZ * ay;
	//�i�s�x�N�g�����v�Z����

	DirectX::XMFLOAT3 vec;
	vec.x = cameraFrontX + cameraRightX;
	vec.z = cameraFrontZ + cameraRightZ;
	//Y�������ɂ͈ړ����Ȃ�
	vec.y = 0.0f;

	return vec;
}

//�O�㔻��Ŏg�����ρ@�O�㔻�� = ���ςł͂Ȃ�
//���E����Ŏg���O�ρ@���E���� = �O�ςł͂Ȃ�


void Player::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//�Փ˔���p�̃f�o�b�O����`��
	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	//�Փ˔���p�̃f�o�b�O�~����`��
	debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));

	//�{�[���f�o�b�O�v���~�e�B�u
	ballManager.DrawDebugPrimitive();
}

void Player::OnLanding()
{
	jumpCount = 0;
}

//�v���C���[�ƃG�l�~�[�̏Փˏ���
//void Player::CollisionPlayerVsEnemies()
//{
//	BallManager& ballManager = BallManager::Instance();
//
//	//�S�Ă̓G�Ƒ�������ŏՓˏ���
//	//�Q�Ɖ񐔂����炷���߂�int�^
//	int enemyCount =ballManager.GetBallCount();
//	for (int i = 0; i < enemyCount; ++i)
//	{
//		Ball* ball = ballManager.GetBall(i);
//
//		//�Փˏ���
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
//			//�G�̐^��t�߂ɓ����������𔻒�
//			DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&position);
//			DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&ball->GetPosition());
//			DirectX::XMVECTOR V = DirectX::XMVectorSubtract(P, E);
//			DirectX::XMVECTOR N = DirectX::XMVector3Normalize(V);
//			DirectX::XMFLOAT3 normal;
//			DirectX::XMStoreFloat3(&normal, N);
//
//
//			//�ォ�瓥��Â����ꍇ�͏��W�����v����
//			if (normal.y > 0.8f)
//			{
//				//���W�����v����
//				Jump(jumpSpeed * 0.5f);
//				ball->ApplyDamage(1, 0.0f);
//				//�q�b�g�G�t�F�N�g�Đ�
//				{
//					DirectX::XMFLOAT3 e = ball->GetPosition();
//					e.y += ball->GetHeight() * 0.5f;
//					hiteffect->Play(e);
//				}
//			}
//			else
//			{
//				//�����o����̈ʒu�ݒ�
//				ball->SetPosition(outPosition); //����������G�l�~�[�̍��W���C��
//			}
//		}
//	}
//
//}
//�����ړ��@�����@�O������͂��������Ă��Ȃ���Ύ~�܂��Ă����炸���Ɠ����Ă����炸����
//�����G���W���Ƃ̈Ⴂ�@���ʂ̈Ⴂ�@���ʂƗ͂őS�ċ��߂�@
//�W�����v���͏���
//void Player::InputJump()
//{
//	//�{�^�����͂ŃW�����v(�W�����v�񐔐����t��)
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
//	//���i�e�۔���
//	if (gamePad.GetButtonDown() & GamePad::BTN_X)
//	{
//		//�O����
//		DirectX::XMFLOAT3 dir;
//		dir.x = sinf(angle.y);
//		dir.y = 0.0f;
//		dir.z = cosf(angle.y);
//		//���ˈʒu
//		DirectX::XMFLOAT3 pos;
//		pos.x = position.x;
//		pos.y = position.y + height * 0.5f;
//		pos.z = position.z;
//		//����
//		ProjectileStraite* projectile = new ProjectileStraite(&projectileManager);
//		projectile->Launch(dir, pos);
//		//projectileManager.Register(projectile);
//	}
//
//	//�ǔ��e�۔���
//	if (gamePad.GetButtonDown() & GamePad::BTN_Y)
//	{
//		//�O����
//		DirectX::XMFLOAT3 dir;
//		dir.x = sinf(angle.y);
//		dir.y = 0.0f;
//		dir.z = cosf(angle.y);
//		//���ˈʒu
//		DirectX::XMFLOAT3 pos;
//		pos.x = position.x;
//		pos.y = position.y + height * 0.5f;
//		pos.z = position.z;
//		//�^�[�Q�b�g(�f�t�H���g�ł̓v���C���[�̑O��)
//		DirectX::XMFLOAT3 target;
//		target.x = pos.x + dir.x * 1000.0f;
//		target.y = pos.y + dir.y * 1000.0f;
//		target.z = pos.z + dir.z * 1000.0f;
//
//		//1�ԋ߂��̓G���^�[�Q�b�g�ɂ���
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
//		//����
//		ProjectileHoming* projectile = new ProjectileHoming(&projectileManager);
//		projectile->Launch(dir, pos, target);
//	}
//}
//void Player::CollisionProjectilesVsEnemies()
//{
//	BallManager& ballManager = BallManager::Instance();
//
//	//�S�Ă̒e�ۂƑS�Ă̓G�𑍓�����ŏՓˏ���
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
//			// �G�������G���ǂ����`�F�b�N
//			/*if (enemy->IsInvincible())
//				continue;*/
//			
//
//			//�Փˏ���
//			DirectX::XMFLOAT3 outPosition;
//			if (Collision::IntersectSqhereVsCylinder(
//				projectile->GetPosition(),
//				projectile->GetRadius(),
//				ball->GetPosition(),
//				ball->GetRadius(),
//				ball->GetHeight(),
//				outPosition))
//			{
//				//�_���[�W��^����
//				if (ball->ApplyDamage(1, 0.8f))
//				{
//					//������΂�
//					DirectX::XMFLOAT3 impulse;
//					const float power = 10.0f;
//
//					//������΂������̌v�Z
//					const DirectX::XMFLOAT3& e = ball->GetPosition();
//					const DirectX::XMFLOAT3& p = projectile->GetPosition();
//					float vx = e.x - p.x;
//					float vz = e.z - p.z;
//					//���K��
//					float lengthxz = sqrtf(vx*vx+vz*vz);
//					vx /= lengthxz;
//					vz /= lengthxz;
//
//
//					//�͂̐ݒ�
//					impulse.x = vx * power;
//					impulse.z = vz * power;
//					impulse.y = 0.5f * power;
//
//					ball->AddImpulse(impulse);
//				}
//
//				//�q�b�g�G�t�F�N�g�Đ�
//				{
//					DirectX::XMFLOAT3 e = ball->GetPosition();
//					e.y += ball->GetHeight() * 0.5f;
//					hiteffect->Play(e);
//				}
//
//				//�e�۔j��
//				projectile->Destroy();
//			}
//		}
//	}
//}
