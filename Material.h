#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Shader.h"
#include "Texture.h"
class Material
{
public:
	GLuint textureID = 0;
	float roughness = 0;
	float metalness = 0;
	float specular = 0;
	float emissive = 0;

	bool useColourOnly = false;
	glm::vec3 colour = glm::vec3(1.0f);

	Material() = default;
	Material(const glm::vec3& colour);
	Material(Texture* texture);

	
};

class DiffuseMaterial : public Material{
public:
	DiffuseMaterial(Texture* texture) : Material(texture) {
		roughness = 1.0f;
		metalness = 0.0f;
		specular = 0.0f;
		emissive = 0.0f;
	}
};

class MetallicMaterial : public Material {
	public:
	MetallicMaterial(Texture* texture) : Material(texture) {
		roughness = 0.2f;
		metalness = 1.0f;
		specular = 1.0f;
		emissive = 0.0f;
	}
};

class EmissiveMaterial : public Material {
	public:
	EmissiveMaterial(Texture* texture) : Material(texture) {
		roughness = 1.0f;
		metalness = 0.0f;
		specular = 0.0f;
		emissive = 1.0f;
	}
};

