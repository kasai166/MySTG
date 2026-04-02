#include "Bullet.h"

Bullet::Bullet(float x, float y) 
    : m_x(x), m_y(y), m_speed(15.0f), m_active(true) 
{
}

void Bullet::Update() {
    m_y -= m_speed; 

    if (m_y < -50.0f) {
        m_active = false;
    }
}

void Bullet::Draw(DirectXManager& dx) {
    dx.DrawPlayer(m_x, m_y, 0.01f, 0.03f);// 弾は小さめの矩形で描画
}

bool Bullet::IsOut() const {
    return !m_active;
}