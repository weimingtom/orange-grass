uniform sampler2D sTexture;

varying vec2 TexCoord;
varying vec4 VertexColor;

void main()
{
	vec4 texColor = texture2D(sTexture, TexCoord) * VertexColor;
	gl_FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);//texColor;
}

