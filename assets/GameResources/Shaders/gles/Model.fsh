uniform sampler2D sTexture;

uniform highp vec3 FogColor;
uniform highp float FogEnabled;

varying lowp vec3 DiffuseLight;
varying mediump vec2 TexCoord;
varying lowp vec3 FogIntensity;

uniform lowp float AlphaReference;

void main()
{
    lowp vec4 texColor = (texture2D(sTexture, TexCoord)) * vec4(DiffuseLight, 1.0);
    if (AlphaReference > 0.0 && texColor.a < AlphaReference)
    {
        discard;
    }

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

