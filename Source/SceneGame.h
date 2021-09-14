#pragma once

#include "Stage.h"
#include "player.h"
#include "Pitcher.h"
#include "Camera.h"
#include "Ball.h"
#include "CameraController.h"
#include "Scene.h"

#include "Graphics/Sprite.h"
#include"Audio/Audio.h"


// ゲームシーン
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// 初期化
	void Initialize() override;

	// 終了化
	void Finalize() override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

	std::unique_ptr<AudioSource> Game;
	std::unique_ptr<AudioSource> Swing;
	std::unique_ptr<AudioSource> Hit;
	std::unique_ptr<AudioSource> Ballcatch;

public:
	//DirectX11で利用する様々なリソースを作成するやつ
	Microsoft::WRL::ComPtr<ID3D11Device>device;
	//ID3D11DeviceContext* immediate_context;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context;
	std::unique_ptr<Sprite>sprites[8];
private:
	Stage* stage = nullptr;
	Player* player = nullptr;
	Pitcher* pitcher = nullptr;
	Ball* ball = nullptr;
	CameraController* cameraController = nullptr;
	

	Sprite* scenegame_s0_ui = nullptr;
	Sprite* scenegame_s1_ui = nullptr;
	Sprite* scenegame_s2_ui = nullptr;
};
