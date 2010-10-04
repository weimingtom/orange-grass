uniform sampler2D sTexture;

uniform vec3 FogColor;

varying vec4 VertexColor;
varying vec2 TexCoord;
varying vec3 FogIntensity;

void main()
{
	vec4 texColor = texture2D(sTexture, TexCoord) * VertexColor;
	vec3 color = mix(FogColor, texColor.rgb, FogIntensity);
	gl_FragColor = vec4(color, texColor.a);
}

