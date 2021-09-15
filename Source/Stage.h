#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"

//ステージ
class Stage
{
public:
	Stage();
	virtual ~Stage();

	//更新処理
	virtual void Update(float elapsedTime);

	//描画処理
	virtual void Render(ID3D11DeviceContext* dc, Shader* shader);

	// 位置取得
	const DirectX::XMFLOAT3& GetPosition() const { return position; }
	// 位置設定
	void setPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

protected:

	//行列更新処理
	void UpdateTransform();

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT3		scale = { 1,1,1 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,	//斜めに１のこの配列を単位行列という　すなわち１という
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

private:
	Model* model = nullptr;
};
