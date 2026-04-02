#include "Enemy.h"

Enemy::Enemy(float x, float y, int type)
    : m_x(x), m_y(y), m_type(type), m_speed(3.0f), m_active(true)
{
}

void Enemy::Update() {
    
    m_y += m_speed;

    if (m_y > 800.0f) {
        m_active = false;
    }
}

void Enemy::Draw(DirectXManager& dx) {
   
    dx.DrawEnemyCircle(m_x, m_y, 20.0f, 32);
}

bool Enemy::IsOut() const {
    return !m_active;
}