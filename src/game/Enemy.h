#pragma once
#include "../engine/DirectXManager.h"

class Enemy {
public:
    Enemy(float x, float y, int type);
    void Update();
    void Draw(DirectXManager& dx);
    bool IsOut() const;

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }

private:
    float m_x, m_y;
    float m_speed;
    int   m_type;
    bool  m_active;
};