#pragma once

#include <DirectXMath.h>

// �����_�[�R���e�L�X�g
struct RenderContext
{
	//����ϊ�
	DirectX::XMFLOAT4X4		view;
	//���e�ϊ�
	DirectX::XMFLOAT4X4		projection;
	//�����̂��郉�C�g�@
	DirectX::XMFLOAT4		lightDirection;
};
