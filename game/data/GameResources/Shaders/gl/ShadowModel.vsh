attribute /*highp*/ vec4 inVertex;
attribute /*highp*/ vec3 inNormal;
attribute /*highp*/ vec2 inTexCoord;

uniform /*highp*/ mat4 MVPMatrix;

void main()
{
    gl_Position = MVPMatrix * inVertex;
}
