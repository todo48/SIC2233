#pragma once

#include<DirectXMath.h>
#include"BallManager.h"

//�L�����N�^�[

class Character
{
public:
	Character(){}
	virtual ~Character() {}

	//�s��X�V����
	void UpdateTransform();

	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition()const { return position; }

	//�ʒu�ݒ�
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

	//��]�擾
	const DirectX::XMFLOAT3& GetAngle() const { return angle; }

	//��]�ݒ�
	void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }

	//�X�P�[���擾
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//�X�P�[���ݒ�
	void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }

	//���a�擾
	float GetRadius()const { return radius; }

	//�n�ʂɒ��n���Ă��邩
	bool IsGround() const { return isGround; }

	//�����擾 
	float GetHeight() const { return height; }

	//�_���[�W��^����
	bool ApplyDamage(int damage, float invincibleTime);

	// true...���G��
	//bool IsInvincible() { return invincibleTimer > 0.0f; }

	//�Ռ���^����
	void AddImpulse(const DirectX::XMFLOAT3& impulse);

	//���ˉ�
	bool LaunchReady = true;

private:
	//�������͍X�V����
	void UpdateVerticalVelocity(float elapsedFrame);

	//�����ړ��X�V���u
	void UpdateVerticalMove(float elapsedTime);

	//�������͍X�V����
	void UpdateHorizontalVelocity(float elapsedFrame);

	//�����ړ��X�V����
	void UpdateHorizontalMove(float elapsedTime);

protected:
	//�ړ�����
	void Move(float vx, float vz, float speed);

	//���񏈗�
	void Turn(float elapsedTime, float vx, float vz, float speed);

	//�W�����v����
	void Jump(float speed);

	//���x�����X�V
	void UpdateVelocity(float elapsedTime);

	//���G���ԍX�V
	void UpdateInvincibleTimer(float elapsedTime);

	//���n�������ɌĂ΂��
	virtual void OnLanding(){}

	//�_���[�W���󂯂����ɌĂ΂��
	virtual void OnDamage(){}

	//���S�������ɌĂ΂��
	virtual void OnDead(){}

	BallManager ballManager;

protected:
	DirectX::XMFLOAT3   position = { 0,0,0 };
	DirectX::XMFLOAT3   angle    = { 0,0,0 };
	DirectX::XMFLOAT3   scale    = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	float radius = 0.5f;
	float gravity = -1.0f;
	DirectX::XMFLOAT3 velocity = { 0,0,0 };
	bool isGround = false;
	float height = 2.0f;
	int health = 5;
	
	// ���݂̖��G����
	float invincibleTimer = 1.0f;
	// 

	float friction = 0.5f;
	float acceleration = 1.0f;
	float maxMoveSpeed = 5.0f;
	float moveVecX = 0.0f;
	float moveVecZ = 0.0f;
};