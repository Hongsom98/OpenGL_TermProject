#version 330 core

layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Normal;

out vec3 FragPos; //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 Normal; //--- ��ְ��� �����׸�Ʈ ���̴��� ������.

uniform mat4 Model; //--- �𵨸� ��ȯ��
uniform mat4 View; //--- ���� ��ȯ��
uniform mat4 Projection; //--- ���� ��ȯ��

void main()
{
	gl_Position = Projection * View * Model * vec4(in_Pos, 1.0);
	FragPos = vec3(Model * vec4(in_Pos, 1.0));
	Normal = in_Normal;
}