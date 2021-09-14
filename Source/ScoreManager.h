#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <functional>
class ScoreManager
{

public:
    //�B��̃C���X�^���X�擾
    static ScoreManager& Instance()
    {
        static ScoreManager instance;
        return instance;
    }
    // ���݂̃X�R�A
    int Score ;



    // s...����̃X�R�A
    void AddScore(int s)
    {
        // �����L���O�X�R�A�ɍ���̃X�R�A��ǉ�
        rankingScoreList.push_back(s);

        // �\�[�g
        std::sort(
            rankingScoreList.begin(),
            rankingScoreList.end(),
            std::greater<int>());//�~���\�[�g
    }
    // ���݂̃X�R�A���擾
    int GetCurrentScore() { return Score; }
    
    // index.... ���ʁ@�O�Ԃ���
    int GetRankingScore(int index) { return rankingScoreList[index]; }

    int Size() { return rankingScoreList.size(); }

private:
    // �����L���O�\���p�̃X�R�A���X�g
    std::vector<int> rankingScoreList;
};