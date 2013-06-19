#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 inVertex;
attribute vec3 inNormal;
attribute vec2 inTexCoord;

uniform mat4 MVPMatrix;

void main()
{
    gl_Position = MVPMatrix * inVertex;
}
