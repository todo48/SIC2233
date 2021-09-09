#include"BaseBall.h"

//�R���X�g���N�^
BaseBall::BaseBall(BallManager* manager):Ball(manager)
{

}

//�f�X�g���N�^
BaseBall::~BaseBall()
{
	delete model;
}

//�X�V����
void BaseBall::Update(float elapsedTime)
{
	//��������
	lifeTimer -= elapsedTime;
	if (lifeTimer <= 0)
	{
		//�������폜
		Destroy();
	}

	//�ړ�
	{
		float moveSpeed = this->moveSpeed * elapsedTime;

		position.x += direction.x * moveSpeed;
		//position.y += direction.y * moveSpeed;
		position.z += direction.z * moveSpeed;
	}
	//����
	{
		float turnSpeed = this->turnSpeed * elapsedTime;

		//�^�[�Q�b�g�܂ł̃x�N�g�����Z�o
		DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&position);
		DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&target);
		DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Target, Position);

		//�[���x�N�g���łȂ��Ȃ��]����
		DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
		float lengthSq;
		DirectX::XMStoreFloat(&lengthSq, LengthSq);
		if (lengthSq > 0.00001f)
		{
			//�^�[�Q�b�g�܂ł̃x�N�g����P�ʃx�N�g����
			Vec = DirectX::XMVector3Normalize(Vec);

			//�����Ă�������x�N�g����ϊ�
			DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);

			//�O�����x�N�g���ƃ^�[�Q�b�g�܂ł̃x�N�g���̓���(�p�x)���Z�o
			DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Direction, Vec);
			float dot;
			DirectX::XMStoreFloat(&dot, Dot);

			//2�̒P�ʃx�N�g���̊p�x���������ق�
			//1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
			float rot = 1.0 - dot;
			if (rot > turnSpeed)
			{
				rot = turnSpeed;	//1�t���[���ł̉�肷����}��
			}

			//��]�p�x������Ȃ��]����������
			if (fabsf(rot) > 0.0001f)
			{
				//��]�����Z�o
				DirectX::XMVECTOR Axis = DirectX::XMVector3Cross(Direction, Vec);


				//��]���Ɖ�]�ʂ����]�s����Z�o
				DirectX::XMMATRIX Rotation = DirectX::XMMatrixRotationAxis(Axis, rot);

				//���݂̍s�����]������
				DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);
				Transform = DirectX::XMMatrixMultiply(Transform, Rotation);

				//��]��̑O�����������o���A�P�ʃx�N�g��������
				Direction = DirectX::XMVector3Normalize(Transform.r[2]);
				DirectX::XMStoreFloat3(&direction, Direction);
			}
		}

	}

	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform(transform);
}

//�`�揈��
void BaseBall::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}

void BaseBall::Launch(
	const DirectX::XMFLOAT3& direction,
	const DirectX::XMFLOAT3& position,
	const DirectX::XMFLOAT3& target)
{
	this->direction = direction;
	this->position = position;
	this->target = target;

	UpdateTransform();
}
