#include "Graphics/Graphics.h"
#include "Input/Input.h"
#include "SceneLoading.h"
#include "SceneManager.h"
#include <thread>

//初期化
void SceneLoading::Initialize()
{
    //スプライト初期化
    sprite = new Sprite("Data/Sprite/Howtoplay.png");
 

    //スレッド開始
    std::thread thread(LoadingThread, this);

    //スレッドの管理を放棄
    thread.detach();
}

//終了化
void SceneLoading::Finalize()
{
    //スプライト終了化
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
}

//更新処理
void  SceneLoading::Update(float elapsedTime)
{
   /* constexpr float speed = 180;
    angle += speed * elapsedTime;*/

    //次のシーンの準備が完了したらシーンを切り替える
    //if(nextScene->IsReady())
    //{
    //    SceneManager::Instance().ChangeScene(nextScene);
    //    nextScene = nullptr;
    //}
}

//描画処理
void SceneLoading::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0〜1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    //2Dスプライト描画
    {
        //画面右上にローディングアイコンを描画
        float screenWidth = 1920;
        float screenHeight = 1080;
        float textureWidth = 1920;
        float textureHeight = 1080;
        float positionX = -150;
        float positionY = 0;

        //タイトルスプライト描画
        sprite->Render(dc,
            positionX, positionY, textureWidth, textureHeight,
            0, 0, textureWidth, textureHeight,
           0,
            1, 1, 1, 1);
    }
}

//ローディングスレッド
void SceneLoading::LoadingThread(SceneLoading* scene)
{
    //COM関連の初期化でスレッド毎に呼ぶ必要がある
    CoInitialize(nullptr);

    //次のシーンの初期化を行う
    scene->nextScene->Initialize();

    //スレッドが終わる前にCOM関連の初期化
    CoUninitialize();

    //次のシーンの準備完了設定
    scene->nextScene->SetReady();
}