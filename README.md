# TradescantiaEngine

## Info

Tradescantia Engine is a 3D generalist Game Engine, currently optimized for particle simulation. Interesting files can be consulted here:
  - Engine Loop: https://github.com/RobinLmn/TradescantiaEngine/blob/main/TradescantiaEngine/Source/Core/Engine.cpp
  - Scene and Rendering: https://github.com/RobinLmn/TradescantiaEngine/blob/main/TradescantiaEngine/Source/Scene/Scene.cpp
  - Particle Simulation: https://github.com/RobinLmn/TradescantiaEngine/blob/main/TradescantiaEngine/Source/Systems/ParticleSystem.cpp

The engine can render and simulate up to 6k particles on the CPU with multithreading. The next step of the project is to run the simulation on the GPU. The integration is done with the Semi Implicit Euler method.

The rendering is done with OpenGL, Tracy is used as the profiler, ImGUI for the UI and spdlog for logging. Special thanks to The Cherno's "Game Engine" series that helped me a lot throughout the process.

## Demo

A demo can be consulted here: https://youtu.be/Vba1tp6Ombk

![Particle Simulation - Disk Shaped](https://user-images.githubusercontent.com/55120018/148679750-3db6aeb2-f3c9-4383-abe1-fe911b2d9be4.png)
