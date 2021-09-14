#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <functional>
class ScoreManager
{

public:
    //唯一のインスタンス取得
    static ScoreManager& Instance()
    {
        static ScoreManager instance;
        return instance;
    }
    // 現在のスコア
    int Score ;



    // s...今回のスコア
    void AddScore(int s)
    {
        // ランキングスコアに今回のスコアを追加
        rankingScoreList.push_back(s);

        // ソート
        std::sort(
            rankingScoreList.begin(),
            rankingScoreList.end(),
            std::greater<int>());//降順ソート
    }
    // 現在のスコアを取得
    int GetCurrentScore() { return Score; }
    
    // index.... 順位　０番から
    int GetRankingScore(int index) { return rankingScoreList[index]; }

    int Size() { return rankingScoreList.size(); }

private:
    // ランキング表示用のスコアリスト
    std::vector<int> rankingScoreList;
};