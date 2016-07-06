#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect tex0;
uniform float threshold;
uniform vec3 chromaKeyColor;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 outputColor;

vec4 desaturateKeepAlpha(vec4 col)
{
    // 1. desaturate
    vec3 hsl = RGBToHSL(col.rgb);
    hsl.g = 0.0; // desaturate
    vec3 rgb = HSLToRGB(hsl);
    vec4 rgba = vec4(rgb, col.a);
    return rgba;
}

void main()
{
    vec4 texel0 = texture(tex0, fsIn.texCoord);
    float diff = length(chromaKeyColor - texel0.rgb);
    
    if (diff < threshold)
    {
        texel0.a = 0.0;
    }

    outputColor = desaturateKeepAlpha(texel0);    
}