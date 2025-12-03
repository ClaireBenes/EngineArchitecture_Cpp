#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 velocity;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec4 color;

void main()
{
   gl_Position = pos * uWorldTransform * uViewProj;
   gl_PointSize = 100.0 / gl_Position.z;

   color = mix(vec4(1, 1, 1, 1), vec4(1, 1, 1, 0.4), clamp(length(velocity.xyz) / 10, 0, 1));
}
