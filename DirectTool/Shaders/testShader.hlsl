cbuffer Buffer_Camera : register(b0)
{
    float4 View;

    float2 CameraPos;
    float2 Padding_Camera;
}

cbuffer Buffer_World : register(b1)
{
    float4 World;

    float2 Pos;
    float2 Padding_World;
}

cbuffer Buffer_UI : register(b2)
{
    float2 UI_Pos;
    float2 UI_Size;
    float4 UI_TEST;
}

static const float2 arrBasePos[4] =
{
    float2(-1.0, 1.0),
	float2(1.0, 1.0),
	float2(-1.0, -1.0),
	float2(1.0, -1.0),


};
static const float2 WinSizeH = { 640, 360 };

static const float2 arrUV[4] =
{
    float2(0.0, 0.0),
	float2(1.0, 0.0),
	float2(0.0, 1.0),
	float2(1.0, 1.0),
};


struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCROOD0;
};


PixelInput VS(uint VertexID : SV_VertexID)
{
    PixelInput output;

    static const float2 tempPos[4] =
    {
        UI_Pos / WinSizeH, (UI_Pos + float2(UI_Size.x, 0)) / WinSizeH,
        (UI_Pos - float2(0, UI_Size.y)) / WinSizeH, (UI_Pos + float2(UI_Size.x, -UI_Size.y)) / WinSizeH

    };
    //static const float2 tempPos[4] =
    //{
    //    float2(UI_TEST.xy),
    //    float2(UI_TEST.yy),
    //    float2(UI_TEST.xx),
    //    float2(UI_TEST.yx)

    //};

    
    //output.position = float4(arrBasePos[VertexID].xy, 0.0, 1.0);
    output.position = float4(tempPos[VertexID].xy, 0.0, 1.0);
    output.uv = arrUV[VertexID].xy;

    return output;
}


Texture2D temp : register(b0);
SamplerState defaultSampler : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    float4 color = input.color;
    //float2 origin = Position;
    
    float2 position = float2(0, 0);
    float2 uv = float2(0, 0);
    position.xy = UI_Pos;
    color = temp.Sample(defaultSampler, float2(input.uv.x * 0.25f, input.uv.y));
    if (color.a < 0.8f)
        discard;
    
    return color;
}