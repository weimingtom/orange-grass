uniform sampler2D sTexture;

varying mediump vec2  TexCoord;

void main()
{
	lowp vec3 texColor  = texture2D(sTexture, TexCoord).rgb;
	gl_FragColor = vec4(texColor, 1.0);
}

