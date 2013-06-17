attribute /*highp*/ vec4 inVertex;
attribute /*highp*/ vec3 inNormal;
attribute /*highp*/ vec2 inTexCoord;

uniform /*highp*/ mat4 MVPMatrix;
uniform /*highp*/ mat4 MVMatrix;
uniform /*highp*/ vec3 LightDirection;

uniform /*highp*/ float FogEnd;
uniform /*highp*/ float FogRcpEndStartDiff;
uniform /*highp*/ float FogEnabled;

uniform /*highp*/ vec3 MaterialAmbient;
uniform /*highp*/ vec3 MaterialDiffuse;

varying /*lowp*/ vec3 DiffuseLight;
varying /*mediump*/ vec2 TexCoord;
varying /*lowp*/ vec3 FogIntensity;

void main()
{
    gl_Position = MVPMatrix * inVertex;
    DiffuseLight = MaterialDiffuse * vec3(max(dot(inNormal, LightDirection), 0.0)) + MaterialAmbient;
    TexCoord = inTexCoord;
    
    // calculating fog
    if (FogEnabled > 0.0)
    {
        // transform position to view space as we need the distance to the eye for fog
        /*highp*/ vec3 viewPos = vec3(MVMatrix * inVertex);
        /*highp*/ float eyeDist = length(viewPos);
        /*highp*/ float fogIntensity = (FogEnd - eyeDist) * FogRcpEndStartDiff;
        // clamp the intensity within a valid range
        FogIntensity = vec3(clamp(fogIntensity, 0.0, 1.0));
    }
    else
    {
        FogIntensity = vec3(0.0, 0.0, 0.0);
    }
}
