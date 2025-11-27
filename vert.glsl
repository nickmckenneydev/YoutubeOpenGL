#version 410 core
layout(location = 0) in vec3 position; // Note: vec3 to match your C++ float array

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}