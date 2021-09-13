#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include"Audio/Audio.h"

//タイトルシーン
class SceneResult : public Scene
{
public:
    SceneResult() {}
    ~SceneResult() {}

    //初期化
    void Initialize() override;

    //終了化
    void Finalize() override;

    //更新処理
    void Update(float elapsedTime) override;

    //描画処理
    void Render() override;

    //DirectX11で利用する様々なリソースを作成するやつ
    Microsoft::WRL::ComPtr<ID3D11Device>device;
    //ID3D11DeviceContext* immediate_context;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context;
    std::unique_ptr<Sprite>sprites[8];


private:
    std::unique_ptr<AudioSource> AResult;
    std::unique_ptr<AudioSource> GameStart;
public:
    int state = 0;
    int title_timer = 0;
    int Score = 0;
    int First = 0;
    int Second = 0;
    int Third = 0;
private:
    Sprite* Result = nullptr;

    int Countre_1st = 0;
};
