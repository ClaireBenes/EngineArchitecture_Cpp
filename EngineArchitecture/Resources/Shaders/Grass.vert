#version 450 core

layout(location = 0) in vec3 pos;        
layout(location = 2) in vec2 texCoord;   

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform float time;

uniform int uGridSizeX;
uniform int uGridSizeZ;

out vec2 fragTexCoord;

float rand(float n) 
{
    return fract(sin(n * 17.0) * 0.5453123);
}

mat4 constructRotationMatrixY(float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    return mat4(
        vec4(c, 0.0, s, 0.0), 
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(-s, 0.0, c, 0.0), 
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

void main()
{
    int x = gl_InstanceID % uGridSizeX;
    int z = gl_InstanceID / uGridSizeZ;

    vec2 offset = vec2(float(x), float(z)) / 5; 

    float r = rand(float(gl_InstanceID));
    float swayOffset = r * 6.2831;

    // Base scale and wind strength
    float baseScale = r * 0.5 + 0.5;
    float windStrength = (0.1 + r + 1.3) * 0.15;


    // Gust factor
    float gustFactor = (sin(time * 0.1) + 1.0) * 0.5;

    // Global wave (influences the field-wide wind effect)
    float globalWave = sin(time * (2.0 + r * 0.5) - offset.x * 0.8 + pos.y * 0.3);
    globalWave = (globalWave + 1.0) * 0.5 * gustFactor; // normalize and apply gust

    // Individual sway (per-blade variation)
    float individualSway = sin(time * (2.0 + r * 0.5) + swayOffset + pos.y * 1.5);
    individualSway = (individualSway + 1.0) * 0.5;

    // Combine sway: make the global wave more dominant
    float combinedSway = (globalWave * 0.8 + individualSway * 0.2) * windStrength;

    // Bending factor based on position height
    float bendFactor = smoothstep(0.0, 1.0, pos.y);

    // Apply random rotation around Y-axis
    float rotationAngle = r * 3.14159265 * 2.0;
    mat4 rotationMatrix = constructRotationMatrixY(rotationAngle);

    // Apply rotation to the position
    vec3 rotatedPos = (rotationMatrix * vec4(pos, 1.0)).xyz;

    // Scale grass based on wave and random factor
    float scaleFactor = baseScale + globalWave * 0.05; // increased wave scale effect
    vec3 scaledPos = rotatedPos * scaleFactor;

    // Displace based on sway and bending factor
    vec3 displacedPos = scaledPos + vec3(combinedSway * bendFactor, 0.0, 0.0);
    displacedPos.xz += offset;

    // Final position transformation
    gl_Position = vec4(displacedPos, 1.0) * uWorldTransform * uViewProj;
    fragTexCoord = texCoord;
}