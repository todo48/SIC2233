#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"BallManager.h"
#include "Effect.h"

//�v���C���[
class Pitcher : public Character
{
public:
	Pitcher();
	~Pitcher() override;

	static Pitcher& instance()
	{
		static Pitcher pitcher;
		return pitcher;
	}
	int PitchZone = 0;

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�f�o�b�O�pGUI�`��
	void DrawDebugGUI();

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	//�{�[�����ˏ���
	void InputBall();

	
protected:
	void OnLanding() override;
	
private:
	Model* model = nullptr;
	Effect* hiteffect = nullptr;
	BallManager ballManager;
	float Launch_Timer = 300;

}; 
