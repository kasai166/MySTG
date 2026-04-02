#include <windows.h>
#include "engine/DirectXManager.h"

#pragma execution_character_set("utf-8")

DirectXManager g_dx;

float g_playerX = 640.0f;
float g_playerY = 600.0f;
float g_playerSpeed = 5.0f;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow) {
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"MYSTG_CLASS";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassExW(&wc)) return 0;

    HWND hWnd = CreateWindowW(
        L"MYSTG_CLASS", L"STG Project - Altair", WS_OVERLAPPEDWINDOW, 
        100, 100, 1280, 720, NULL, NULL, hInst, NULL
    );
    if (!hWnd) return 0;

    // 初期化失敗時
    if (FAILED(g_dx.Init(hWnd))) {
        MessageBoxW(hWnd, L"DirectXの初期化に失敗しました。終了します。", L"Fatal Error", MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nShow);

    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            if (GetAsyncKeyState(VK_LEFT))  g_playerX -= g_playerSpeed;
            if (GetAsyncKeyState(VK_RIGHT)) g_playerX += g_playerSpeed;
            if (GetAsyncKeyState(VK_UP))    g_playerY -= g_playerSpeed;
            if (GetAsyncKeyState(VK_DOWN))  g_playerY += g_playerSpeed;

            g_dx.BeginRender();
            g_dx.DrawPlayer(g_playerX, g_playerY);
            g_dx.EndRender();
        }
    }
    return 0;
}