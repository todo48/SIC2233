#include "Graphics/Graphics.h"
#include "SceneResult.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneLoading.h"


//������
void SceneResult::Initialize()
{
    //�X�v���C�g������
    sprites[0] = std::make_unique<Sprite>("Data/Fonts/font3.png");
    Result = new Sprite("Data/Sprite/Result.png");

    //Audio������
    AResult = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Result.wav", true);
    GameStart = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\GameStart.wav", true);
}

#define DELETE_IF(x) if( (x) != nullptr ){ delete (x); x = nullptr;}

//�I����
void  SceneResult::Finalize()
{
    DELETE_IF(Result);
}

//�X�V����
void SceneResult::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    AResult->Play();

#if 0
    //�Ȃɂ��{�^�����������玟�̃V�[���֐؂�ւ�
    const GamePadButton anyButton =
        GamePad::BTN_A |
        GamePad::BTN_B |
        GamePad::BTN_X |
        GamePad::BTN_Y;
#endif

    // �^�C�g���ɖ߂�
    if (gamePad.GetButtonDown() & GamePad::BTN_START)
    {
        // ���[�h��ʂ�����Ȃ� " 0 " ����Ȃ��Ȃ�@" 1 "
#if 1
        GameStart->Play();
        SceneManager::Instance().ChangeScene(new SceneTitle);
#else
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle));
#endif
    
    }

    // �Q�[���ɖ߂�
    if (gamePad.GetButtonDown() & GamePad::BTN_SPACE)
    {
        // ���[�h��ʂ�����Ȃ� " 0 " ����Ȃ��Ȃ�@" 1 "
#if 1   
        SceneManager::Instance().ChangeScene(new SceneGame);
#else 

        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
#endif


    }
}

//�`�揈��
void SceneResult::Render()
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
        float textureWidth = static_cast<float>(Result->GetTextureWidth());
        float textureHeight = static_cast<float>(Result->GetTextureHeight());
        //�^�C�g���X�v���C�g�`��
        Result->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0,
            1, 1, 1, 1);

        int i = 45;

        //sprites[0]->textout(dc, i, 0, 0, 16, 16, 1, 1, 1, 1);
        sprites[0]->textout(dc, std::to_string(i), 200, 200, 32, 32, 1, 1, 1, 1);
    }
}