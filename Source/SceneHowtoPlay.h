#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"



//タイトルシーン
class SceneHowtoPlay : public Scene
{
public:
    SceneHowtoPlay() {}
    ~SceneHowtoPlay() {}

    //初期化
    void Initialize() override;

    //終了化
    void Finalize() override;

    //更新処理
    void Update(float elapsedTime) override;

    //描画処理
    void Render() override;


public:
    int state = 0;
    int title_timer = 0;
private:
    Sprite* sprite = nullptr;
};
