#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D sTexture;
uniform float AlphaReference;

varying vec2 TexCoord;

void main()
{
    vec4 texColor = texture2D(sTexture, TexCoord);
    if (texColor.a < AlphaReference)
    {
        discard;
    }

    gl_FragColor = vec4(0.4, 0.4, 0.4, 1.0);
}

