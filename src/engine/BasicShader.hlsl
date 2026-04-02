struct VS_INPUT {
    float3 Pos : POSITION; // C++側と合わせてfloat3に修正
    float4 Col : COLOR;
};

struct PS_INPUT {
    float4 Pos : SV_POSITION;
    float4 Col : COLOR;
};

// 頂点シェーダー
PS_INPUT VS(VS_INPUT input) {
    PS_INPUT output;
    output.Pos = float4(input.Pos, 1.0f); // float4に正しく変換
    output.Col = input.Col;
    return output;
}

// ピクセルシェーダー
float4 PS(PS_INPUT input) : SV_Target {
    return input.Col;
}