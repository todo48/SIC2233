#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"ProjectileManager.h"
#include "Effect.h"

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

	////弾丸入力処理
	//void InputProjectile();

	////ジャンプ入力処理
	//void InputJump();

	//void CollisionProjectilesVsEnemies();

	void HitBack(const DirectX::XMFLOAT3& impulse);

protected:
	void OnLanding() override;


private:
	////スティック入力値から移動ベクトルを取得
	//DirectX::XMFLOAT3 GetMoveVec()const;

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

	int SwingZone = 0;
	bool isSwing = false;
};