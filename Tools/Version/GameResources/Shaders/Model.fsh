uniform sampler2D sTexture;

uniform vec3 FogColor;

varying vec3 DiffuseLight;
varying vec2 TexCoord;
varying vec3 FogIntensity;

void main()
{
	vec4 texColor = (texture2D(sTexture, TexCoord)) * vec4(DiffuseLight, 1.0) + vec4(0.2,0.2,0.2,0.0);
	vec3 color = mix(FogColor, texColor.rgb, FogIntensity);
	gl_FragColor = vec4(color, texColor.a);
}

