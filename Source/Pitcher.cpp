#include<imgui.h>
#include"Pitcher.h"
#include"Input/Input.h"
#include"Camera.h"
#include"Graphics/Graphics.h"
#include"Collision.h"
#include"BaseBall.h"
#include"player.h"


//�R���X�g���N�^
Pitcher::Pitcher()
{
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

	hiteffect = new Effect("Data/Effect/NewHit.efk");
	//���f�����傫���̂ŃX�P�[�����O
	scale.x = scale.y = scale.z = 0.02f;
	position = {0,0,50};
}

//�f�X�g���N�^
Pitcher::~Pitcher()
{
	delete model;
	delete hiteffect;
}

//�X�V����
void Pitcher::Update(float elapsedTime)
{
	//�{�[�����ˏ���
	if(LaunchReady == true)
	InputBall();

	//�{�[���̈ʒu������ʒu�ɒB������
	//BaseBall* baseball = new BaseBall(&ballManager);
	//if (baseball->GetPosition().z < -10 && baseball->GetPosition().z > 50)
	////���ˏ�����true
	//LaunchReady = true;

	if (LaunchReady == false)
	{
		Launch_Timer--;
		if (Launch_Timer < 0)
		{
			Launch_Timer = 600;
			LaunchReady = true;
		}
	}

	//���x�����X�V
	UpdateVelocity(elapsedTime);

	//�{�[���X�V����
	ballManager.Update(elapsedTime);
	
	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform(transform);

	
}

void Pitcher::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);

	//�{�[���`�揈��
	ballManager.Render(dc, shader);
}

void Pitcher::DrawDebugGUI()
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
			angle.y = DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);
			//�X�P�[��
			ImGui::InputFloat3("Scale", &scale.x);
		}
	}
	ImGui::End();
}

void Pitcher::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//�Փ˔���p�̃f�o�b�O����`��
	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	//�Փ˔���p�̃f�o�b�O�~����`��
	debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));

	//�{�[���f�o�b�O�v���~�e�B�u
	ballManager.DrawDebugPrimitive();
}

void Pitcher::OnLanding()
{
}

void Pitcher::InputBall()
{
	BaseBall* baseball = new BaseBall(&ballManager);
		//�O����
		DirectX::XMFLOAT3 dir;
		dir.x = -sinf(angle.y);
		dir.y = 0.0f;
		dir.z = -cosf(angle.y);

		//���ˈʒu
		DirectX::XMFLOAT3 pos;
		pos.x = position.x;
		pos.y = position.y + height * 0.5f;
		pos.z = position.z;

		//������ʒu(�f�t�H���g�ł́@S�@�̈ʒu)
		DirectX::XMFLOAT3 target;
		target.x = 0;
		target.y = 1.30;
		target.z = 0;

		//������ʒu�𒊑I
		//�X�g���C�N
		int a = 20;
		//�{�[����
		int b = 18;
		switch (a)
		{
		case 0:
			b = rand() % 17;
			break;
		case 1:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 2:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 3:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 4:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 5:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 6:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 7:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 8:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
			break;
		case 9:
			target.x = 0;
			target.y = 1.75;
			target.z = 0;
			PitchZone = 1;
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

		DirectX::XMVECTOR PitchPos = DirectX::XMLoadFloat3(&position);
		DirectX::XMVECTOR ZonePos = {0,0,0};
		DirectX::XMVECTOR V = DirectX::XMVectorSubtract(ZonePos, PitchPos);
		DirectX::XMVECTOR R = DirectX::XMVector3LengthSq(V);

		baseball->GetPosition();

		//����
		baseball->Launch(dir, pos, target);
		LaunchReady = false;
}
