#version 330 core

in vec3 ex_Color;
out vec4 FragColor;

void main()
{
	FragColor = vec4(ex_Color,1.0);
}