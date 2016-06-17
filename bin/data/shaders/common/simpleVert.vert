#pragma include "./header.glsl"
#pragma include "./defaultVertIn.glsl"

out VSOUT
{
    vec2 texCoord;
} vsout;

void main()
{
    vsout.texCoord = texcoord;
    vec4 vPos = modelViewProjectionMatrix * position;
    gl_Position = vPos;
}