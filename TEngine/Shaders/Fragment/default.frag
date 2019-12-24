#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}