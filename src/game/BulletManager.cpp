#include "BulletManager.h"

void BulletManager::Create(float x, float y) {
    m_bullets.push_back({ x, y, true });
}

void BulletManager::Update() {
    for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
        it->y -= 15.0f;

        if (it->y < -50.0f) {
            it = m_bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void BulletManager::Draw(DirectXManager& dx) {
    for (const auto& b : m_bullets) {
        dx.DrawPlayer(b.x, b.y, 0.01f, 0.03f);
    }
}