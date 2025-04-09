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

void main()
{
    int gridSize = 10;
    int x = gl_InstanceID % gridSize;
    int z = gl_InstanceID / gridSize;

    vec2 offset = vec2(float(x), float(z)) * 2.0; // spacing between grass

    float r = rand(float(gl_InstanceID));

    // Basic wind effect using sine wave
    float windStrength = 0.5;
    float sway = sin(time + pos.x * 5.0 + pos.z * 5.0) * windStrength;

    // Use vertex height to affect bend strength (e.g., tip bends more than root)
    float bendFactor = smoothstep(0.0, 1.0, pos.y);

    vec3 displacedPos = pos + vec3(sway * bendFactor, 0.0, 0.0);
    displacedPos.xz += offset;

    gl_Position = vec4(displacedPos, 1.0) * uWorldTransform * uViewProj;
    fragTexCoord = texCoord;
}