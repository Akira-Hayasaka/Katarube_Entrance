#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect outOfCanvas;
uniform sampler2DRect ink;
uniform sampler2DRect cutout;
uniform sampler2DRect interactive;
uniform sampler2DRect bg;
uniform sampler2DRect bgMask;
uniform float doInteractive; // 0.0 = false, 1.0 = true;
uniform vec3 rdmForInteractive;
uniform vec2 res;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 outputColor;

void main()
{
    vec4 bgMaskPx = texture(bgMask, fsIn.texCoord);
    vec4 inkPx = texture(ink, fsIn.texCoord);
    vec4 cutoutPx = texture(cutout, fsIn.texCoord);
    vec4 outCanvasPx = texture(outOfCanvas, fsIn.texCoord);
    vec4 interactivePx = texture(interactive, fsIn.texCoord);
    vec4 paperPx = texture(bg, fsIn.texCoord);	

    vec4 result = outCanvasPx;

   	if (outCanvasPx.a == 0.0)
    {
        if (bgMaskPx.a == 0.0)
            result = paperPx;
        else
        {
            result = vec4(BlendColorBurn(paperPx.rgb, cutoutPx.rgb), paperPx.a);
            result = vec4(BlendColorBurn(result.rgb, inkPx.rgb), paperPx.a);
            
            // tweak col
            if (doInteractive == 1.0)
            {
                vec3 interactivePxHSL = RGBToHSL(interactivePx.rgb);
                interactivePxHSL += rdmForInteractive;
                interactivePx.rgb = HSLToRGB(interactivePxHSL);
            }
            result = vec4(BlendColorBurn(result.rgb, interactivePx.rgb), paperPx.a);
        }
    }

	outputColor = result;
}