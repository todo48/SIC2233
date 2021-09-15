#include"Ball.h"
#include"Graphics/Graphics.h"
#include"BallManager.h"



//コンストラクタ
Ball::Ball(BallManager* manager) :manager(manager)
{
	manager->Register(this);
}

//デバッグプリミティブ描画
void Ball::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	//衝突判定用のデバッグ円柱を描画
	debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}

void Ball::UpdateTransform()
{
	DirectX::XMVECTOR Front, Up, Right;
	//前ベクトルを算出 z
	Front = DirectX::XMLoadFloat3(&direction);
	Front = DirectX::XMVector3Normalize(Front);

	//仮の上ベクトルを算出  y
	Up = DirectX::XMVectorSet(0.001f, 1, 0, 0);
	//「同じベクトルで外積するとゼロベクトルになる」 現象を防ぐため0.001f
	Up = DirectX::XMVector3Normalize(Up);
	//右ベクトルを算出 x
	Right = DirectX::XMVector3Cross(Up, Front);
	Right = DirectX::XMVector3Normalize(Right);
	//上ベクトルを算出 y
	Up = DirectX::XMVector3Cross(Front, Right);
	DirectX::XMFLOAT3 right, up, front;
	DirectX::XMStoreFloat3(&right, Right);
	DirectX::XMStoreFloat3(&up, Up);
	DirectX::XMStoreFloat3(&front, Front);
	//とりあえず、仮で回転は無視した行列を作成する
	transform._11 = right.x * scale.x;
	transform._12 = right.y * scale.x;
	transform._13 = right.z * scale.x;
	transform._14 = 0.0f;
	transform._21 = up.x * scale.y;
	transform._22 = up.y * scale.y;
	transform._23 = up.z * scale.y;
	transform._24 = 0.0f;
	transform._31 = front.x * scale.z;
	transform._32 = front.y * scale.z;
	transform._33 = front.z * scale.z;
	transform._34 = 0.0f;
	transform._41 = position.x;
	transform._42 = position.y;
	transform._43 = position.z;
	transform._44 = 1.0f;

	DirectX::XMMATRIX ST = DirectX::XMLoadFloat4x4(&transform);

	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	DirectX::XMMATRIX W = R * ST;

	DirectX::XMStoreFloat4x4(&transform, W);

	////スケール行列を作成
	//DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	////回転行列を作成
	//DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
	////位置行列を作成
	//DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	////3つの行列を組み合わせ、ワールド行列を取り出す
	//DirectX::XMMATRIX W = S * R * T;
	////計算したワールド行列を取り出す
	//DirectX::XMStoreFloat4x4(&transform, W);

	//発射方向
	this->direction = front;
}


//破棄
void Ball::Destroy()
{
	manager->Remove(this);
}