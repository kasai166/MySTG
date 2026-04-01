#include <windows.h>
#include "engine/DirectXManager.h"

// DirectXを管理するクラスのインスタンス（実体）
DirectXManager g_dx;

// ウィンドウのメッセージ（閉じるボタンなど）を処理する関数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// プログラムの開始地点
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow) {
    // 1. ウィンドウの設定
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, hInst, NULL, NULL, NULL, NULL, L"MYSTG", NULL };
    RegisterClassEx(&wc);

    // 2. ウィンドウを作る
    HWND hWnd = CreateWindowW(L"MYSTG", L"MYSTG-Altair", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, NULL, NULL, hInst, NULL);
    
    // 3. DirectXの初期化
    if (FAILED(g_dx.Init(hWnd))) {
        return 0;
    }

    ShowWindow(hWnd, nShow);

    // 4. メインループ（ここがゲームの心臓部）
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // --- 描画処理 ---
            g_dx.BeginRender(); // 画面をクリア

            // ここに後で「弾の移動」や「描画」を書いていきます

            g_dx.EndRender();   // 画面を更新（表示）
        }
    }

    return 0;
}