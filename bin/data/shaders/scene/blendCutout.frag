#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect knife;
uniform sampler2DRect portrait;
uniform sampler2DRect flyer;
uniform vec3 rdmForPortrait;
uniform vec3 rdmForFlyer;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 outputColor;

void main()
{
    vec4 knifePx = texture(knife, fsIn.texCoord);
    vec4 portraitPx = texture(portrait, fsIn.texCoord);
    vec4 flyerPx = texture(flyer, fsIn.texCoord);
    
    // tweak col 
    vec3 portraitPxHSL = RGBToHSL(portraitPx.rgb);
    portraitPxHSL += rdmForPortrait;
    portraitPx.rgb = HSLToRGB(portraitPxHSL);
    
    vec3 flyerPxHSL = RGBToHSL(flyerPx.rgb);
    flyerPxHSL += rdmForFlyer;
    flyerPx.rgb = HSLToRGB(flyerPxHSL.rgb);
    flyerPx.rgb = ContrastSaturationBrightness(flyerPx.rgb, 1.0, 1.0, 1.2);

    vec4 result = knifePx;
    if (portraitPx != vec4(1.0))
        result = vec4(BlendMultiply(knifePx.rgb, portraitPx.rgb), 1.0);
    if (flyerPx != vec4(1.0))
        result = vec4(BlendMultiply(result.rgb, flyerPx.rgb), 1.0);
    
    outputColor = result;
}