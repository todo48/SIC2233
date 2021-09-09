#include"BallManager.h"

//コンストラクタ
BallManager::BallManager()
{

}

//デストラクタ
BallManager::~BallManager()
{
	Clear();
}

//更新処理
void BallManager::Update(float elapsedTime)
{
	//更新処理
	for (Ball* ball : balls)
	{
		ball->Update(elapsedTime);
	}

	//破棄処理
	//ballsの範囲for文中でerase()すると不具合が発生してしまうため、
	//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する
	for (Ball* ball : removes)
	{
		//std::vectorから要素を削除する場合はイテレーターで削除しなければならない
		std::vector<Ball*>::iterator it = std::find(balls.begin(), balls.end(), ball);

		if (it != balls.end())
		{
			balls.erase(it);
		}

		//弾丸の破棄処理
		delete ball;
	}
	//破棄リストをクリア
	removes.clear();
}

//描画処理
void BallManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Ball* ball : balls)
	{
		ball->Render(dc, shader);
	}
}

//デバッグプリミティブ描画
void  BallManager::DrawDebugPrimitive()
{
	for (Ball* ball : balls)
	{
		ball->DrawDebugPrimitive();
	}
}

// 弾丸登録
void BallManager::Register(Ball* ball)
{
	balls.emplace_back(ball);
}

void BallManager::Remove(Ball* ball)
{
	//破棄リストに追加
	removes.emplace_back(ball);
}


//弾丸全削除
void BallManager::Clear()
{
	for (Ball* ball : balls)
	{
		delete ball;
	}
	balls.clear();
}