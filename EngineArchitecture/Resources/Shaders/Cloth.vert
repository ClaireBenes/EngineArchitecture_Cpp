#version 330 core

layout(location = 0) in vec4 pos;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

void main()
{
   gl_Position = pos * uWorldTransform * uViewProj;
   gl_PointSize = 100.0 / gl_Position.z;
}
