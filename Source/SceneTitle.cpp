#include "Graphics/Graphics.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneLoading.h"

//������
void SceneTitle::Initialize()
{
    //�X�v���C�g������
    sprite = new Sprite("Data/Sprite/Title.png");


    Title = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Title.wav", true);

    GameStart = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Gamestart.wav", false);
 //   GameStart = Audio::Instance().LoadAudioSource("Data/Audio/Gamestart.wav", false);

    titlet_imer = 30;
}

#define DELETE_IF(x) if( (x) != nullptr ){ delete (x); x = nullptr;}

//�I����
void  SceneTitle::Finalize()
{
   

    DELETE_IF(sprite);
}

//�X�V����
void SceneTitle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //�Ȃɂ��{�^�����������玟�̃V�[���֐؂�ւ�
    const GamePadButton anyButton =
        GamePad::BTN_A |
        GamePad::BTN_B |
        GamePad::BTN_X |
        GamePad::BTN_Y;

    //Title->Play();
    switch (state)
    {
    case 0:
        if (gamePad.GetButtonDown() & anyButton)
        {

            GameStart->Play();
        
            state++;
        }

        break;
    case 1:
            titlet_imer--;
        if (titlet_imer < 0)
        {
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
            break;
        }

    }
}

//�`�揈��
void SceneTitle::Render()
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