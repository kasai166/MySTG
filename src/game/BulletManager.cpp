#include "BulletManager.h"

void BulletManager::Create(float x, float y) {
    m_bullets.emplace_back(x, y); // 新しい弾を生成してリストに追加
}

void BulletManager::Update() {
    for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
        it->Update(); // 弾自身で移動処理

        if (it->IsOut()) {
            it = m_bullets.erase(it); // [cite: 4]
        } else {
            ++it;
        }
    }
}

void BulletManager::Draw(DirectXManager& dx) {
    for (auto& b : m_bullets) {
        b.Draw(dx); // 各弾の描画処理
    }
}