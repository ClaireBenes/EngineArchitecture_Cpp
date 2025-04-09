#version 450 core

layout(location = 0) in vec3 pos;        
layout(location = 2) in vec2 texCoord;   

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform float time;

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
    int gridSize = 10;
    int x = gl_InstanceID % gridSize;
    int z = gl_InstanceID / gridSize;

    vec2 offset = vec2(float(x), float(z)) / 5; // spacing between grass

    float r = rand(float(gl_InstanceID));
    float swayOffset = r * 6.2831;

    // Basic wind effect using sine wave
    float windStrength = (0.1 + r + 1.3) * 0.1;
    float swayRaw = sin(time * 0.5 + pos.x + pos.z + swayOffset);
    float sway = pow(max(swayRaw, 0.0), 2.0) * windStrength;

    float bendFactor = smoothstep(0.0, 1.0, pos.y);

    float rotationAngle = r * 3.14159265 * 2.0; 
    mat4 rotationMatrix = constructRotationMatrixY(rotationAngle);

    vec3 rotatedPos = (rotationMatrix * vec4(pos, 1.0)).xyz;

    float scaleFactor = r * 0.5 + 0.5; // Random scale between 0.8 and 1.0
    vec3 scaledPos = rotatedPos * scaleFactor;

    vec3 displacedPos = scaledPos + vec3(sway * bendFactor, 0.0, 0.0);
    displacedPos.xz += offset;

    gl_Position = vec4(displacedPos, 1.0) * uWorldTransform * uViewProj;
    fragTexCoord = texCoord;
}