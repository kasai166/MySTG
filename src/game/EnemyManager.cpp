#include "EnemyManager.h"

void EnemyManager::Create(float x, float y, int moveID, int shotID) {
    m_enemies.emplace_back(x, y, moveID, shotID);
}
void EnemyManager::Update(int currentFrame, float px, float py) {
    // 出現テーブルの監視
    for (auto it = m_spawnTable.begin(); it != m_spawnTable.end(); ) {
        if (currentFrame >= it->spawnFrame) { // 時間が来たら生成
            m_enemies.emplace_back(it->x, -50.0f, it->moveID, it->shotID);
            it = m_spawnTable.erase(it); // 出現させたデータはリストから削除
        } else {
            // spawnFrame順に並んでいるためループを抜けて効率化
            break; 
        }
    }

    // 敵個別の移動処理
    for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
        it->Update(px, py);
        if (it->IsOut()) {
            it = m_enemies.erase(it);
        } else {
            ++it;
        }
    }
}

void EnemyManager::Draw(DirectXManager& dx) {
    for (auto& e : m_enemies) {
        e.Draw(dx);
    }
}
void EnemyManager::LoadStageData() {
    // 引数順: { 出現フレーム, X座標, 種類(type), 移動ID, 射撃ID }
    m_spawnTable.push_back({ 60,  640.0f, 0, 1, 0 });  
    m_spawnTable.push_back({ 120, 320.0f, 0, 0, 0 });  
    m_spawnTable.push_back({ 120, 960.0f, 0, 0, 0 });  
}