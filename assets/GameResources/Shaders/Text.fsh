#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_textureCoord;
varying vec4 v_color;
uniform sampler2D sTexture;

void main(void)
{
    gl_FragColor = texture2D(sTexture, v_textureCoord) * v_color;
}
