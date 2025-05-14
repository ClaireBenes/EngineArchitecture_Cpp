#version 450 core

layout(triangles, fractional_even_spacing, cw) in;

in TESC_OUT {
    vec2 texCoord;
    vec3 worldPos;
} tese_in[];

out TESE_OUT {
    vec2 texCoord;
} tese_out;

uniform sampler2D uNoiseTex;
uniform float uTime;
uniform float uWaveStrength;
uniform float uRippleStrength;
uniform float uRippleInterp;
uniform mat4 uViewProj;

vec2 interpolate2D(vec2 a, vec2 b, vec2 c)
{
    return gl_TessCoord.x * a +
           gl_TessCoord.y * b +
           gl_TessCoord.z * c;
}

vec3 interpolate3D(vec3 a, vec3 b, vec3 c)
{
    return gl_TessCoord.x * a +
           gl_TessCoord.y * b +
           gl_TessCoord.z * c;
}

void main()
{
    vec2 texCoord = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
    vec3 pos = interpolate3D(tese_in[0].worldPos, tese_in[1].worldPos, tese_in[2].worldPos);

    // Sinusoidal wave
    float wave = sin(pos.x * 1.5 + uTime) * cos(pos.z * 1.2 + uTime * 0.5);

    // Noise-based ripples
    float noise = texture(uNoiseTex, texCoord * 4.0 + vec2(uTime * 0.05)).r;

    float displacement = wave * uWaveStrength + noise * uRippleStrength * uRippleInterp;
    pos.y += displacement;

    gl_Position = uViewProj * vec4(pos, 1.0);
    tese_out.texCoord = texCoord;
}
