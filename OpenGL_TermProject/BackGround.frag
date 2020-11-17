#version 330 core

in vec3 FragPos; //--- 노멀값을 계산하기 위해 객체의 위치값을 버텍스 세이더에서 받아온다.
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

uniform float Alpha; // 알파블렌딩을 하기 위하여 필요한 Alpha값

void main ()
{
	float ambientLight = 0.3; //--- 주변 조명 세기
	vec3 ambient = ambientLight * lightColor; //--- 주변 조명 값
	vec3 normalVector = normalize (Normal);
	vec3 lightDir = normalize (lightPos - FragPos); //--- 표면과 조명의 위치로 조명의 방향을 결정한다.
	float diffuseLight = max (dot (normalVector, lightDir), 0.0); //--- N과 L의 내적 값으로 강도 조절: 음수 방지
	vec3 diffuse = diffuseLight * lightColor; //--- 산란 반사 조명값: 산란반사값 * 조명색상값

	int shininess = 128; //--- 광택 계수
	vec3 viewDir = normalize (viewPos - FragPos); //--- 관찰자의 방향
	vec3 reflectDir = reflect (-lightDir, normalVector); //--- 반사 방향: reflecct 함수 - 입사 벡터의 반사 방향 계산
	float specularLight = max (dot (viewDir, reflectDir), 0.0); //--- V와 R의 내적값으로 강도 조절: 음수 방지
	specularLight = pow(specularLight, shininess); //--- shininess 승을 해주어 하이라이트를 만들어준다.
	vec3 specular = specularLight * lightColor; //--- 거울 반사 조명값: 거울반사값 * 조명색상값
	
	vec3 result = (ambient + diffuse + specular) * objectColor; //--- 최종 조명 설정된 픽셀 색상: (주변+산란반사+거울반사조명)*객체 색상
	
	FragColor = vec4 (result, Alpha); // --- 픽셀 색을 출력
}

