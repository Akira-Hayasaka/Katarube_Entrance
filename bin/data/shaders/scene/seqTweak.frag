#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect tex0;
uniform sampler2DRect blendTex;
uniform sampler2DRect bgMask;
uniform sampler2DRect paperTex;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 outputColor;

void main()
{
    vec4 bgMaskPx = texture(bgMask, fsIn.texCoord);
    if(bgMaskPx.a == 0.0)
        discard;
    
    vec4 texel = texture(tex0, fsIn.texCoord);
    vec4 blendTgt = texture(blendTex, fsIn.texCoord);
    vec4 paperPx = texture(paperTex, fsIn.texCoord);

  	vec4 texBlend = vec4(BlendOverlay(texel.rgb, blendTgt.rgb), texel.a);
    vec4 result = vec4(BlendMultiply(paperPx.rgb, texBlend.rgb), texel.a);

    outputColor = result;
}