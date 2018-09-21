struct FVertex
{
     float4 Position
     float4 Color
};

struct FAnchor
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

FAnchor VertexShader(FVertex Vertex : VERTEX)
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