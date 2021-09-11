#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include"Audio/Audio.h"


//タイトルシーン
class SceneTitle : public Scene
{
public:
    SceneTitle() {}
    ~SceneTitle() {}

    //初期化
     void Initialize() override;

    //終了化
     void Finalize() override;

    //更新処理
     void Update(float elapsedTime) override;

    //描画処理
     void Render() override;

     std::unique_ptr<AudioSource> Title;
     std::unique_ptr<AudioSource> GameStart;

public:
    int state = 0;
    int title_timer = 0;
private:
    Sprite* sprite = nullptr;
};
