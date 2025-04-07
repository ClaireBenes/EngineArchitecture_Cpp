#version 330

in TESE_OUT{ vec2 texCoord; } frag_in;
out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
   outColor = texture(uTexture, frag_in.texCoord);
}
