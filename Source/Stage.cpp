#include"Stage.h"

//�s��X�V
void Stage::UpdateTransform()
{
	//�X�P�[���s����쐬
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//��]�s����쐬
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//3�̍s���g�ݍ��킹�A���[���h�s����쐬
	DirectX::XMMATRIX W = S * R * T;

	//�v�Z�������[���h�s������o��
	DirectX::XMStoreFloat4x4(&transform, W);
}

//�R���X�g���N�^
Stage::Stage()
{
	//�X�e�[�W���f����ǂݍ���
	model = new Model("Data/Model/Stage/Stage2.mdl");
	//model = new Model("Data/Model/ExampleStage/ExampleStage.mdl");

	position.y = -2*3;
	position.z = 57.5;
	position.x = -0.8*3;
	angle.y = 1.5708;
	scale.x = scale.y = scale.z = 0.3;
}

//�f�X�g���N�^
Stage::~Stage()
{
	//�X�e�[�W���f����j��
	delete model;
}

//�X�V����
void Stage::Update(float elapsedTime)
{
	//���͓��ɂ�邱�Ƃ��Ȃ�
	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform(transform);
}

//�`�揈��
void Stage::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	//�V�F�[�_�[�Ƀ��f����`�悵�Ă��炤
	shader->Draw(dc, model);
}