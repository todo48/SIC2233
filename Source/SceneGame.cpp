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


// ������
void SceneGame::Initialize()
{
	//�X�e�[�W������
	stage = new Stage();
	//�v���C���[������
	player = new Player();
	//�s�b�`���[������
	pitcher = new Pitcher();
	//�J�����R���g���[���[�̏�����
	cameraController = new CameraController();
	//�J���������ݒ�
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

	// 2D�X�v���C�g

	scenegame_ui = new Sprite("Data/Sprite/UI_SceneGame_S1.png");

	//Audio������
	Game		 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Game.wav", true);
	Hit			 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Hit.wav", true);
	Ballcatch	 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Ballcatch.wav", true);
	Swing		 = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Swing.wav", true);
	


}

// �I����
void SceneGame::Finalize()
{
	//�J�����R���g���[���[�I����
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}

	//�v���C���[�I����
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	//�s�b�`���[�I����
	if (pitcher != nullptr)
	{
		delete pitcher;
		pitcher = nullptr;
	}
	//�X�e�[�W�I����
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}
	
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	//�X�e�[�W�X�V����
	stage->Update(elapsedTime);

	//�v���C���[�X�V����
	player->Update(elapsedTime);

	//�s�b�`���[�X�V����
	pitcher->Update(elapsedTime);

	// BGM
	//Game->Play();

	//�J�����R���g���[���[�X�V����
	DirectX::XMFLOAT3 eye = player->GetPosition();
	eye.y += 1.5;
	eye.z += 2.0;
	cameraController->SetEye(eye);
	cameraController->Update(elapsedTime);

	//�G�t�F�N�g�X�V����
	EffectManager::Instance().Update(elapsedTime);


	// 

	GamePad& gamePad = Input::Instance().GetGamePad();

	if (gamePad.GetButtonDown() & GamePad::BTN_J)
	{
		SceneManager::Instance().ChangeScene(new SceneResult);
	}


}


// �`�揈��
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// �`�揈��
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j
	
	//�J�����p�����[�^�ݒ�
	Camera& camera = Camera::instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	
	// 3D���f���`��
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);

		//�X�e�[�W�`��
		stage->Render(dc, shader);

		//�v���C���[�`��
		player->Render(dc, shader);

		//�s�b�`���[�`��
		pitcher->Render(dc, shader);

		shader->End(dc);
	}

	// 2D�X�v���C�g�`��
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




	//3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 3D�f�o�b�O�`��
	{
		//�v���C���[�f�o�b�O�v���~�e�B�u�`��
		player->DrawDebugPrimitive();

		//�s�b�`���[�f�o�b�O�v���~�e�B�u�`��
		pitcher->DrawDebugPrimitive();

		// ���C�������_���`����s
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

	

	// 2D�f�o�b�OGUI�`��
	{
		player->DrawDebugGUI();
	}
}
