#include"Collision.h"

//球と球の交差判定

//bool Collision::IntersectSphereVsSphere
//(
//	const DirectX::XMFLOAT3& positionA,
//	float radiusA,
//	const DirectX::XMFLOAT3& positionB,
//	float radiusB,
//	DirectX::XMFLOAT3& outPositionB)
//{
//	DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
//	DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
//	DirectX::XMVECTOR Vec       = DirectX::XMVectorSubtract(PositionA, PositionB);
//	DirectX::XMVECTOR LengthSq  = DirectX::XMVector3LengthSq(Vec);
//	//SQ=スクエア = 平方の略
//	float lengthSq;
//	DirectX::XMStoreFloat(&lengthSq, LengthSq);
//
//	//距離判定
//	float range = radiusA + radiusB;
//	if (lengthSq > range * range)
//	{
//		return false;
//	}
//
//	//AがBを押し出す
//	//ルートが絡むと計算コストが上がるから両方を２乗の状態にして大小関係を決める
//	//正規化
//	Vec = DirectX::XMVector3Normalize(Vec);
//	//大きさ調整
//	Vec = DirectX::XMVectorScale(Vec, -range);
//	//PositionAにVecを足す
//	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
//	//計算したPositionBをoutPositionに代入
//	DirectX::XMStoreFloat3(&outPositionB, PositionB);
//
//	return true;
//}

//円柱と円柱の交差判定
bool Collision::IntersectCylinderVsCylinder
(
	const DirectX::XMFLOAT3& PositionA,
	float radiusA,
	float heightA,
	const DirectX::XMFLOAT3& PositionB,
	float radiusB,
	float heightB,
	DirectX::XMFLOAT3& outPositionB
)
{
	//Aの足元がBの頭より上なら当たってない
	if (PositionA.y > PositionB.y + heightB)
	{
		return false;
	}
	//Aの頭がBの足元より下なら当たってない
	if (PositionB.y > PositionA.y + heightA)
	{
		return false;
	}
	//XZ平面での範囲チェック
	float dx = PositionA.x - PositionB.x;
	float dz = PositionA.z - PositionB.z;
	float lengthSq = dx * dx + dz * dz;
	//距離 衝突判定
	float range = radiusA + radiusB;
	
	if (lengthSq > range * range)
	{
		return false;
	}
	//AがBを押し出す
	float length = sqrtf(lengthSq);
	//正規化
	dx /= length;
	dz /= length;
	outPositionB.x = PositionA.x - dx * range;
	outPositionB.z = PositionA.z - dz * range;
	outPositionB.y = PositionB.y; //yを維持

	return true;
}

//球と円柱の交差判定
bool Collision::IntersectSqhereVsCylinder
(
	const DirectX::XMFLOAT3& sqherePosition,
	float sqhereRadius,
	const DirectX::XMFLOAT3& cylinderPosition,
	float cylinderRadius,
	float cylinderHeight,
	DirectX::XMFLOAT3& outCylinderPosition
)
{
	//球の足元が円柱の頭より上なら外れ
	if (sqherePosition.y - sqhereRadius > cylinderPosition.y + cylinderHeight)return false;

	//円柱の足元が球の頭より上なら外れ
	if (cylinderPosition.y > sqherePosition.y + sqhereRadius)return false;

	//円-->球のベクトルの長さ計算
	float dx = sqherePosition.x - cylinderPosition.x;
	float dz = sqherePosition.z - cylinderPosition.z;
	float lengthSq = dx * dx + dz * dz;

	//距離計測・衝突判定
	float range = sqhereRadius + cylinderRadius;
	if (lengthSq > range * range)
	{
		return false;
	}


	return true;
}