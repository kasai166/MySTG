#pragma once
#include "../engine/DirectXManager.h"

class Bullet {
public:    
    Bullet(float x, float y);// コンストラクタで初期位置を設定
    void Update();
    void Draw(DirectXManager& dx);//描画
    bool IsOut() const;// 画面外に出たかどうかを判定

private:
    float m_x, m_y;
    float m_speed;
    bool  m_active;
};