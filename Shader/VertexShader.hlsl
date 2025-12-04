
//------  VertexShader.hlsl  ------


struct Vertex   //------  頂点入力構造体
{
    /*
    
    
    */
    float3 Postion  : POSITION;
    float4 Color    : COLOR;
};

struct VertexOutput //------  頂点出力構造体
{
    /*
    
    */
    float3 Postion  : SV_POSITION;
    float4 Color    : COLOR;
};

struct PixelInput   //------  ピクセル入力構造体
{
    /*
    
    */
    float3 Postion  : SV_POSITION;
    float4 Color    : COLOR;
};

//------  頂点シェーダー  ------
VertexOutput vs(Vertex input)
{
    VertexOutput output;

    output.Postion = float4(input.Postion, 1.0f);
    output.Color = input.Color;
    return output;
}

//------  ピクセルシェーダー  ------
float4 ps(PixelInput input) : SV_TARGET
{
    return input.Color;
}