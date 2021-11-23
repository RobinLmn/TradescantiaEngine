#version 330 core

out vec4 FragColor;
in float ourSize;
  
void main()
{
    vec2 weight = (gl_PointCoord - 0.5) * 2;

    float r = sqrt(weight.x * weight.x + weight.y * weight.y);
    float brightness = ourSize / exp(10*r);
    FragColor = vec4(brightness, brightness, brightness, 1.0);
}