#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out VS_OUT {
    vec2 texCoord;
    vec3 worldPos;
} vs_out;

void main()
{
    vec4 world = uWorldTransform * vec4(pos, 1.0);
    vs_out.worldPos = world.xyz;
    vs_out.texCoord = texCoord;
    gl_Position = uViewProj * world;
}
