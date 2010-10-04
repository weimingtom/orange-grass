uniform sampler2D sTexture;

varying vec2 TexCoord;

void main()
{
	vec3 texColor = texture2D(sTexture, TexCoord).rgb;
	gl_FragColor = vec4(texColor, 1.0);
}

