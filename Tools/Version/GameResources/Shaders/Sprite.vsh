attribute vec4  inVertex;
attribute vec2  inTexCoord;

uniform mat4   MVPMatrix;

varying vec2  TexCoord;

void main()
{
	gl_Position = MVPMatrix * inVertex;
	TexCoord = inTexCoord;
}
