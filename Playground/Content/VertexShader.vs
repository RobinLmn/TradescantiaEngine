#version 450 core

out vec4 myColor;
uniform mat4 u_ViewProjection;

struct particle_data 
{
  vec4 pos;
  vec4 color;
  vec4 force;
};

layout(std430, binding = 0) readonly buffer ParticleBuffer
{
    particle_data data[];
} particles;

void main()
{
  gl_Position = u_ViewProjection * particles.data[gl_InstanceID].pos;
  myColor = particles.data[gl_InstanceID].color;
}
