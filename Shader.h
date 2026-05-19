#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Use();
	GLuint getProgramID() const { return programID; }
	void setMat4(const std::string& name, const glm::mat4& mat);
	void setInt(const std::string& name, int value);
	void setVec3(const std::string& name, const glm::vec3& vec);
	void setFloat(const std::string& name, float value);

private:
	GLuint programID;
	GLuint compileShader(const std::string& source, GLenum shaderType);
	std::string loadFile(const std::string& path);
	
};

