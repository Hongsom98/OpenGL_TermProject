#version 330 core

layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_TexCoord;

out vec3 FragPos; 
out vec3 Normal; 
out vec2 TexCoord;

uniform mat4 Model; 
uniform mat4 View; 
uniform mat4 Projection; 

uniform sampler2D outTexture;

void main()
{
	gl_Position = Projection * View * Model * vec4(in_Pos, 1.0);
	FragPos = vec3(Model * vec4(in_Pos, 1.0));
	Normal = in_Normal;
	TexCoord = in_TexCoord;
}