uniform sampler2D sTexture;

varying vec4 VertexColor;
varying vec2 TexCoord;

void main()
{
    gl_FragColor = texture2D(sTexture, TexCoord) * VertexColor;
}

