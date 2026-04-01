#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class DirectXManager {
public:
    DirectXManager();
    ~DirectXManager();

    // 初期化
    HRESULT Init(HWND hWnd);
    
    // 描画開始
    void BeginRender();
    
    // 描画終了
    void EndRender();

private:
    ComPtr<ID3D11Device>           m_pDevice;
    ComPtr<ID3D11DeviceContext>    m_pImmediateContext;
    ComPtr<IDXGISwapChain>         m_pSwapChain;
    ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
};