#version 330 core

layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Color;

out vec3 ex_Color;

uniform mat4 Model;

void main()
{
	gl_Position = Model * vec4(in_Pos, 1.0);
	ex_Color = in_Color;
}