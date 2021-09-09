#pragma once

#include<vector>
#include"Ball.h"


//ボールマネージャー
class BallManager 
{
public:
	BallManager();
	~BallManager();

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグプリミティブ描画
	void DrawDebugPrimitive();

	// ボール登録
	void Register(Ball* ball);

	//ボール全削除
	void Clear();

	//ボール数取得
	int GetBallCount() const { return static_cast<int>(balls.size()); }

	//ボール取得
	Ball* GetBall(int index) { return balls.at(index); }

	//ボール削除
	void Remove(Ball* ball);
	


private:
	std::vector<Ball*>balls;
	std::vector <Ball*>removes;
};
