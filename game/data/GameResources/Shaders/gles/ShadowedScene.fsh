uniform sampler2D sTexture;

uniform highp vec3 FogColor;
uniform highp float FogEnabled;

varying mediump vec2 TexCoord;
varying lowp vec3 FogIntensity;

void main()
{
    lowp vec4 texColor = texture2D(sTexture, TexCoord);

    lowp vec3 color;
    if (FogEnabled > 0.0)
    {
        color = mix(FogColor, texColor.rgb, FogIntensity);
    }
    else
    {
        color = texColor.rgb;
    }

    gl_FragColor = vec4(color, texColor.a);
}
