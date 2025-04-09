#version 450 core

layout(location = 0) in vec3 pos;        
layout(location = 2) in vec2 texCoord;   

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform float time;

out vec2 fragTexCoord;

void main()
{
    // Basic wind effect using sine wave
    float windStrength = 0.5;
    float sway = sin(time + pos.x * 5.0 + pos.z * 5.0) * windStrength;

    // Use vertex height to affect bend strength (e.g., tip bends more than root)
    float bendFactor = smoothstep(0.0, 1.0, pos.y);

    vec3 displacedPos = pos + vec3(sway * bendFactor, 0.0, 0.0);

    gl_Position = vec4(displacedPos, 1.0) * uWorldTransform * uViewProj;
    fragTexCoord = texCoord;
}