#version 450 core

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uTexture;
uniform vec2 uTileSize;

void main()
{
   outColor = texture(uTexture, fragTexCoord * uTileSize);
}