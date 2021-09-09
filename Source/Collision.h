#pragma once

#include<DirectXMath.h>

//ƒRƒŠƒWƒ‡ƒ“
class Collision
{
public:
	//‹…‚Æ‹…‚ÌŒğ·”»’è
	//static bool IntersectSphereVsSphere
	//(
	//	const DirectX::XMFLOAT3& PositionA,
	//	float radiusA,
	//	const DirectX::XMFLOAT3& PositionB,
	//	float radiusB,
	//	DirectX::XMFLOAT3& outPositionB
	//	);

	//‰~’Œ‚Æ‰~’Œ‚ÌŒğ·”»’è
	static bool IntersectCylinderVsCylinder
	(
		const DirectX::XMFLOAT3& PositionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& PositionB,
		float radiusB,
		float heightB,
		DirectX::XMFLOAT3& outPositionB
	);

	//‹…‚Æ‰~’Œ‚ÌŒğ·”»’è
	static bool IntersectSqhereVsCylinder
	(
		const DirectX::XMFLOAT3& sqherePosition,
		float sqhereRadius,
		const DirectX::XMFLOAT3& cylinderPosition,
		float cylinderRadius,
		float cylinderHeight,
		DirectX::XMFLOAT3& outCylinderPosition
	);


};