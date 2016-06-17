#pragma include "./header.glsl"

uniform sampler2DRect tex;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 fragColor;

void main()
{
    vec2 texCoord = fsIn.texCoord;
    fragColor = texture(tex, texCoord);
}