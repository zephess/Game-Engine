#version 330 core

in vec3 vColour;
in vec2 vUV;
in vec3 vNormal;
in vec3 vFragPos;


uniform int uOutline;
uniform sampler2D uTexture;

struct DirectionalLight {
	vec3 direction;
	vec3 colour;
};

uniform DirectionalLight uLight;
uniform vec3 uViewPos;

uniform int uUseColour;
uniform vec3 uColour;

uniform float uRoughness;
uniform float uMetalness;
uniform float uSpecular;
uniform float uEmissive;

out vec4 FragColour;

void main()
{
	if(uUseColour == 1)
	{
		FragColour = vec4(uColour, 1.0);
		return;
	}

	if(uOutline == 1)
	{
		FragColour = vec4(vColour, 1.0);
		return;
	}
	
	vec3 tex = texture(uTexture, vUV).rgb;

	float diff = max(dot(normalize(vNormal), normalize(uLight.direction)), 0.0);

	vec3 viewDir = normalize(uViewPos - vFragPos);
	vec3 halfwayDir = normalize(uLight.direction + viewDir);
	float spec = pow(max(dot(normalize(vNormal), halfwayDir), 0.0), mix(8.0, 128.0, 1.0 - uRoughness));

	vec3 specColour = mix(vec3(1.0), tex, uMetalness);

	vec3 lighting = tex * diff * specColour + spec * uSpecular + tex * uEmissive;

	FragColour = vec4(lighting, 1.0);
}