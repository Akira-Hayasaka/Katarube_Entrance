#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect knife;
uniform sampler2DRect portrait;
uniform vec3 rdmForPortrait;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 outputColor;

void main()
{
    vec4 knifePx = texture(knife, fsIn.texCoord);
    vec4 portraitPx = texture(portrait, fsIn.texCoord);
    
    // tweak col randomly
    vec3 portraitPxHSL = RGBToHSL(portraitPx.rgb);
    portraitPxHSL += rdmForPortrait;
    portraitPx.rgb = HSLToRGB(portraitPxHSL);

    vec4 result = vec4(BlendMultiply(knifePx.rgb, portraitPx.rgb), 1.0);
    
    outputColor = result;
}