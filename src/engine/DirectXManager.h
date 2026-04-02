#pragma once
#include <d3d11.h>
#include <wrl/client.h> 

using Microsoft::WRL::ComPtr;

class DirectXManager {
public:
    HRESULT Init(HWND hWnd);
    void BeginRender();
    void EndRender();
    void DrawPlayer(float x, float y, float width = 0.05f, float height = 0.08f);

private:
    ComPtr<ID3D11Device>           m_device;
    ComPtr<ID3D11DeviceContext>    m_context;
    ComPtr<IDXGISwapChain>         m_swapChain;
    ComPtr<ID3D11RenderTargetView> m_renderTarget;

    ComPtr<ID3D11VertexShader>     m_vertexShader;
    ComPtr<ID3D11PixelShader>      m_pixelShader;
    ComPtr<ID3D11InputLayout>      m_inputLayout;
};