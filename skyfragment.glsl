#version 330 core

out vec4 FragColor;
in vec3 vDirection;

uniform float uTime;

uniform vec3 topColor;
uniform vec3 bottomColor;
uniform float waveAmplitude;

void main()
{
	float t = normalize(vDirection).y * 0.5 + 0.5;

	float wave = sin(uTime * 0.4) * waveAmplitude;

	vec3 top = topColor + wave;
	vec3 bottom = bottomColor + wave;

	vec3 color = mix(bottom, top, t);
	FragColor = vec4(color, 1.0);
}