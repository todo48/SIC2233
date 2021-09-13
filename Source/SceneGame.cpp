#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include"Camera.h"
#include"BallManager.h"
#include"BaseBall.h"
#include"EffectManager.h"

#include"Input/GamePad.h"
#include"Input/Input.h"
#include "SceneResult.h"
#include "SceneManager.h"


// 初期化
void SceneGame::Initialize()
{
	//ステージ初期化
	stage = new Stage();
	//プレイヤー初期化
	player = new Player();
	//ピッチャー初期化
	pitcher = new Pitcher();
	//カメラコントローラーの初期化
	cameraController = new CameraController();
	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);

	// 2Dスプライト

	scenegame_ui = new Sprite("Data/Sprite/UI_SceneGame_S1.png");

	//Audio初期化
	Game		 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Game.wav", true);
	Hit			 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Hit.wav", true);
	Ballcatch	 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Ballcatch.wav", true);
	Swing		 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Swing.wav", true);
	


}

// 終了化
void SceneGame::Finalize()
{
	//カメラコントローラー終了化
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}

	//プレイヤー終了化
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	//ピッチャー終了化
	if (pitcher != nullptr)
	{
		delete pitcher;
		pitcher = nullptr;
	}
	//ステージ終了化
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}
	
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	//ステージ更新処理
	stage->Update(elapsedTime);

	//プレイヤー更新処理
	player->Update(elapsedTime);

	//ピッチャー更新処理
	pitcher->Update(elapsedTime);

	// BGM
	//Game->Play();

	//カメラコントローラー更新処理
	DirectX::XMFLOAT3 eye = player->GetPosition();
	eye.y += 1.5;
	eye.z += 2.0;
	cameraController->SetEye(eye);
	cameraController->Update(elapsedTime);

	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);


	// 

	GamePad& gamePad = Input::Instance().GetGamePad();

	if (gamePad.GetButtonDown() & GamePad::BTN_J)
	{
		SceneManager::Instance().ChangeScene(new SceneResult);
	}


}


// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）
	
	//カメラパラメータ設定
	Camera& camera = Camera::instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	
	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);

		//ステージ描画
		stage->Render(dc, shader);

		//プレイヤー描画
		player->Render(dc, shader);

		//ピッチャー描画
		pitcher->Render(dc, shader);

		shader->End(dc);
	}

	// 2Dスプライト描画
	{
		float screenWidth = static_cast<float>(graphics.GetScreenWidth());
		float screenHeight = static_cast<float>(graphics.GetScreenHeight());
		float textureWidth = static_cast<float>(scenegame_ui->GetTextureWidth());
		float textureHeight = static_cast<float>(scenegame_ui->GetTextureHeight());
		scenegame_ui->Render(dc,
			0, 0, screenWidth, screenHeight,
			0, 0, textureWidth, textureHeight,
			0,
			1, 1, 1, 1);
	}




	//3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 3Dデバッグ描画
	{
		//プレイヤーデバッグプリミティブ描画
		player->DrawDebugPrimitive();

		//ピッチャーデバッグプリミティブ描画
		pitcher->DrawDebugPrimitive();

		// ラインレンダラ描画実行
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// デバッグレンダラ描画実行
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

	

	// 2DデバッグGUI描画
	{
		player->DrawDebugGUI();
	}
}
