#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	// Load and compile shaders
	std::string vertexCode = loadFile(vertexPath);
	std::string fragmentCode = loadFile(fragmentPath);
	GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	std::cout << "Created Shader Program ID: " << programID << std::endl;
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		throw std::runtime_error(std::string("Shader Program Linking Failed: ") + infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	// Cleanup
	glDeleteProgram(programID);
}

void Shader::Use() {
	// Activate the shader program
	glUseProgram(programID);
	GLint currentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
}

GLuint Shader::compileShader(const std::string& source, GLenum shaderType) {
	// Compile individual shader
	GLuint shader = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		throw std::runtime_error(std::string("Shader Compilation Failed: ") + infoLog);
	}
	return shader;
}

// Load shader source code from file
std::string Shader::loadFile(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open shader file: " + path);
	}
	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Uniform setters
// Set 4x4 matrix uniform
void Shader::setMat4(const std::string& name, const glm::mat4& mat) {
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
}
// Set integer uniform
void Shader::setInt(const std::string& name, int value) {
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniform1i(loc, value);
}
// Set vec3 uniform
void Shader::setVec3(const std::string& name, const glm::vec3& vec) {
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniform3fv(loc, 1, &vec[0]);
}
// Set float uniform
void Shader::setFloat(const std::string& name, float value) {
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniform1f(loc, value);
}
