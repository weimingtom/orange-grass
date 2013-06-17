attribute vec4 inVertex;
attribute vec3 inNormal;
attribute vec2 inTexCoord;

uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform vec3 LightDirection;

uniform float FogEnd;
uniform float FogRcpEndStartDiff;
uniform float FogEnabled;

uniform vec3 MaterialAmbient;
uniform vec3 MaterialDiffuse;

varying vec3 DiffuseLight;
varying vec2 TexCoord;
varying vec3 FogIntensity;

void main()
{
    gl_Position = MVPMatrix * inVertex;
    DiffuseLight = MaterialDiffuse * vec3(max(dot(inNormal, LightDirection), 0.0)) + MaterialAmbient;
    TexCoord = inTexCoord;
    
    // calculating fog
    if (FogEnabled > 0.0)
    {
        // transform position to view space as we need the distance to the eye for fog
        vec3 viewPos = vec3(MVMatrix * inVertex);
        float eyeDist = length(viewPos);
        float fogIntensity = (FogEnd - eyeDist) * FogRcpEndStartDiff;
        // clamp the intensity within a valid range
        FogIntensity = vec3(clamp(fogIntensity, 0.0, 1.0));
    }
    else
    {
        FogIntensity = vec3(0.0, 0.0, 0.0);
    }
}
