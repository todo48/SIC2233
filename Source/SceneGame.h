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


private:
	Stage* stage = nullptr;
	Player* player = nullptr;
	Pitcher* pitcher = nullptr;
	Ball* ball = nullptr;
	CameraController* cameraController = nullptr;
	

	Sprite* scenegame_ui = nullptr;
};
