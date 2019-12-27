#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTextCoord;

out vec3 FragPos;
out vec3 FragNormal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
	//FragNormal = vec3(model * vec4(normalize(aNormal), 1.0));
	FragNormal = normalize(mat3(model) * aNormal);
	TexCoords = aTextCoord;
	gl_Position = projection * view * vec4(FragPos, 1.0);
}