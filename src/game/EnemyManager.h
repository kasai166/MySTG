#pragma once
#include <vector>
#include "Enemy.h"

struct EnemySpawnData
{
    int spawnFrame; // 何フレーム目に出現するか
    float x;        // どの横位置に出すか
    int type;       // 敵の種類
    int moveID;     // 移動パターンID   
    int shotID;         // 射撃パターンID
}; // 出現テーブル

class EnemyManager
{
public:
    void Create(float x, float y,  int moveID, int shotID);
    void Update(int currentFrame, float playerX, float playerY);
    void Draw(DirectXManager &dx);
    void Clear() { m_enemies.clear(); }
    void LoadStageData();

private:
    std::vector<Enemy> m_enemies;
    std::vector<EnemySpawnData> m_spawnTable; // 敵の出現スケジュール
};