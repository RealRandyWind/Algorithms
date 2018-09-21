cbuffer Parameters : register(b0)
{
    float Radius;
    float2 Origin, Min, Max, Scale;
    float4 Color;
    bool UseDataRange;
};

struct FVertex
{
     float4 Position : POSITION;
     float4 Color : COLOR;
};

struct FAnchor
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

FAnchor VertexShader(FVertex Vertex)
{
    FAnchor Anchor;

    Anchor.Position = Vertex.Position;
    Anchor.Color = Vertex.Color;
    return Anchor;
}

float4 FragmentShader(
        FAnchor Anchor
    ) : SV_TARGET
{
    return Anchor.Color;
}