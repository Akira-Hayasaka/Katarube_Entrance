#pragma include "../common/header.glsl"

float KINECT_W = 640.0;
float KINECT_H = 480.0;

uniform sampler2DRect depthTex;
uniform float nearThresh;
uniform float farThresh;
uniform float angleAdjust;

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
    
    float nTexY = texCoord.y / KINECT_H;
    float angleFactor = 0.0;
    if (angleAdjust < 0.0)
        angleFactor = map(nTexY, 0.0, 1.0, -0.5, 0.5) * abs(angleAdjust);
    else if (0.0 < angleAdjust)
        angleFactor = map(nTexY, 0.0, 1.0, 0.5, -0.5) * abs(angleAdjust);
    depth += angleFactor;
    
    float normNearThresh = map(nearThresh, 80.0, 400.0, 1.0, 0.0);
    float normFarThresh = map(farThresh, 80.0, 400.0, 1.0, 0.0);
    
    if (normFarThresh < depth && depth < normNearThresh)
        fragColor = vec4(vec3(depth), 1.0);
    else
        fragColor = vec4(vec3(0.0), 1.0);
}
