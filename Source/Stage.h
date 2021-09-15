#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"

//�X�e�[�W
class Stage
{
public:
	Stage();
	virtual ~Stage();

	//�X�V����
	virtual void Update(float elapsedTime);

	//�`�揈��
	virtual void Render(ID3D11DeviceContext* dc, Shader* shader);

	// �ʒu�擾
	const DirectX::XMFLOAT3& GetPosition() const { return position; }
	// �ʒu�ݒ�
	void setPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

protected:

	//�s��X�V����
	void UpdateTransform();

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT3		scale = { 1,1,1 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,	//�΂߂ɂP�̂��̔z���P�ʍs��Ƃ����@���Ȃ킿�P�Ƃ���
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

private:
	Model* model = nullptr;
};
