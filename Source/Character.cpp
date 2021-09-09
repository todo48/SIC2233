#include"Character.h"

//�s��X�V����
void Character::UpdateTransform()
{
	//�X�P�[���s����쐬
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	//��]�s����쐬
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	//3�̍s���g�ݍ��킹�A���[���h�s������o��
	DirectX::XMMATRIX W = S * R * T;
	//�v�Z�������[���h�s������o��
	DirectX::XMStoreFloat4x4(&transform, W);
}
//�ړ�����
void Character::Move(float vx, float vz, float speed)
{
	//�ړ������x�N�g����ݒ�
	moveVecX = vx;
	moveVecZ = vz;

	//�ő呬�x�ݒ�
	maxMoveSpeed = speed;
}



//�O�㔻��Ŏg�����ρ@�O�㔻�� = ���ςł͂Ȃ�
//���E����Ŏg���O�ρ@���E���� = �O�ςł͂Ȃ�
//���񏈗�
void Character::Turn(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;

	//�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�͂Ȃ�
	float length = sqrtf(vx * vx + vz * vz);
	if (length < 0.001f)return;

	//�i�s�x�N�g����P�ʃx�N�g����
	vx /= length;
	vz /= length;
	//���g�̉�]�l����O���������߂�
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);

	//���E������s�����߂�2�̒P�ʃx�N�g���̊O�ς��v�Z����@vec1��vec2�̒��g�����ւ����瓚�����ς��
	//�O�ς̋��ߕ�
	//float cross = frontX * vz - frontZ * vx;

	//2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
	//���E������s�����Ƃɂ���č��E��]��I������
	//if (cross < 0.0f)
	//{
	//	angle.y += speed;
	//}
	//else
	//	angle.y -=  speed;
	//}

	//��]�p�����߂邽�߁A2�̒P�ʃx�N�g���̓��ς��v�Z���� �P�ʃx�N�g�������ăo�O��P�[�X������
	float dot = frontX * vx + frontZ * vz;
	//���ϒl��-1.0�`1.00�ŕ\������Ă���A2�̒P�ʃx�N�g���̊p�x��
	//�������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
	float rot = 1.0 - dot;
	if (rot < speed)speed = rot;
	//���E������s�����߂�2�̒P�ʃx�N�g���̊O�ς��v�Z���� �O�ς͂����܂łȂ�
	float cross = frontX * vz - frontZ * vx;
	//2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
	//���E������s�����Ƃɂ���č��E��]��I������
	if (cross < 0.0f)
	{
		angle.y += speed;
	}
	else
	{
		angle.y -= speed;
	}
}

//�W�����v����
void Character::Jump(float speed)
{
	//������̗͂�ݒ�
	velocity.y = speed;
}

//���x�����X�V
void Character::UpdateVelocity(float elapsedTime)
{
	//�o�߃t���[��
	float elapsedFrame = 60.0f * elapsedTime;
	
	//�������͍X�V����
	UpdateVerticalVelocity(elapsedFrame);

	//�������͍X�V����
	UpdateHorizontalVelocity(elapsedFrame);

	//�����ړ��X�V����
	UpdateVerticalMove(elapsedTime);

	//�����ړ��X�V����
	UpdateHorizontalMove(elapsedTime);
}

bool Character::ApplyDamage(int damage,float invincibleTime)
{
	//�_���[�W��0�̏ꍇ�͌��N��Ԃ�ύX����K�v���Ȃ�
	if (damage == 0)return false;

	//���S���Ă���ꍇ�͌��N��Ԃ�ύX���Ȃ�
	if (health < 1)return false;

	if (invincibleTimer > 0.0f) return false;

	invincibleTimer = invincibleTime;

	//�_���[�W����
	health -= damage;
	
	//���S�ʒm
	if (health < 1)
	{
		OnDead();
	}
	//�_���[�W�ʒm
	else {
		OnDamage();
	}

	//���N��Ԃ��ύX�����ꍇ��true��Ԃ�
	return true;
}

//���G���ԍX�V
void Character::UpdateInvincibleTimer(float elapsedTime)
{
	if (invincibleTimer > 0.0f)
	{
		invincibleTimer -= elapsedTime;
	}
}

//�Ռ���^����
void Character::AddImpulse(const DirectX::XMFLOAT3& impulse)
{

	//���͂ɗ͂�������
	velocity.x += impulse.x;
	velocity.y += impulse.y;
	velocity.z += impulse.z;
}


//�������͍X�V����
void Character::UpdateVerticalVelocity(float elapsedFrame)
{
	//�d�͏���
	velocity.y += gravity * elapsedFrame;
}

//�������͍X�V����
void Character::UpdateVerticalMove(float elapsedTime)
{
	//�ړ�����
	position.y += velocity.y * elapsedTime;

	//�n�ʔ���
	if (position.y < 0.0f)
	{
		position.y = 0.0f;
		velocity.y = 0.0f;
	//���n����
		if (!isGround)OnLanding(); 
		isGround = true;
	}
	else 
	{
		isGround = false;
	}
}

//�������͍X�V����
void Character::UpdateHorizontalVelocity(float elapsedFrame)
{
	//XZ���ʂ̑��͂���������
	float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
	if (length > 0.0f)
	{
		//���C��
		float friction = this->friction * elapsedFrame;

		//�󒆂ɂ���Ƃ��͖��C�͂����炷
		if (!IsGround())
		{
			friction *= 0.5;
		}

		//���C�ɂ�鉡�����̌�������
		if (length > friction)
		{
			//���K��
			float vx = velocity.x / length;
			float vz = velocity.z / length;

			//����
			velocity.x = velocity.x - vx * friction;
			velocity.z = velocity.z - vz * friction;
		}
		//�������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���
		else
		{
			velocity.x = 0.0f;
			velocity.z = 0.0f;
		}
	}

	//XZ���ʂ̑��͂���������
	if (length <= maxMoveSpeed)
	{
		//�ړ��x�N�g�����[���x�N�g���łȂ��Ȃ��������
		float moveVecLength = sqrtf(moveVecX*moveVecX + moveVecZ*moveVecZ);
		if (moveVecLength > 0.0f)
		{
			//������
			float acceleration = this->acceleration * elapsedFrame;

			//�󒆂ɂ���Ƃ��͉����͂����炷
			if (!IsGround())
			{
				acceleration *= 0.5;
			}

			//�ړ��x�N�g���ɂ���������
			velocity.x += acceleration * moveVecX;
			velocity.z += acceleration * moveVecZ;
			//�ő呬�x����
			float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
			if (length > maxMoveSpeed)
			{
				//xz�����Ő��K��
				float vx = velocity.x / length;
				float vz = velocity.z / length;

				//����
				velocity.x = vx * maxMoveSpeed;
				velocity.z = vz * maxMoveSpeed;
			}
		}
	}
	//�ړ��x�N�g�������Z�b�g
	moveVecX = 0;
	moveVecZ = 0;
}

//�����ړ��X�V����
void  Character::UpdateHorizontalMove(float elapsedTime)
{
	//�ړ�����
	position.x += velocity.x * elapsedTime;
	position.z += velocity.z * elapsedTime;
}