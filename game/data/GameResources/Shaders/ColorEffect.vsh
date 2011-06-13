attribute vec4 inVertex;
attribute vec2 inTexCoord;
attribute vec4 inColor;

uniform mat4 MVPMatrix;

varying vec4 VertexColor;
varying vec2 TexCoord;

void main()
{
	gl_Position = MVPMatrix * inVertex;
	VertexColor = inColor;
	TexCoord = inTexCoord;
}
