#pragma once
#include <vector>
#include <wrl.h>
#include "../engine/DirectXManager.h"


struct Bullet {
    float x, y;
    bool active;
};

class BulletManager {
public:
    void Create(float x, float y); // 新しい弾を作成
    void Update();  // 弾の位置を更新し、画面外に出た弾は非アクティブにする
    void Draw(DirectXManager& dx);  // アクティブな弾を描画
    void Clear() { m_bullets.clear(); } // 全ての弾を削除

private:
    std::vector<Bullet> m_bullets;
};