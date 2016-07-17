#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect body;
uniform sampler2DRect ink;
uniform sampler2DRect cutout;
uniform sampler2DRect bg;
uniform sampler2DRect bgMask;

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
    vec4 bodyPx = texture(body, fsIn.texCoord);
    vec4 paperPx = texture(bg, fsIn.texCoord);	

    vec4 result = bodyPx;

   	if (bodyPx.a == 0.0)
    {
        if (bgMaskPx.a == 0.0)
            result = paperPx;
        else
        {
            result = vec4(BlendColorBurn(paperPx.rgb, cutoutPx.rgb), paperPx.a);
            result = vec4(BlendColorBurn(result.rgb, inkPx.rgb), paperPx.a);
        }
    }

	outputColor = result;
}