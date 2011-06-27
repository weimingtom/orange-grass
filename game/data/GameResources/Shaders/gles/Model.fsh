uniform sampler2D sTexture;

uniform highp vec3 FogColor;

varying lowp vec3 DiffuseLight;
varying mediump vec2 TexCoord;
varying lowp vec3 FogIntensity;

uniform lowp float AlphaReference;

void main()
{
	lowp vec4 texColor = (texture2D(sTexture, TexCoord)) * vec4(DiffuseLight, 1.0) + vec4(0.2,0.2,0.2,0.0);
	lowp vec3 color = mix(FogColor, texColor.rgb, FogIntensity);
    if (AlphaReference > 0.0 && texColor.a < AlphaReference)
    {
        discard;
    }
	gl_FragColor = vec4(color, texColor.a);
}

