#version 450 core

layout(triangles, fractional_even_spacing, cw) in;

in TESC_OUT{ vec2 texCoord; } tese_in[];
out TESE_OUT { vec2 texCoord; float displacement; } tese_out;

uniform float uTime;
uniform float uSpeed;
uniform float uFrequency;
uniform float uAmplitude;
uniform float uDisplacement;

uniform sampler2D uNoiseTex;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2) {
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2) {
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

void main(void) {
    vec2 uv = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
    vec4 pos = interpolate4D(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);


    float noise = texture(uNoiseTex, uv * 10.0).r;
    float wave = sin((uv.x * uFrequency - uTime * uSpeed)) * (uAmplitude * noise);
    wave *= mix(0.8, 1.2, noise);

    pos.y += wave * uDisplacement ;

    gl_Position = pos;
    tese_out.texCoord = uv;
    tese_out.displacement = clamp(wave * uDisplacement + 0.3, 0.0, 1.0);
}
