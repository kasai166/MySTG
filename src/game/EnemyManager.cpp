#include "EnemyManager.h"

void EnemyManager::Create(float x, float y, int type) {
    m_enemies.emplace_back(x, y, type);
}

void EnemyManager::Update(int currentFrame) {
    // 出現テーブルの監視
    for (auto it = m_spawnTable.begin(); it != m_spawnTable.end(); ) {
        if (currentFrame >= it->spawnFrame) { // 時間が来たら生成
            Create(it->x, -50.0f, it->type);
            it = m_spawnTable.erase(it); // 出現させたデータはリストから削除
        } else {
            // spawnFrame順に並んでいるためループを抜けて効率化
            break; 
        }
    }

    // 敵個別の移動処理
    for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
        it->Update();
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
    // 第1引数：出現フレーム、第2引数：X座標、第3引数：敵の種類
    //テストのために簡単な出現パターンを追加
    m_spawnTable.push_back({ 60,  640.0f, 0 });  // 1秒後：中央
    m_spawnTable.push_back({ 120, 320.0f, 0 });  // 2秒後：左
    m_spawnTable.push_back({ 120, 960.0f, 0 });  // 2秒後：右
}