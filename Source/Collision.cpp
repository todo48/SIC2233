#include"Collision.h"

//‹…‚Æ‹…‚ÌŒğ·”»’è

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
//	//SQ=ƒXƒNƒGƒA = •½•û‚Ì—ª
//	float lengthSq;
//	DirectX::XMStoreFloat(&lengthSq, LengthSq);
//
//	//‹——£”»’è
//	float range = radiusA + radiusB;
//	if (lengthSq > range * range)
//	{
//		return false;
//	}
//
//	//A‚ªB‚ğ‰Ÿ‚µo‚·
//	//ƒ‹[ƒg‚ª—‚Ş‚ÆŒvZƒRƒXƒg‚ªã‚ª‚é‚©‚ç—¼•û‚ğ‚Qæ‚Ìó‘Ô‚É‚µ‚Ä‘å¬ŠÖŒW‚ğŒˆ‚ß‚é
//	//³‹K‰»
//	Vec = DirectX::XMVector3Normalize(Vec);
//	//‘å‚«‚³’²®
//	Vec = DirectX::XMVectorScale(Vec, -range);
//	//PositionA‚ÉVec‚ğ‘«‚·
//	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
//	//ŒvZ‚µ‚½PositionB‚ğoutPosition‚É‘ã“ü
//	DirectX::XMStoreFloat3(&outPositionB, PositionB);
//
//	return true;
//}

//‰~’Œ‚Æ‰~’Œ‚ÌŒğ·”»’è
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
	//A‚Ì‘«Œ³‚ªB‚Ì“ª‚æ‚èã‚È‚ç“–‚½‚Á‚Ä‚È‚¢
	if (PositionA.y > PositionB.y + heightB)
	{
		return false;
	}
	//A‚Ì“ª‚ªB‚Ì‘«Œ³‚æ‚è‰º‚È‚ç“–‚½‚Á‚Ä‚È‚¢
	if (PositionB.y > PositionA.y + heightA)
	{
		return false;
	}
	//XZ•½–Ê‚Å‚Ì”ÍˆÍƒ`ƒFƒbƒN
	float dx = PositionA.x - PositionB.x;
	float dz = PositionA.z - PositionB.z;
	float lengthSq = dx * dx + dz * dz;
	//‹——£ Õ“Ë”»’è
	float range = radiusA + radiusB;
	
	if (lengthSq > range * range)
	{
		return false;
	}
	//A‚ªB‚ğ‰Ÿ‚µo‚·
	float length = sqrtf(lengthSq);
	//³‹K‰»
	dx /= length;
	dz /= length;
	outPositionB.x = PositionA.x - dx * range;
	outPositionB.z = PositionA.z - dz * range;
	outPositionB.y = PositionB.y; //y‚ğˆÛ

	return true;
}

//‹…‚Æ‰~’Œ‚ÌŒğ·”»’è
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
	//‹…‚Ì‘«Œ³‚ª‰~’Œ‚Ì“ª‚æ‚èã‚È‚çŠO‚ê
	if (sqherePosition.y - sqhereRadius > cylinderPosition.y + cylinderHeight)return false;

	//‰~’Œ‚Ì‘«Œ³‚ª‹…‚Ì“ª‚æ‚èã‚È‚çŠO‚ê
	if (cylinderPosition.y > sqherePosition.y + sqhereRadius)return false;

	//‰~-->‹…‚ÌƒxƒNƒgƒ‹‚Ì’·‚³ŒvZ
	float dx = sqherePosition.x - cylinderPosition.x;
	float dz = sqherePosition.z - cylinderPosition.z;
	float lengthSq = dx * dx + dz * dz;

	//‹——£Œv‘ªEÕ“Ë”»’è
	float range = sqhereRadius + cylinderRadius;
	if (lengthSq > range * range)
	{
		return false;
	}


	return true;
}