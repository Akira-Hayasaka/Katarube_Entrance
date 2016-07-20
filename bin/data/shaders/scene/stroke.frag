#pragma include "../common/header.glsl"

uniform sampler2DRect tex;
uniform sampler2DRect stroke;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 fragColor;

void main()
{
	vec4 col = texture(tex, fsIn.texCoord);
	vec4 strokeMask = texture(stroke, fsIn.texCoord);
	//col.a = strokeMask.a;
	if (strokeMask.a == 0.0)
		discard;
	fragColor = col;
}