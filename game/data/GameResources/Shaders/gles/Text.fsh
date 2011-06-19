varying highp vec2	v_textureCoord;
varying highp vec4	v_color;
uniform sampler2D sTexture;

void main(void)
{
	gl_FragColor = texture2D(sTexture, v_textureCoord) * v_color;
}
