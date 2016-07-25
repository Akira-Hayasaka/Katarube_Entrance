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
    if (texture(tex, fsIn.texCoord).a != 0.0)
        fragColor = vec4(1.0);
    else
        fragColor = vec4(0.0);
}