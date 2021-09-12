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

	static Pitcher& Instance()
	{
		static Pitcher instance;
		return instance;
	}

	

	static int PitchZone;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void DrawDebugPrimitive();

	//ボール発射処理
	void InputBall();

	
protected:
	void OnLanding() override;
	
private:
	Model* model = nullptr;
	Effect* hiteffect = nullptr;
	float Launch_Timer = 300;

}; 
