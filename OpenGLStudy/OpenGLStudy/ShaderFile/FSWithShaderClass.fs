#version 330 core
out vec4 FragColor;

uniform float someUniform;

void main()
{
    FragColor = vec4(someUniform, 0.0, 0.0, 1.0);
}