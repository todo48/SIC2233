#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include"Audio/Audio.h"


//�^�C�g���V�[��
class SceneTitle : public Scene
{
public:
    SceneTitle() {}
    ~SceneTitle() {}

    //������
     void Initialize() override;

    //�I����
     void Finalize() override;

    //�X�V����
     void Update(float elapsedTime) override;

    //�`�揈��
     void Render() override;

     std::unique_ptr<AudioSource> Title;
     std::unique_ptr<AudioSource> GameStart;

public:
    int state = 0;
    int title_timer = 0;
private:
    Sprite* sprite = nullptr;
};
