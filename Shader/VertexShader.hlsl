
struct VertexInput
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct VertexOutput
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

struct PixelIutput
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VertexOutput vs(VertexInput input)
{
    VertexOutput output;
    output.Position = float4(input.Position, 1.0f);
    output.Color = input.Color;
    return output;
}

float4 ps(PixelIutput input):SV_TARGET
{
    return input.Color;
}