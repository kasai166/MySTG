#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float x, float y, int moveID, int shotID)
    : m_x(x), m_y(y), m_moveID(moveID), m_shotID(shotID), m_timer(0), m_active(true) {}

void Enemy::Update(float playerX, float playerY) {
    m_timer++;
    
    MoveRoutine();          
    ShotRoutine(playerX, playerY);

    if (m_y > 800.0f || m_y < -100.0f || m_x < -100.0f || m_x > 1380.0f) {
        m_active = false;
    }
}

// --- 移動パターン ---
void Enemy::MoveRoutine() {
    switch (m_moveID) {
        case 0: // 単純落下
            m_y += 3.0f;
            break;
        case 1: // 止まってから円を描く
            if (m_timer < 120) m_y += 2.0f;
            else {
                m_x += cosf(m_timer * 0.05f) * 4.0f;
                m_y += sinf(m_timer * 0.05f) * 4.0f;
            }
            break;
    }
}

// --- 攻撃パターン ---
void Enemy::ShotRoutine(float px, float py) {
    if (m_timer % 60 != 0) return; 

    switch (m_shotID) {
        case 1: break;
    }
}

void Enemy::Draw(DirectXManager& dx) {
    dx.DrawEnemyCircle(m_x, m_y, 20.0f);
}

bool Enemy::IsOut() const { return !m_active; }