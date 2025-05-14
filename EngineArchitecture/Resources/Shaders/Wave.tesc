#version 450 core

layout(vertices = 3) out;

in VS_OUT {
    vec2 texCoord;
    vec3 worldPos;
} tesc_in[];

out TESC_OUT {
    vec2 texCoord;
    vec3 worldPos;
} tesc_out[];

void main()
{
    // Pass through
    tesc_out[gl_InvocationID].texCoord = tesc_in[gl_InvocationID].texCoord;
    tesc_out[gl_InvocationID].worldPos = tesc_in[gl_InvocationID].worldPos;
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 4.0;
        gl_TessLevelOuter[0] = 8.0;
        gl_TessLevelOuter[1] = 8.0;
        gl_TessLevelOuter[2] = 8.0;
    }
}
