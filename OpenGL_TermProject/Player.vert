#version 330

in vec3 in_Position;
uniform vec3 in_Color;

uniform mat4 Model;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
out vec3 ex_Color;

void main()
{
	
	gl_Position = projectionTransform * viewTransform * Model * vec4(in_Position, 1.0);

	ex_Color = in_Color;

}