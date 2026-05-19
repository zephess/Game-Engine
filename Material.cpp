#include "Material.h"

Material::Material(Texture* texture) : textureID(texture->id)
{
	// Textured material
	useColourOnly = false;
}

Material::Material(const glm::vec3& colour)
{
	// Colour only material
	useColourOnly = true;
	this->colour = colour;
	// Create a 1x1 texture with the given colour
	unsigned char data[3] = {
		static_cast<unsigned char>(colour.r * 255),
		static_cast<unsigned char>(colour.g * 255),
		static_cast<unsigned char>(colour.b * 255)
	};
	// Generate OpenGL texture and bind data
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

