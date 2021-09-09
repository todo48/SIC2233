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
    Result = new Sprite("Data/Sprite/Result.png");
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

#if 0
    //なにかボタンを押したら次のシーンへ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_A |
        GamePad::BTN_B |
        GamePad::BTN_X |
        GamePad::BTN_Y;
#endif

    // タイトルに戻る
    if (gamePad.GetButtonDown() & GamePad::BTN_START)
    {
        // ロード画面がいるなら " 0 " いらないなら　" 1 "
#if 1
        SceneManager::Instance().ChangeScene(new SceneTitle);
#else
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle));
#endif
    
    }

    // ゲームに戻る
    if (gamePad.GetButtonDown() & GamePad::BTN_SPACE)
    {
        // ロード画面がいるなら " 0 " いらないなら　" 1 "
#if 1   
        SceneManager::Instance().ChangeScene(new SceneGame);
#else 

        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
#endif


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
    }
}