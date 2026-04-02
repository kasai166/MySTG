#include "DirectXManager.h"
#include <d3dcompiler.h>
#include <wrl.h> // ComPtrを使用するために必要

// ライブラリのリンク設定（tasks.jsonでも指定していますが、ここにも書くとより安全です）
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

struct Vertex {
    float pos[3];
    float color[4];
};

HRESULT DirectXManager::Init(HWND hWnd) {
    // --- スワップチェーンとデバイスの作成 ---
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 1280;
    sd.BufferDesc.Height = 720;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, nullptr, &m_context);
    if (FAILED(hr)) return hr;

    // --- レンダーターゲットビューの作成 ---
    ComPtr<ID3D11Texture2D> backBuffer;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
    m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_renderTarget);
    m_context->OMSetRenderTargets(1, m_renderTarget.GetAddressOf(), nullptr);

    // --- ビューポートの設定 ---
    D3D11_VIEWPORT vp = { 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f };
    m_context->RSSetViewports(1, &vp);

    ComPtr<ID3DBlob> vsBlob, psBlob, errorBlob;
    
    // --- 頂点シェーダーの読み込み ---
    hr = D3DCompileFromFile(L"engine/BasicShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &vsBlob, &errorBlob);
    if (FAILED(hr)) {
        if (errorBlob) MessageBoxA(hWnd, (char*)errorBlob->GetBufferPointer(), "VS Compile Error", MB_OK);
        else MessageBoxW(hWnd, L"engine/BasicShader.hlsl が見つかりません。", L"File Error", MB_OK);
        return hr;
    }
    m_device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_vertexShader);

    // --- ピクセルシェーダーの読み込み ---
    hr = D3DCompileFromFile(L"engine/BasicShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &psBlob, &errorBlob);
    if (FAILED(hr)) {
        if (errorBlob) MessageBoxA(hWnd, (char*)errorBlob->GetBufferPointer(), "PS Compile Error", MB_OK);
        else MessageBoxW(hWnd, L"engine/BasicShader.hlsl が見つかりません。", L"File Error", MB_OK);
        return hr;
    }
    m_device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_pixelShader);

    // --- 入力レイアウトの作成 ---
    D3D11_INPUT_ELEMENT_DESC ied[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    m_device->CreateInputLayout(ied, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_inputLayout);

    return S_OK;
}

// 描画開始前の画面クリア
void DirectXManager::BeginRender() {
    float clearColor[] = { 0.1f, 0.1f, 0.3f, 1.0f };
    m_context->ClearRenderTargetView(m_renderTarget.Get(), clearColor);
}

void DirectXManager::EndRender() {
    // 画面を更新（垂直同期あり）
    m_swapChain->Present(1, 0);
}

void DirectXManager::DrawPlayer(float x, float y) {
    // 座標をスクリーン座標(0~1280)からDirectXの座標(-1~1)へ変換
    float nx = (x / 1280.0f) * 2.0f - 1.0f;
    float ny = 1.0f - (y / 720.0f) * 2.0f;
    float w = 0.05f, h = 0.08f;

    Vertex vertices[] = {
        { { nx - w, ny + h, 0.0f }, { 1, 1, 1, 1 } },
        { { nx + w, ny + h, 0.0f }, { 1, 1, 1, 1 } },
        { { nx - w, ny - h, 0.0f }, { 1, 1, 1, 1 } },
        { { nx + w, ny - h, 0.0f }, { 1, 1, 1, 1 } },
    };

    // 頂点バッファの作成
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = vertices;
    ComPtr<ID3D11Buffer> vertexBuffer;
    m_device->CreateBuffer(&bd, &sd, &vertexBuffer);

    // 描画設定
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    m_context->IASetInputLayout(m_inputLayout.Get());
    m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    
    m_context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

    // 描画実行
    m_context->Draw(4, 0);
}