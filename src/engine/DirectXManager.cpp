#include "DirectXManager.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

DirectXManager::DirectXManager() {}
DirectXManager::~DirectXManager() {}

HRESULT DirectXManager::Init(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 1280;
    sd.BufferDesc.Height = 720;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 1,
        D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice, NULL, &m_pImmediateContext
    );
    if (FAILED(hr)) return hr;

    ComPtr<ID3D11Texture2D> pBackBuffer;
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);
    m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, &m_pRenderTargetView);
    m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);

    D3D11_VIEWPORT vp = { 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f };
    m_pImmediateContext->RSSetViewports(1, &vp);

    return S_OK;
}

void DirectXManager::BeginRender() {
    float clearColor[] = { 0.1f, 0.1f, 0.3f, 1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), clearColor);
}

void DirectXManager::EndRender() {
    m_pSwapChain->Present(0, 0);
}