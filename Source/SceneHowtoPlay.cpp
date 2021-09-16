#include "Graphics/Graphics.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneHowtoPlay.h"
//初期化
void SceneHowtoPlay::Initialize()
{
    Tutorial = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Tutorial.wav", true);

    //スプライト初期化
    sprite = new Sprite("Data/Sprite/Howtoplay.png");
    title_timer = 26;
    state = 0;
}

#define DELETE_IF(x) if( (x) != nullptr ){ delete (x); x = nullptr;}

//終了化
void  SceneHowtoPlay::Finalize()
{


    DELETE_IF(sprite);
}

//更新処理
void SceneHowtoPlay::Update(float elapsedTime)
{
    Tutorial->Play();
    GamePad& gamePad = Input::Instance().GetGamePad();
    // BGM
       //なにかボタンを押したら次のシーンへ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_Q | GamePad::BTN_W | GamePad::BTN_E |
        GamePad::BTN_A | GamePad::BTN_S | GamePad::BTN_D |
        GamePad::BTN_Z | GamePad::BTN_X | GamePad::BTN_C;
    // ゲームに移動
    if (gamePad.GetButtonDown() & anyButton)
    {
        SceneManager::Instance().ChangeScene(new SceneGame);
    }

}

//描画処理
void SceneHowtoPlay::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    //2Dスプライト描画
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        //タイトルスプライト描画
        sprite->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0,
            1, 1, 1, 1);
    }
}