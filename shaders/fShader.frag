#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D ourTexture;
uniform vec4 textureColor;

void main()
{
 vec2 texCoord = vec2(texCoords.x, 1.0f - texCoords.y);

  color =vec4(textureColor) *texture(ourTexture, texCoord);
}