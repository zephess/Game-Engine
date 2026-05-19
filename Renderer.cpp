#include "Renderer.h"

#include <iostream>
void Renderer::init() {
	// Enable back-face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::startRendering(Camera& camera, Shader& shader) {
	// Set view and projection matrices
	shader.Use();
	shader.setMat4("uView", camera.getViewMatrix());
	shader.setMat4("uProjection", camera.getProjectionMatrix());
	
}

void Renderer::drawMesh(Mesh& mesh, Transforms& transform, Shader& shader, Material& material) {
	
	GLint currentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	
	// Set model matrix
	shader.setMat4("uModel", transform.getModelMatrix());
	// Bind texture and set material properties
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.textureID);
	shader.setFloat("uMetalness", material.metalness);
	shader.setFloat("uRoughness", material.roughness);
	shader.setFloat("uSpecular",material.specular);
	shader.setFloat("uEmissive", material.emissive);
	shader.setInt("uTexture", 0);
	mesh.Draw();
}

void Renderer::stopRendering() {
	// Any cleanup if necessary
}
