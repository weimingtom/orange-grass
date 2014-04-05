#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D sTexture;
uniform sampler2D sShadowTexture;

uniform vec3 FogColor;
uniform bool FogEnabled;

varying vec3 DiffuseLight;
varying vec2 TexCoord;
varying vec4 TexCoordShadow;
//varying vec2 TexCoordShadow;
varying vec3 FogIntensity;

void main()
{
    vec4 texSColor = texture2DProj(sShadowTexture, TexCoordShadow);
    vec4 texColor = texture2D(sTexture, TexCoord);
    vec3 texColorShaded = texColor.rgb * DiffuseLight - texSColor;

    //float comp = (TexCoordShadow.z / TexCoordShadow.w) - 0.03;
    //float depth = texture2DProj(sShadowTexture, TexCoordShadow).r;
    //float shadowVal = comp <= depth ? 1.0 : 0.0;

    if (FogEnabled)
    {
        gl_FragColor.rgb = mix(FogColor, texColorShaded.rgb, FogIntensity);
    }
    else
    {
        gl_FragColor.rgb = texColorShaded.rgb * texSColor.a;// * shadowVal;
    }
    gl_FragColor.a = texColor.a;
}
