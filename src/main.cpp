#include <windows.h>
#include "engine/DirectXManager.h"
#include "game/BulletManager.h"
#include "game/EnemyManager.h"

#pragma comment(lib, "winmm.lib")
#pragma execution_character_set("utf-8")

DirectXManager g_dx;
BulletManager g_bulletMgr;
EnemyManager g_enemyMgr;
int g_stageFrame = 0; 

// プレイヤー設定
float g_playerX = 640.0f;
float g_playerY = 600.0f;
float g_playerSpeed = 5.0f;

// 連射制限用カウンター
int g_shotTimer = 0;
const int SHOT_INTERVAL = 8; // ショット間隔（フレーム数）

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
    // --- ウィンドウクラスの設定 ---
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"MYSTG_CLASS";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassExW(&wc))
        return 0;

    // --- ウィンドウの作成 ---
    HWND hWnd = CreateWindowW(
        L"MYSTG_CLASS", L"STG Project - Altair", WS_OVERLAPPEDWINDOW,
        100, 100, 1280, 720, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return 0;

    // --- DirectXの初期化 ---
    if (FAILED(g_dx.Init(hWnd)))
    {
        MessageBoxW(hWnd, L"DirectXの初期化に失敗しました。終了します。", L"Fatal Error", MB_OK);
        return 0;
    }

    g_enemyMgr.LoadStageData();

    ShowWindow(hWnd, nShow);
    timeBeginPeriod(1);

    DWORD frameStartTime = timeGetTime();
    const DWORD targetFrameTime = 1000 / 60; 
    
    // --- メイン ---
    MSG msg = {0};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            frameStartTime = timeGetTime();

            //  自機の移動
            if (GetAsyncKeyState(VK_LEFT))
                g_playerX -= g_playerSpeed;
            if (GetAsyncKeyState(VK_RIGHT))
                g_playerX += g_playerSpeed;
            if (GetAsyncKeyState(VK_UP))
                g_playerY -= g_playerSpeed;
            if (GetAsyncKeyState(VK_DOWN))
                g_playerY += g_playerSpeed;

            //  弾の発射
            if (g_shotTimer > 0)
                g_shotTimer--;

            if (GetAsyncKeyState('Z') & 0x8000)
            {
                if (g_shotTimer <= 0)
                {
                    g_bulletMgr.Create(g_playerX, g_playerY);
                    g_shotTimer = SHOT_INTERVAL;
                }
            }

            g_bulletMgr.Update();
            g_enemyMgr.Update(g_stageFrame);

            g_dx.BeginRender();

            g_dx.DrawPlayer(g_playerX, g_playerY);

            g_bulletMgr.Draw(g_dx);

            g_enemyMgr.Draw(g_dx);

            g_dx.EndRender();
            
            g_stageFrame++;
            DWORD frameTime = timeGetTime() - frameStartTime;
            if (frameTime < targetFrameTime) {
                Sleep(targetFrameTime - frameTime); // 足りない時間分だけ待機
            }
        }
    }

    g_bulletMgr.Clear();

    return 0;
}