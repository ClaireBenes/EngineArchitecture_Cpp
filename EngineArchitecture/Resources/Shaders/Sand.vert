#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec2 uTileSize;

out VS_OUT{ vec2 texCoord; } vs_out;

void main()
{
   gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
   vs_out.texCoord = texCoord * uTileSize;
}
