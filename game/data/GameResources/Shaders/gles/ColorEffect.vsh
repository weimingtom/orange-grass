attribute highp vec4 inVertex;
attribute highp vec2 inTexCoord;
attribute highp vec4 inColor;

uniform highp mat4 MVPMatrix;

varying highp vec4 VertexColor;
varying highp vec2 TexCoord;

void main()
{
	gl_Position = MVPMatrix * inVertex;
	VertexColor = inColor;
	TexCoord = inTexCoord;
}
