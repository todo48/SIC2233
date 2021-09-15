#include"Ball.h"
#include"Graphics/Graphics.h"
#include"BallManager.h"



//�R���X�g���N�^
Ball::Ball(BallManager* manager) :manager(manager)
{
	manager->Register(this);
}

//�f�o�b�O�v���~�e�B�u�`��
void Ball::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	//�Փ˔���p�̃f�o�b�O�~����`��
	debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}

void Ball::UpdateTransform()
{
	DirectX::XMVECTOR Front, Up, Right;
	//�O�x�N�g�����Z�o z
	Front = DirectX::XMLoadFloat3(&direction);
	Front = DirectX::XMVector3Normalize(Front);

	//���̏�x�N�g�����Z�o  y
	Up = DirectX::XMVectorSet(0.001f, 1, 0, 0);
	//�u�����x�N�g���ŊO�ς���ƃ[���x�N�g���ɂȂ�v ���ۂ�h������0.001f
	Up = DirectX::XMVector3Normalize(Up);
	//�E�x�N�g�����Z�o x
	Right = DirectX::XMVector3Cross(Up, Front);
	Right = DirectX::XMVector3Normalize(Right);
	//��x�N�g�����Z�o y
	Up = DirectX::XMVector3Cross(Front, Right);
	DirectX::XMFLOAT3 right, up, front;
	DirectX::XMStoreFloat3(&right, Right);
	DirectX::XMStoreFloat3(&up, Up);
	DirectX::XMStoreFloat3(&front, Front);
	//�Ƃ肠�����A���ŉ�]�͖��������s����쐬����
	transform._11 = right.x * scale.x;
	transform._12 = right.y * scale.x;
	transform._13 = right.z * scale.x;
	transform._14 = 0.0f;
	transform._21 = up.x * scale.y;
	transform._22 = up.y * scale.y;
	transform._23 = up.z * scale.y;
	transform._24 = 0.0f;
	transform._31 = front.x * scale.z;
	transform._32 = front.y * scale.z;
	transform._33 = front.z * scale.z;
	transform._34 = 0.0f;
	transform._41 = position.x;
	transform._42 = position.y;
	transform._43 = position.z;
	transform._44 = 1.0f;

	DirectX::XMMATRIX ST = DirectX::XMLoadFloat4x4(&transform);

	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	DirectX::XMMATRIX W = R * ST;

	DirectX::XMStoreFloat4x4(&transform, W);

	////�X�P�[���s����쐬
	//DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	////��]�s����쐬
	//DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
	////�ʒu�s����쐬
	//DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	////3�̍s���g�ݍ��킹�A���[���h�s������o��
	//DirectX::XMMATRIX W = S * R * T;
	////�v�Z�������[���h�s������o��
	//DirectX::XMStoreFloat4x4(&transform, W);

	//���˕���
	this->direction = front;
}


//�j��
void Ball::Destroy()
{
	manager->Remove(this);
}