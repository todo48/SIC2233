#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"

//�^�C�g���V�[��
class SceneResult : public Scene
{
public:
    SceneResult() {}
    ~SceneResult() {}

    //������
    void Initialize() override;

    //�I����
    void Finalize() override;

    //�X�V����
    void Update(float elapsedTime) override;

    //�`�揈��
    void Render() override;

private:
    //std::unique_ptr<AudioSource> audio_Stage = nullptr;
    //std::unique_ptr<AudioSource> audio_TimeUp = nullptr;
private:
    Sprite* Result = nullptr;

    int Countre_1st = 0;
};
