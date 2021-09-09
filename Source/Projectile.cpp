//内積　
//Inner Product   Product(積)Inner(内側の)
//Dot Product 
//Scalar   Scalar(スカラー)

//外積
//Outer Product
//Cross Product
//Vector Product

#include"Projectile.h"
#include"ProjectileManager.h"
#include"Graphics/Graphics.h"

//コンストラクタ
Projectile::Projectile(ProjectileManager* manager):manager(manager)
{
	manager->Register(this);
}

//デバッグプリミティブ描画
void Projectile::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバッグ球を描画
	debugRenderer->DrawSphere(position, radius,DirectX::XMFLOAT4(0, 0, 0, 1));
}

void Projectile::UpdateTransform()
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
	Right = DirectX::XMVector3Cross(Up,Front);
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

	//発射方向
	this->direction = front;
}




//破棄
void Projectile::Destroy()
{
	manager->Remove(this);
}