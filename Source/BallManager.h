#pragma once

#include<vector>
#include"Ball.h"


//�{�[���}�l�[�W���[
class BallManager 
{
public:
	BallManager();
	~BallManager();

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	// �{�[���o�^
	void Register(Ball* ball);

	//�{�[���S�폜
	void Clear();

	//�{�[�����擾
	int GetBallCount() const { return static_cast<int>(balls.size()); }

	//�{�[���擾
	Ball* GetBall(int index) { return balls.at(index); }

	//�{�[���폜
	void Remove(Ball* ball);
	


private:
	std::vector<Ball*>balls;
	std::vector <Ball*>removes;
};
