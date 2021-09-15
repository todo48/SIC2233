#include "StageManager.h"

//�X�V����
void StageManager::Update(float elapedTime)
{
	for (Stage* stage : stages)
	{
		stage->Update(elapedTime);
	}
}

//�`�揈��
void StageManager::Render(ID3D11DeviceContext* context, Shader* shader)
{
	for (Stage* stage : stages)
	{
		stage->Render(context, shader);
	}
}

void StageManager::Register(Stage* stage)
{
	//stages.emplace_back(stage);
}

void StageManager::clear()
{
	for (Stage* item : stages) {
		if (item != nullptr) {
			delete item;
			item = nullptr;
		}
	}
	stages.clear();
}