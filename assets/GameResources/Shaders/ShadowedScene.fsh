#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D sTexture;

uniform vec3 FogColor;
uniform float FogEnabled;

varying vec2 TexCoord;
varying vec3 FogIntensity;

void main()
{
    vec4 texColor = texture2D(sTexture, TexCoord);
    gl_FragColor = vec4(mix(FogColor, texColor.rgb, FogIntensity), texColor.a);
}
