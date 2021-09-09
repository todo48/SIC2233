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
	InputBall();

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
	if (LaunchReady == true)
	{	
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
		target.y = 20;
		target.z = 0;

		//������ʒu�𒊑I


		DirectX::XMVECTOR PitchPos = DirectX::XMLoadFloat3(&position);
		DirectX::XMVECTOR ZonePos = {0,0,0};
		DirectX::XMVECTOR V = DirectX::XMVectorSubtract(ZonePos, PitchPos);
		DirectX::XMVECTOR R = DirectX::XMVector3LengthSq(V);

		//����
		BaseBall* ball = new BaseBall(&ballManager);
		ball->Launch(dir, pos, target);

		LaunchReady = false;
	}
}
