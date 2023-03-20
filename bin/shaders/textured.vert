// Our textured shhader
#version 410
layout(location = 0) in vec4 Position;
layout(location = 2) in vec2 TexCoord;

out vec2 vTextCoord;

uniform mat4 ProjectionViewModel;

void main() 
{
    vTextCoord = TexCoord;
    gl_Position = ProjectionViewModel * Position;
}