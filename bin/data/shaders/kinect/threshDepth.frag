#pragma include "../common/header.glsl"

uniform sampler2DRect depthTex;
uniform float nearThresh;
uniform float farThresh;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 fragColor;

float map(float value, float low1, float high1, float low2, float high2)
{
    float newVal = low2 + (value - low1) * (high2 - low2) / (high1 - low1);
    return newVal;
}

void main()
{
    vec2 texCoord = fsIn.texCoord;
    vec4 depthCol = texture(depthTex, texCoord);
    
    float depth = depthCol.r;
    float normNearThresh = map(nearThresh, 80.0, 400.0, 1.0, 0.0);
    float normFarThresh = map(farThresh, 80.0, 400.0, 1.0, 0.0);
    
    if (normFarThresh < depth && depth < normNearThresh)
        fragColor = vec4(vec3(depth), 1.0);
    else
        fragColor = vec4(vec3(0.0), 1.0);
}

//#pragma include "../common/header.glsl"
//
//uniform sampler2DRect tex;
//uniform float low1;
//uniform float high1;
//uniform vec2 texRes;
//uniform float vertFlip; // 0 = false, 1 = true;
//uniform float horizFlip; // 0 = false, 1 = true;
//uniform float farFactorOnTop;
//uniform float nearFactorOnBottom;
//
//in VSOUT
//{
//    vec2 texCoord;
//} fsIn;
//
//out vec4 fragColor;
//
//float map(float value, float low1, float high1, float low2, float high2)
//{
//    float newVal = low2 + (value - low1) * (high2 - low2) / (high1 - low1);
//    return newVal;
//}
//
//void main()
//{
//    vec2 texCoord = fsIn.texCoord;
//    float yCoord = 0.0;
//    float yRes = 0.0;
//    
//    if (horizFlip == 1.0)
//    {
//        texCoord.x = texRes.x - texCoord.x;
//        yCoord = texCoord.y;
//        yRes = texRes.y;
//    }
//    
//    if (vertFlip == 1.0)
//    {
//        texCoord.y = texRes.y - texCoord.y;
//        yCoord = texCoord.x;
//        yRes = texRes.x;
//    }
//    
//    vec4 col = texture(tex, texCoord);
//    float value = col.r;
//    
//    float angleFactor = map(yCoord, 0.0, yRes, nearFactorOnBottom, farFactorOnTop);
//    value *= angleFactor;
//    
//    float low2 = 1.0;
//    float high2 = 0.0;
//    float d = clamp(low2 + (value - low1) * (high2 - low2) / (high1 - low1), 0.0, 1.0);
//    
//    if (d == 1.0)
//    {
//        d = 0.0;
//    }
//    
//    fragColor = vec4(vec3(d), 1.0);
//}