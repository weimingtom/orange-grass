uniform sampler2D sTexture;

varying highp vec4 VertexColor;
varying highp vec2 TexCoord;

void main()
{
    gl_FragColor = texture2D(sTexture, TexCoord) * VertexColor;
}

