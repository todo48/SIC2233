#include "Graphics/Graphics.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneHowtoPlay.h"
//������
void SceneHowtoPlay::Initialize()
{
    Tutorial = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Tutorial.wav", true);

    //�X�v���C�g������
    sprite = new Sprite("Data/Sprite/Howtoplay.png");
    title_timer = 26;
    state = 0;
}

#define DELETE_IF(x) if( (x) != nullptr ){ delete (x); x = nullptr;}

//�I����
void  SceneHowtoPlay::Finalize()
{


    DELETE_IF(sprite);
}

//�X�V����
void SceneHowtoPlay::Update(float elapsedTime)
{
    Tutorial->Play();
    GamePad& gamePad = Input::Instance().GetGamePad();
    // BGM
       //�Ȃɂ��{�^�����������玟�̃V�[���֐؂�ւ�
    const GamePadButton anyButton =
        GamePad::BTN_Q | GamePad::BTN_W | GamePad::BTN_E |
        GamePad::BTN_A | GamePad::BTN_S | GamePad::BTN_D |
        GamePad::BTN_Z | GamePad::BTN_X | GamePad::BTN_C;
    // �Q�[���Ɉړ�
    if (gamePad.GetButtonDown() & anyButton)
    {
        SceneManager::Instance().ChangeScene(new SceneGame);
    }

}

//�`�揈��
void SceneHowtoPlay::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    //2D�X�v���C�g�`��
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        //�^�C�g���X�v���C�g�`��
        sprite->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0,
            1, 1, 1, 1);
    }
}