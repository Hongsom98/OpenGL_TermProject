#version 330 core

in vec3 ex_Color;

out vec4 FragColor;

uniform float Alpha; 

void main ()
{
	FragColor = vec4 (ex_Color, Alpha); 
}

