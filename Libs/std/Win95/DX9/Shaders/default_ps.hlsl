#include "common.hlsli"

struct PS_INPUT 
{
    float4 diffuse : COLOR0;
    float4 specular : COLOR1;
    float2 texCoord : TEXCOORD0;
    float rhw : TEXCOORD1;
};

sampler2D g_texture : register(s0);

float4 main(PS_INPUT input) : COLOR 
{
    // Use texture coordinates directly - they should already be perspective correct
    // from the original TL vertex calculation
    float4 texColor   = tex2D(g_texture, input.texCoord.xy);

    // TODO: In case of texture being 0 nothing will be rendered!
    float4 finalColor = texColor * input.diffuse;

    // Apply fog if enabled
    if (g_fogParams.w > 0.0f) // Note, branching might impact performance
    {
       // Calculate linear fog factor
       // fogFactor = (rhw - fogStart) / (fogEnd - fogStart)
       // Using pre-calculated 1/(end-start) in g_fogParams.z for efficiency
       float fogFactor = saturate((input.rhw - g_fogParams.x) * g_fogParams.z); // saturate - Clamp fog factor to [0, 1] range
       finalColor.rgb  = lerp(finalColor.rgb, g_fogColor.rgb, fogFactor);
    }
    
    return finalColor;
};