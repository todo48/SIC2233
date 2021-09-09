#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"

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

private:
    //std::unique_ptr<AudioSource> audio_Stage = nullptr;
    //std::unique_ptr<AudioSource> audio_TimeUp = nullptr;
private:
    Sprite* Result = nullptr;

    int Countre_1st = 0;
};
