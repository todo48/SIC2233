#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include"Audio/Audio.h"

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

    //DirectX11�ŗ��p����l�X�ȃ��\�[�X���쐬������
    Microsoft::WRL::ComPtr<ID3D11Device>device;
    //ID3D11DeviceContext* immediate_context;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context;
    std::unique_ptr<Sprite>sprites[8];


private:
    std::unique_ptr<AudioSource> AResult;
    std::unique_ptr<AudioSource> GameStart;
private:
    Sprite* Result = nullptr;

    int Countre_1st = 0;
};
