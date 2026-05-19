#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh() = default;
	Mesh(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices);
	~Mesh();
	void init(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices);
	void Draw();
private:
	GLuint VAO, VBO, EBO;
	GLsizei vertexCount;
	GLsizei indexCount;
};



