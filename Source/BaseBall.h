#pragma once

#include"Graphics/Model.h"
#include"Ball.h"

//野球ボール
class BaseBall :public Ball
{
public:
	BaseBall(BallManager* manager);
	~BaseBall()override;

	//更新処理
	void Update(float elapsedTime)override;

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;

	//発射
	void Launch
	(
		const DirectX::XMFLOAT3& direction,
		const DirectX::XMFLOAT3& position,
		const DirectX::XMFLOAT3& target
	);

private:
	Model* model = nullptr;
	DirectX::XMFLOAT3 target = { 0,0,0 };
	float moveSpeed = 10.0f;
	float turnSpeed = DirectX::XMConvertToRadians(180);
	float lifeTimer = 3.0f;

};

