#pragma once

#include "Stage.h"
#include "player.h"
#include "Pitcher.h"
#include "Camera.h"
#include "Ball.h"
#include "CameraController.h"
#include "Scene.h"

#include "Graphics/Sprite.h"

// �Q�[���V�[��
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// ������
	void Initialize() override;

	// �I����
	void Finalize() override;

	// �X�V����
	void Update(float elapsedTime) override;

	// �`�揈��
	void Render() override;

private:
	Stage* stage = nullptr;
	Player* player = nullptr;
	Pitcher* pitcher = nullptr;
	Ball* ball = nullptr;
	CameraController* cameraController = nullptr;
	

	Sprite* scenegame_ui = nullptr;
};
