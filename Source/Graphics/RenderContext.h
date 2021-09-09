#pragma once

#include <DirectXMath.h>

// レンダーコンテキスト
struct RenderContext
{
	//視野変換
	DirectX::XMFLOAT4X4		view;
	//投影変換
	DirectX::XMFLOAT4X4		projection;
	//方向のあるライト　
	DirectX::XMFLOAT4		lightDirection;
};
