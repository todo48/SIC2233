#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"ProjectileManager.h"
#include "Effect.h"

//�v���C���[
class Player : public Character
{
public:
	Player();
	~Player() override;

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�f�o�b�O�pGUI�`��
	void DrawDebugGUI();	

	////�ړ����͏���
	void InputMove(float elapsedTime);

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	////�e�ۓ��͏���
	//void InputProjectile();

	////�W�����v���͏���
	//void InputJump();

	//void CollisionProjectilesVsEnemies();

	void HitBack(const DirectX::XMFLOAT3& impulse);

protected:
	void OnLanding() override;


private:
	////�X�e�B�b�N���͒l����ړ��x�N�g�����擾
	//DirectX::XMFLOAT3 GetMoveVec()const;

	////�v���C���[�ƃG�l�~�[�̏Փˏ���
	//void CollisionPlayerVsEnemies();

	//ProjectileManager projectileManager;

private:
	Model* model = nullptr;
	Effect* hiteffect = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
	float jumpSpeed = 20.0f;
	int   jumpCount = 0;
	int   jumpLimit = 2;

	int SwingZone = 0;
	bool isSwing = false;
};