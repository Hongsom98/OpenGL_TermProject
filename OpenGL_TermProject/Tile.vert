#version 330 core

layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Normal;

out vec3 FragPos; //--- 객체의 위치값을 프래그먼트 세이더로 보낸다.
out vec3 Normal; //--- 노멀값을 프래그먼트 세이더로 보낸다.

uniform mat4 Model; //--- 모델링 변환값
uniform mat4 View; //--- 뷰잉 변환값
uniform mat4 Projection; //--- 투영 변환값

void main()
{
	gl_Position = Projection * View * Model * vec4(in_Pos, 1.0);
	FragPos = vec3(Model * vec4(in_Pos, 1.0));
	Normal = in_Normal;
}