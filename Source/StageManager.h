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

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�X�e�[�W�o�^
	void Register(Stage* stage);

	void clear();

private:
	std::vector<Stage*> stages;
};