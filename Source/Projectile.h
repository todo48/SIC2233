#pragma once

#include"Graphics/Shader.h"
class ProjectileManager;

//�e��
class Projectile
{
public:
	Projectile(ProjectileManager* manager);
	virtual ~Projectile(){}

	//�X�V����
	virtual void Update(float elapsedTime) = 0;

	//�`�揈��
	virtual void Render(ID3D11DeviceContext* dc, Shader* sheder) = 0;

	//�f�o�b�O�v���~�e�B�u�`��
	virtual void DrawDebugPrimitive();

	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition()const { return position; }

	//�����擾
	const DirectX::XMFLOAT3& GetDirection() const { return direction; }

	//�X�P�[���擾
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//���a�擾
	float GetRadius()const { return radius; }

	//�j��
	void Destroy();

protected:
	void UpdateTransform();
protected:
	DirectX::XMFLOAT3   position = { 0,0,0 };
	DirectX::XMFLOAT3   direction = { 0,0,1 };
	DirectX::XMFLOAT3   scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	ProjectileManager* manager = nullptr;
	float radius = 0.5f;
};

