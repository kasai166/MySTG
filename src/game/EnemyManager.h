#pragma once
#include <vector>
#include "Enemy.h"

struct EnemySpawnData {
    int   spawnFrame; // 何フレーム目に出現するか
    float x;          // どの横位置に出すか
    int   type;       // 敵の種類
};//出現テーブル

class EnemyManager {
public:
    void Create(float x, float y, int type);
    void Update(int currentFrame); 
    void Draw(DirectXManager& dx);
    void Clear() { m_enemies.clear(); }
    void LoadStageData();

private:
    std::vector<Enemy> m_enemies;
    std::vector<EnemySpawnData> m_spawnTable; // 敵の出現スケジュール
};