#pragma once
#include <GL/glew.h>


class Texture
{
public:
	GLuint id;
	Texture() = default;
	Texture(const char* filePath);
	~Texture();
	
};

