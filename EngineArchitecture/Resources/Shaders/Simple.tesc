#version 450 core

layout(vertices = 3) out;

in VS_OUT{ vec2 texCoord; } tesc_in[];
out TESC_OUT{ vec2 texCoord; } tesc_out[];

void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 5.0f;
        gl_TessLevelInner[1] = 7.0;
        gl_TessLevelOuter[0] = 5.0f;
        gl_TessLevelOuter[1] = 5.0f;
        gl_TessLevelOuter[2] = 5.0f;
        gl_TessLevelOuter[3] = 5.0;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tesc_out[gl_InvocationID].texCoord = tesc_in[gl_InvocationID].texCoord;
}
