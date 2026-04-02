#pragma once
#include <vector>
#include "Bullet.h"

class BulletManager {
public:
    void Create(float x, float y); 
    void Update();                 
    void Draw(DirectXManager& dx); 
    void Clear() { m_bullets.clear(); }

private:
    std::vector<Bullet> m_bullets;
};