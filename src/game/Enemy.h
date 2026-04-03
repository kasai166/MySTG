#pragma once
#include "../engine/DirectXManager.h"

class Enemy {
public:
    Enemy(float x, float y, int moveID, int shotID);
    void Update(float playerX, float playerY); 
    void Draw(DirectXManager& dx);
    bool IsOut() const;

private:
    void MoveRoutine();
    void ShotRoutine(float px, float py);

    float m_x, m_y;
    int m_moveID;
    int m_shotID;
    int m_timer; 
    bool m_active;
};