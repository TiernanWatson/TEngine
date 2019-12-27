#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 FragNormal;
in vec2 TexCoords;

uniform uint numPointLights;
uniform float ambientStrength;

uniform vec3 eyePos;

uniform sampler2D texDiffuse0;
uniform sampler2D texDiffuse1;
uniform sampler2D texDiffuse2;
uniform sampler2D texSpecular0;
uniform sampler2D texNormal0;
uniform sampler2D texHeight0;

struct PointLight
{
	vec3 pos;
	vec3 color;
	float intensity;
	float range;
};

void getPLContribution(PointLight p, inout vec4 result)
{
	// Ambient
	vec4 ambient = 0.2 * p.intensity * vec4(p.color, 1.0) * texture(texDiffuse0, TexCoords);
	
	// Diffuse
	vec3 lightDir = normalize(p.pos - FragPos);
	float diffStr = max(dot(FragNormal, lightDir), 0.0);
	vec4 diffuse = diffStr * p.intensity * vec4(p.color, 1.0) * texture(texDiffuse0, TexCoords);
	
	// Specular
	vec3 viewDir = normalize(eyePos - FragPos);
    vec3 reflectDir = reflect(-lightDir, FragNormal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = spec * p.intensity * vec4(p.color, 1.0) * texture(texSpecular0, TexCoords); 
	
	result = ambient + diffuse + specular;
}

void main()
{
	PointLight p = PointLight(vec3(0.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), 2.0, 20.0);
	
	vec4 result;
	getPLContribution(p, result);
	FragColor = result;
}