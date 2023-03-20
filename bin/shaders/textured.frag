// A textured shader 
#version 410

in vec2 vTextCoord;

uniform sampler2D diffuseTexture;

out vec4 FragColor;

void main() 
{
    FragColor = texture(diffuseTexture, vTextCoord);
}