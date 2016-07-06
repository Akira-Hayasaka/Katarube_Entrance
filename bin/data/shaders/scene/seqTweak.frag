#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect tex0;
uniform sampler2DRect blendTex;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 outputColor;

void main()
{
    vec4 texel = texture(tex0, fsIn.texCoord);
    vec4 blendTgt = texture(blendTex, fsIn.texCoord);

  	vec4 result = vec4(BlendOverlay(texel.rgb, blendTgt.rgb), texel.a);

    outputColor = result;
}