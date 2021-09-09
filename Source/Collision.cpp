#include"Collision.h"

//���Ƌ��̌�������

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
//	//SQ=�X�N�G�A = �����̗�
//	float lengthSq;
//	DirectX::XMStoreFloat(&lengthSq, LengthSq);
//
//	//��������
//	float range = radiusA + radiusB;
//	if (lengthSq > range * range)
//	{
//		return false;
//	}
//
//	//A��B�������o��
//	//���[�g�����ނƌv�Z�R�X�g���オ�邩�痼�����Q��̏�Ԃɂ��đ召�֌W�����߂�
//	//���K��
//	Vec = DirectX::XMVector3Normalize(Vec);
//	//�傫������
//	Vec = DirectX::XMVectorScale(Vec, -range);
//	//PositionA��Vec�𑫂�
//	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
//	//�v�Z����PositionB��outPosition�ɑ��
//	DirectX::XMStoreFloat3(&outPositionB, PositionB);
//
//	return true;
//}

//�~���Ɖ~���̌�������
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
	//A�̑�����B�̓�����Ȃ瓖�����ĂȂ�
	if (PositionA.y > PositionB.y + heightB)
	{
		return false;
	}
	//A�̓���B�̑�����艺�Ȃ瓖�����ĂȂ�
	if (PositionB.y > PositionA.y + heightA)
	{
		return false;
	}
	//XZ���ʂł͈̔̓`�F�b�N
	float dx = PositionA.x - PositionB.x;
	float dz = PositionA.z - PositionB.z;
	float lengthSq = dx * dx + dz * dz;
	//���� �Փ˔���
	float range = radiusA + radiusB;
	
	if (lengthSq > range * range)
	{
		return false;
	}
	//A��B�������o��
	float length = sqrtf(lengthSq);
	//���K��
	dx /= length;
	dz /= length;
	outPositionB.x = PositionA.x - dx * range;
	outPositionB.z = PositionA.z - dz * range;
	outPositionB.y = PositionB.y; //y���ێ�

	return true;
}

//���Ɖ~���̌�������
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
	//���̑������~���̓�����Ȃ�O��
	if (sqherePosition.y - sqhereRadius > cylinderPosition.y + cylinderHeight)return false;

	//�~���̑��������̓�����Ȃ�O��
	if (cylinderPosition.y > sqherePosition.y + sqhereRadius)return false;

	//�~-->���̃x�N�g���̒����v�Z
	float dx = sqherePosition.x - cylinderPosition.x;
	float dz = sqherePosition.z - cylinderPosition.z;
	float lengthSq = dx * dx + dz * dz;

	//�����v���E�Փ˔���
	float range = sqhereRadius + cylinderRadius;
	if (lengthSq > range * range)
	{
		return false;
	}


	return true;
}