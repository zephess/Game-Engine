#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Registry.h"
class EnemyManager;
struct placedCube {
	Transforms transform;
	int materialIndex;
};

class World
{
public:
	std::vector<placedCube> cubes;

	void placeBlock(const glm::vec3& position, int materialIndex);
	void removeBlock(const glm::vec3& position);
	void render(Renderer& renderer, Shader& shader, Mesh& cubeMesh, std::vector<Material>& mats);
	void renderGridLines(Renderer& renderer, Shader& shader, const std::vector<glm::vec3>& gridLines, GLuint gridVAO);
	void renderUI(Renderer& renderer, Shader* shader,  std::vector<Material>& blockMats, int selectedBlock, Mesh& uiQuadMesh);
	void saveWorld(const std::string& path);
	void loadWorld(const std::string& path, const std::vector<Material> blockMats);

	std::vector<placedCube> getCubeList() { return cubes; }
		
	
};

