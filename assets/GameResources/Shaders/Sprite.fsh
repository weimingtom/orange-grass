#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D sTexture;

varying vec2 TexCoord;
varying vec4 VertexColor;

void main()
{
    gl_FragColor = texture2D(sTexture, TexCoord) * VertexColor;
}

