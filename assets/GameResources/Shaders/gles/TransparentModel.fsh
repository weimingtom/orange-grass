uniform sampler2D sTexture;

uniform highp vec3 FogColor;
uniform highp float FogEnabled;

varying lowp vec3 DiffuseLight;
varying mediump vec2 TexCoord;
varying lowp vec3 FogIntensity;

uniform lowp float AlphaReference;

void main()
{
    lowp vec4 texColor = texture2D(sTexture, TexCoord);
    if (AlphaReference > 0.0 && texColor.a < AlphaReference)
    {
        discard;
    }

	lowp vec3 texColorShaded = texColor.rgb * DiffuseLight;
    gl_FragColor.rgb = mix(FogColor, texColorShaded.rgb, FogIntensity);
    gl_FragColor.a = texColor.a;
}

