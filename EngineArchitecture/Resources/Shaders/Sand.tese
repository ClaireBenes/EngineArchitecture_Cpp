#version 450 core

layout(triangles, fractional_even_spacing, cw) in;

in TESC_OUT{ vec2 texCoord; } tese_in[];
out TESE_OUT { vec2 texCoord; } tese_out;

uniform float uDisplacementStrength;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2)
{
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

float computeHeight(vec2 uv)
{
    // Simple pseudo bumpiness using sin/cos
    float height = sin(uv.x * 10.0) * cos(uv.y * 10.0);
    return height;
}

void main(void)
{
    vec2 uv = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
    vec4 pos = interpolate4D(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);

    float height = computeHeight(uv) * uDisplacementStrength;

    // Apply height displacement along Y axis
    pos.y += height;

    gl_Position = pos;
    tese_out.texCoord = uv;
}
