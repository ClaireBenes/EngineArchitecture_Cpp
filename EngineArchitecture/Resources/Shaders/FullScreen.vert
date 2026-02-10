#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 2) in vec2 texCoord;

out vec2 fragTexCoord;

void main()
{
    fragTexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    gl_Position = vec4(pos.xy * 2.0, 0.0, 1.0);
}
