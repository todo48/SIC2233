#include "Graphics/Graphics.h"
#include "SceneResult.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneLoading.h"


//初期化
void SceneResult::Initialize()
{
    //スプライト初期化
    sprites[0] = std::make_unique<Sprite>("Data/Fonts/font3.png");
    Result = new Sprite("Data/Sprite/Result.png");

    //Audio初期化
    AResult = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\Result.wav", true);
    GameStart = Audio::Instance().LoadAudioSource(".\\Data\\Audio\\GameStart.wav", true);

    title_timer = 26;
    state = 0;

}

#define DELETE_IF(x) if( (x) != nullptr ){ delete (x); x = nullptr;}

//終了化
void  SceneResult::Finalize()
{
    DELETE_IF(Result);
}

//更新処理
void SceneResult::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    AResult->Play();

#if 0
    //なにかボタンを押したら次のシーンへ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_A |
        GamePad::BTN_B |
        GamePad::BTN_X |
        GamePad::BTN_Y;
#endif
    switch (state)
    {
    case 0:
        // タイトルに戻る
        if (gamePad.GetButtonDown() & GamePad::BTN_START)
        {
            // SE
            GameStart->Play();

            state += 1;
        }


        // ゲームに戻る
        if (gamePad.GetButtonDown() & GamePad::BTN_SPACE)
        {
            // SE
            GameStart->Play();

            state += 2;
        }


        break;

    case 1:
        title_timer--;
        if (title_timer < 0)
        {
            // ロード画面がいるなら " 0 " いらないなら　" 1 "
#if 1
            SceneManager::Instance().ChangeScene(new SceneTitle);
#else
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle));
#endif
        }
        break;

    case 2:
        title_timer--;
        if (title_timer < 0)
        {
            // ロード画面がいるなら " 0 " いらないなら　" 1 "
#if 1   
            SceneManager::Instance().ChangeScene(new SceneGame);
#else 

            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
#endif
        }
    }



}

//描画処理
void SceneResult::Render()
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
        float textureWidth = static_cast<float>(Result->GetTextureWidth());
        float textureHeight = static_cast<float>(Result->GetTextureHeight());
        //タイトルスプライト描画
        Result->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0,
            1, 1, 1, 1);

        Score = 1234567890;
        First = 1234567890;
        Second = 1234567890;
        Third = 1234567890;

        //sprites[0]->textout(dc, i, 0, 0, 16, 16, 1, 1, 1, 1);
        sprites[0]->textout(dc, std::to_string(Score), 850 -200, 235 -40 , 65, 65, 1, 1, 1, 1);
        sprites[0]->textout(dc, std::to_string(First), 850 -200, 460 -0 , 65, 65, 1, 1, 1, 1);
        sprites[0]->textout(dc, std::to_string(Second),850 -200, 635 -0 , 65, 65, 1, 1, 1, 1);
        sprites[0]->textout(dc, std::to_string(Third), 850 -200, 810 -0 , 65, 65, 1, 1, 1, 1);
    }
}