#include"BallManager.h"

//�R���X�g���N�^
BallManager::BallManager()
{

}

//�f�X�g���N�^
BallManager::~BallManager()
{
	Clear();
}

//�X�V����
void BallManager::Update(float elapsedTime)
{
	//�X�V����
	for (Ball* ball : balls)
	{
		ball->Update(elapsedTime);
	}

	//�j������
	//balls�͈̔�for������erase()����ƕs����������Ă��܂����߁A
	//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����
	for (Ball* ball : removes)
	{
		//std::vector����v�f���폜����ꍇ�̓C�e���[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<Ball*>::iterator it = std::find(balls.begin(), balls.end(), ball);

		if (it != balls.end())
		{
			balls.erase(it);
		}

		//�e�ۂ̔j������
		delete ball;
	}
	//�j�����X�g���N���A
	removes.clear();
}

//�`�揈��
void BallManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Ball* ball : balls)
	{
		ball->Render(dc, shader);
	}
}

//�f�o�b�O�v���~�e�B�u�`��
void  BallManager::DrawDebugPrimitive()
{
	for (Ball* ball : balls)
	{
		ball->DrawDebugPrimitive();
	}
}

// �e�ۓo�^
void BallManager::Register(Ball* ball)
{
	balls.emplace_back(ball);
}

void BallManager::Remove(Ball* ball)
{
	//�j�����X�g�ɒǉ�
	removes.emplace_back(ball);
}


//�e�ۑS�폜
void BallManager::Clear()
{
	for (Ball* ball : balls)
	{
		delete ball;
	}
	balls.clear();
}