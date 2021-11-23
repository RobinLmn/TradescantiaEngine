#version 330 core

layout (location = 0) in vec3 aPos;   
layout (location = 1) in float aSize;

uniform mat4 u_ViewProjection;

out float ourSize;

void main()
{
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
    ourSize = aSize;
}
