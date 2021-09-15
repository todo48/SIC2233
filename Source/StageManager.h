#pragma once

#include <vector>
#include "Stage.h"

class StageManager
{
private:
	StageManager() {}
	~StageManager() {}

public:
	static StageManager& Instance() {

		static StageManager instance;
		return instance;
	}

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//ステージ登録
	void Register(Stage* stage);

	void clear();

private:
	std::vector<Stage*> stages;
};