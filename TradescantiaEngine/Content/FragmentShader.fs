#version 330 core

out vec4 FragColor;
in float ourSize;
  
void main()
{
    FragColor = vec4(ourSize,ourSize,ourSize, 1.0);
}