#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 inVertex;
attribute vec2 inTexCoord;
attribute vec4 inColor;

uniform mat4 MVPMatrix;

varying vec2 TexCoord;
varying vec4 VertexColor;

void main()
{
    gl_Position = MVPMatrix * inVertex;
    VertexColor = inColor;
    TexCoord = inTexCoord;
}
