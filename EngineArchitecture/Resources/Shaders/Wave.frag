#version 330 core

in TESE_OUT{ vec2 texCoord; float displacement; } frag_in;
out vec4 outColor;

uniform vec4 uColor;        // 43B6DB (base)
uniform vec4 uSecondColor;  // D8FFFF (highlight)

void main()
{
    // Blend based on displacement factor (could use fresnel or lighting later)
    float t = clamp(frag_in.displacement, 0.0, 1.0);
    outColor = mix(uColor, uSecondColor, t);
}
