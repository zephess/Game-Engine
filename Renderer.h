#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "Components.h"
class Renderer
{
public:
	Renderer() = default;
	void init();
	void startRendering(Camera& camera, Shader& shader);
	void drawMesh(Mesh& mesh, Transforms& transform, Shader& shader, Material& material);
	void stopRendering();
	
};

