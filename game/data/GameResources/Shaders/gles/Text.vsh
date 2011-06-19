attribute highp vec4	inVertex;
attribute highp vec4	inColor;
attribute highp vec2	inTexCoord;

uniform highp mat4	MVPMatrix;

varying highp vec2	v_textureCoord;
varying highp vec4	v_color;

void main(void)
{
	gl_Position = MVPMatrix * inVertex;
	v_textureCoord = inTexCoord;
	v_color = inColor;
}
