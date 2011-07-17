uniform sampler2D sTexture;

varying highp vec2 TexCoord;
varying highp vec4 VertexColor;

void main()
{
    gl_FragColor = texture2D(sTexture, TexCoord) * VertexColor;
}

