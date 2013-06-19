#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 inVertex;
attribute vec4 inColor;
attribute vec2 inTexCoord;

uniform mat4 MVPMatrix;

varying vec2 v_textureCoord;
varying vec4 v_color;

void main(void)
{
    gl_Position = MVPMatrix * inVertex;
    v_textureCoord = inTexCoord;
    v_color = inColor;
}
