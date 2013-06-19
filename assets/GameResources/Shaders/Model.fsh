#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D sTexture;

uniform vec3 FogColor;
uniform float FogEnabled;

varying vec3 DiffuseLight;
varying vec2 TexCoord;
varying vec3 FogIntensity;

uniform float AlphaReference;

void main()
{
    vec4 texColor = texture2D(sTexture, TexCoord);
    if (AlphaReference > 0.0 && texColor.a < AlphaReference)
    {
        discard;
    }

    vec3 texColorShaded = texColor.rgb * DiffuseLight;
    gl_FragColor.rgb = mix(FogColor, texColorShaded.rgb, FogIntensity);
    gl_FragColor.a = texColor.a;
}

