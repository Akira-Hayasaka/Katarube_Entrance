#pragma include "../common/header.glsl"
#pragma include "../common/colTweak.glsl"

uniform sampler2DRect tex;
uniform sampler2DRect mask;
uniform vec2 appRes;
uniform vec2 texRes;

in VSOUT
{
    vec2 texCoord;
} fsIn;

out vec4 fragColor;

void main()
{
    vec4 maskPx = texture(mask, fsIn.texCoord);
    if (maskPx.a != 0.0)
    {
        vec2 cutOutCoord = fsIn.texCoord;
        if (cutOutCoord.x > texRes.x)
            cutOutCoord.x -= texRes.x;
        if (cutOutCoord.y > texRes.y)
            cutOutCoord.y -= texRes.y;
        fragColor = texture(tex, cutOutCoord);
    }
    else
        fragColor = vec4(0.0);
}