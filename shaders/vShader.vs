#version 330 core
layout (location = 0) in vec3 vertex;  
layout (location = 1) in vec2 texcord;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;


void main()
{

gl_Position =projection*model* vec4(vertex, 1.0f);

texCoords = texcord;
}