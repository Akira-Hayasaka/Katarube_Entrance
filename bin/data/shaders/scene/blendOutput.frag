#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect content;
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
    vec4 cutoutPx = texture(cutout, fsIn.texCoord);
    vec4 contentPx = texture(content, fsIn.texCoord);
    vec4 paperPx = texture(bg, fsIn.texCoord);	

    if (bgMaskPx.a == 0.0)
   		contentPx.a = bgMaskPx.a;

    vec4 result = vec4(BlendMultiply(paperPx.rgb, contentPx.rgb), contentPx.a);

   	if (contentPx.a == 0.0)
    {
        if (bgMaskPx.a == 0.0)
            result = paperPx;
        else
            result = vec4(BlendColorBurn(paperPx.rgb, cutoutPx.rgb), paperPx.a);
    }

	outputColor = result;
}