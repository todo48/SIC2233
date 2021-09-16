#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"ProjectileManager.h"
#include "Effect.h"
#include"BallManager.h"

//プレイヤー
class Player : public Character
{
public:
	Player();
	~Player() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグ用GUI描画
	void DrawDebugGUI();	

	////移動入力処理
	void InputMove(float elapsedTime);

	//デバッグプリミティブ描画
	void DrawDebugPrimitive();

	//ボール発射処理
	void InputBall();

//	int GetScore() { return Score; }

	////弾丸入力処理
	//void InputProjectile();
	////ジャンプ入力処理
	//void InputJump();
	//void CollisionProjectilesVsEnemies();
	//void HitBack(const DirectX::XMFLOAT3& impulse);

	static int ScoreCount;

	float speed = 5.0f;
	float speed2 = 5.0f;
protected:
	void OnLanding() override;


private:
	////スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec()const;

	////プレイヤーとエネミーの衝突処理
	//void CollisionPlayerVsEnemies();

	//ProjectileManager projectileManager;

private:
	Model* model = nullptr;
	Effect* hiteffect = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
	float jumpSpeed = 20.0f;
	int   jumpCount = 0;
	int   jumpLimit = 2;

	float InputTimer = 0;
	bool PushButton = false;

	int SwingZone = 0;
	int PitchZone = 0;
	bool IsSwing = false;
	float Launch_Timer = 0;
	float Launch_Timer_2 = 300;
	float SwingTimer = 0;

//	int Score = 0;

	float Timer = 300;
	//発射可否
	bool LaunchReady = true;
	bool LaunchReady_2 = false;

	DirectX::XMFLOAT3   HitPosition = { 0,0,0 };
};