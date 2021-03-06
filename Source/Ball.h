#pragma once

#include"Graphics/Shader.h"
class BallManager;

//ボール
class Ball
{
public:
	Ball(BallManager* manager);
	virtual ~Ball() {}

	//更新処理
	virtual void Update(float elapsedTime) = 0;

	//描画処理
	virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

	//デバッグプリミティブ描画
	virtual void DrawDebugPrimitive();

	//位置取得
	const DirectX::XMFLOAT3& GetPosition()const { return position; }

	//方向取得
	const DirectX::XMFLOAT3& GetDirection() const { return direction; }

	//スケール取得
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//半径取得
	float GetRadius()const { return radius; }

	//破棄
	void Destroy();

protected:
	void UpdateTransform();

protected:
	DirectX::XMFLOAT3   position = { 0,0,0 };
	DirectX::XMFLOAT3   direction = { 0,0,1 };
	DirectX::XMFLOAT3   scale = { 1,1,1 };
	DirectX::XMFLOAT3	angle = { 0,0,0 };
	DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	BallManager* manager = nullptr;
	float radius = 0.5f;
};