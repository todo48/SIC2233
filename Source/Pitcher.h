#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"BallManager.h"
#include "Effect.h"

//プレイヤー
class Pitcher : public Character
{
public:
	Pitcher();
	~Pitcher() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void DrawDebugPrimitive();
	
protected:
	void OnLanding() override;
	
private:
	Model* model = nullptr;
	Effect* hiteffect = nullptr;
}; 
