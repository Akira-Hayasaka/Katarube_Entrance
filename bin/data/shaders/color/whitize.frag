#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect tex;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 fragColor;

void main()
{
    // 1. desaturate
    // 2. invert
    vec2 texCoord = fsIn.texCoord;
    vec4 col = texture(tex, texCoord);
    vec3 hsl = RGBToHSL(col.rgb);
    hsl.g = 0.0; // desaturate
    vec3 rgb = HSLToRGB(hsl);
    vec4 rgba = vec4(1.0 - rgb.r, 1.0 - rgb.g, 1.0 - rgb.b, col.a); // invert
    fragColor = rgba;
}