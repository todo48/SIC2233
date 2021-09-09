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
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

	hiteffect = new Effect("Data/Effect/NewHit.efk");
	//モデルが大きいのでスケーリング
	scale.x = scale.y = scale.z = 0.02f;
	position = {0,0,50};
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
	//ボール発射処理
	InputBall();

	//速度処理更新
	UpdateVelocity(elapsedTime);

	//ボール更新処理
	ballManager.Update(elapsedTime);
	
	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform(transform);

	
}

void Pitcher::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);

	//ボール描画処理
	ballManager.Render(dc, shader);
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

	//ボールデバッグプリミティブ
	ballManager.DrawDebugPrimitive();
}

void Pitcher::OnLanding()
{
}

void Pitcher::InputBall()
{
	if (LaunchReady == true)
	{	
		//前方向
		DirectX::XMFLOAT3 dir;
		dir.x = -sinf(angle.y);
		dir.y = 0.0f;
		dir.z = -cosf(angle.y);

		//発射位置
		DirectX::XMFLOAT3 pos;
		pos.x = position.x;
		pos.y = position.y + height * 0.5f;
		pos.z = position.z;

		//投げる位置(デフォルトでは　S　の位置)
		DirectX::XMFLOAT3 target;
		target.x = 0;
		target.y = 20;
		target.z = 0;

		//投げる位置を抽選


		DirectX::XMVECTOR PitchPos = DirectX::XMLoadFloat3(&position);
		DirectX::XMVECTOR ZonePos = {0,0,0};
		DirectX::XMVECTOR V = DirectX::XMVectorSubtract(ZonePos, PitchPos);
		DirectX::XMVECTOR R = DirectX::XMVector3LengthSq(V);

		//発射
		BaseBall* ball = new BaseBall(&ballManager);
		ball->Launch(dir, pos, target);

		LaunchReady = false;
	}
}
