#version 450 core

in TESE_OUT {
    vec2 texCoord;
} frag_in;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
    vec3 baseColor = texture(uTexture, frag_in.texCoord).rgb;
    outColor = vec4(baseColor, 1.0);
}
