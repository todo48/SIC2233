#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"



//�^�C�g���V�[��
class SceneHowtoPlay : public Scene
{
public:
    SceneHowtoPlay() {}
    ~SceneHowtoPlay() {}

    //������
    void Initialize() override;

    //�I����
    void Finalize() override;

    //�X�V����
    void Update(float elapsedTime) override;

    //�`�揈��
    void Render() override;


public:
    int state = 0;
    int title_timer = 0;
private:
    Sprite* sprite = nullptr;
};
