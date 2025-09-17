//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

// ------------------------------------------
// tx - t is texture buuffer, x - slot
// ------------------------------------------
Texture2D mainTexture : register(t0);

// ------------------------------------------
// sx - s is sampler, x - slot
// ------------------------------------------
SamplerState aSampler : register(s0);

// ------------------------------------------------------------
// Sematics Vertex Output:
//      COLOR - Input to the Pixel Shader
//      SV_POSIION - System Value goes to the raster stage
// ------------------------------------------------------------
struct VertexShaderOutput
{
    float2 tex : TEXCOORD;
    float4 color : COLOR;
    float4 position : SV_POSITION;
};

// --------------------------------------------------------
//  Pixel Shader Main()
//      SV_TARGET - System Value Target
//                  output stored in a render target 0  (only one target)
// --------------------------------------------------------
float4 main(VertexShaderOutput inData) : SV_TARGET
{
    return inData.color * mainTexture.Sample(aSampler, inData.tex);
}


// --- End of File ---
