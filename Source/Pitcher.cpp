#include<imgui.h>
#include"Pitcher.h"
#include"Input/Input.h"
#include"Camera.h"
#include"Graphics/Graphics.h"
#include"Collision.h"
#include"BaseBall.h"
#include"player.h"

//コンストラクタ
Pitcher::Pitcher()
{
	model = new Model("Data/Model/Machine/Machine.mdl");

	hiteffect = new Effect("Data/Effect/NewHit.efk");
	//モデルが大きいのでスケーリング
	scale.x = scale.y = scale.z = 0.02f;
	angle.y = 1.5708*2;
	position = {0.3,0,30};
}

//デストラクタ
Pitcher::~Pitcher()
{
	delete model;
	delete hiteffect;
}

//更新処理
void Pitcher::Update(float elapsedTime)
{

	//速度処理更新
	UpdateVelocity(elapsedTime);
	
	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform(transform);
}

void Pitcher::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}

void Pitcher::DrawDebugGUI()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//位置
			ImGui::InputFloat3("Position", &position.x);
			//回転
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			//ImGui::InputFloat3("Angle", &angle.x);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y = DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);
			//スケール
			ImGui::InputFloat3("Scale", &scale.x);
		}
	}
	ImGui::End();
}

void Pitcher::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバッグ球を描画
	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	//衝突判定用のデバッグ円柱を描画
	debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}

void Pitcher::OnLanding()
{
}

//void Player::InputBall()
//{
//	BaseBall* baseball = new BaseBall(&ballManager);
//		//前方向
//		DirectX::XMFLOAT3 dir;
//		dir.x = -sinf(angle.y);
//		dir.y = 0.0f;
//		dir.z = -cosf(angle.y);
//
//		//発射位置
//		DirectX::XMFLOAT3 pos;
//		pos.x = position.x;
//		pos.y = position.y + height * 0.5f;
//		pos.z = position.z;
//
//		//投げる位置(デフォルトでは　S　の位置)
//		DirectX::XMFLOAT3 target;
//		target.x = 0;
//		target.y = 1.30;
//		target.z = 0;
//
//		//投げる位置を抽選
//		//ストライク
//		//int a = rand() % 10;
//		int a = 1;
//		//ボール球
//		int b = 18;
//		switch (a)
//		{
//		case 0:
//			b = rand() % 17;
//			break;
//		case 1:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 2:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 3:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 4:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 5:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 6:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 7:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 8:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		case 9:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 1;
//			break;
//		}
//
//		switch (b)
//		{
//		case 0:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 1:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 2:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 3:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 4:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 5:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 6:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 7:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 8:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 9:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 10:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 11:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 12:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 13:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 14:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 15:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		case 16:
//			target.x = 0;
//			target.y = 1.75;
//			target.z = 0;
//			PitchZone = 0;
//			break;
//		}
//
//		DirectX::XMVECTOR PitchPos = DirectX::XMLoadFloat3(&position);
//		DirectX::XMVECTOR ZonePos = {0,0,0};
//		DirectX::XMVECTOR V = DirectX::XMVectorSubtract(ZonePos, PitchPos);
//		DirectX::XMVECTOR R = DirectX::XMVector3LengthSq(V);
//
//		baseball->GetPosition();
//
//		//発射
//		baseball->Launch(dir, pos, target);
//		LaunchReady = false;
//}
