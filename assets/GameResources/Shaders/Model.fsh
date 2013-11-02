#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D sTexture;
uniform vec3 FogColor;
uniform bool FogEnabled;

varying vec3 DiffuseLight;
varying vec2 TexCoord;
varying vec3 FogIntensity;

void main()
{
    vec4 texColor = texture2D(sTexture, TexCoord);
    vec3 texColorShaded = texColor.rgb * DiffuseLight;
    if (FogEnabled)
    {
        gl_FragColor.rgb = mix(FogColor, texColorShaded.rgb, FogIntensity);
    }
    else
    {
        gl_FragColor.rgb = texColorShaded.rgb;
    }
    gl_FragColor.a = texColor.a;
}

