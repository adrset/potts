#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec2 position;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) + vec4(position.x, position.y, 0, 0);
}
