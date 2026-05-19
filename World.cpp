#include "World.h"
#include <fstream>
#include <iostream>
#include "EnemyManager.h"
void World::placeBlock(const glm::vec3& position, int materialIndex) {
	// Check if a block already exists at the position
	for (const auto& cube : cubes) {
		if (cube.transform.position == position) {
			// Block already exists, do not place another
			return; 
		}
	}
	// Place new block
	placedCube newCube;
	// Initialize transform
	newCube.transform.position = position;
	newCube.transform.scale = glm::vec3(1.0f);
	newCube.transform.rotation = glm::vec3(0.0f);
	// Set material index
	newCube.materialIndex = materialIndex;
	// Add to world
	cubes.push_back(newCube);

}

void World::removeBlock(const glm::vec3& position) {
	// Find and remove block at the position
	for(auto it = cubes.begin(); it != cubes.end(); ++it) {
		if(it->transform.position == position) {
			cubes.erase(it);
			return;
		}
	}
}

// Render all cubes in the world
void World::render(Renderer& renderer, Shader& shader, Mesh& cubeMesh, std::vector<Material>& mats) {
	for(auto& cube : cubes) {
		renderer.drawMesh(cubeMesh, cube.transform, shader, mats[cube.materialIndex]);
	}
}

// Render grid lines for the editor
void World::renderGridLines(Renderer& renderer, Shader& shader, const std::vector<glm::vec3>& gridLines, GLuint gridVAO) {

	shader.setFloat("uMetalness", 0.0f);
	shader.setFloat("uRoughness", 1.0f);
	shader.setFloat("uSpecular", 0.0f);
	shader.setFloat("uEmissive", 0.0f);
	glBindVertexArray(gridVAO);
	glDrawArrays(GL_LINES, 0, gridLines.size());
	glBindVertexArray(0);
	glDisable(GL_DEPTH_TEST);
	
}

void World::renderUI(Renderer& renderer, Shader* shader, std::vector<Material>& blockMats, int selectedBlock, Mesh& uiQuadMesh){
	// Render UI block selection
	// Setup orthographic projection
	glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	shader->setMat4("uProjection", ortho);
	shader->setMat4("uView", glm::mat4(1.0f));

	// Calculate positions for block slots
	float slotSize = 64.0f;
	float spacing = 16.0f;
	float startX = (800 - (blockMats.size() * (slotSize + spacing))) * 0.5f;
	float y = 60.0f;

	// Hardcoded again to ignore last material (enemy material)
	for (int i = 0; i < blockMats.size()-1; i++) {
		// Calculate transform for each slot
		Transforms t;
		t.position = glm::vec3(startX + i * (slotSize + spacing), y, 0);
		t.scale = glm::vec3(slotSize, slotSize, 1);
		t.rotation = glm::vec3(0.0f);

		// Draw outline if selected
		// slightly larger quad behind
		Transforms outline = t;
		outline.scale *= 1.1f;
		outline.position.z = -0.1f; 
		outline.rotation = glm::vec3(0.0f);
		shader->setInt("uOutline", (i == selectedBlock) ? 1 : 0);
		renderer.drawMesh(uiQuadMesh, outline, *shader, blockMats[i]);

		shader->setInt("uOutline", 0);
		renderer.drawMesh(uiQuadMesh, t, *shader, blockMats[i]);


	}
}

// Save world data to a file
void World::saveWorld(const std::string& path) {
	// Debug output
	std::cout << "Saving world to " << path << " with " << cubes.size() << " cubes.\n";
	// Open file for writing
	std::ofstream file(path);
	// Sanity check
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + path);
	}

	// Write header
	file << "WorldData\n";
	// Write cube count
	file << "CUBES : " << cubes.size() << "\n";
	// Write each cube's data
	for (const auto& cube : cubes) {
		file << cube.transform.position.x << " "
			<< cube.transform.position.y << " "
			<< cube.transform.position.z << " "
			<< cube.materialIndex << "\n";


	}
	// Debug output
	std::cout << "World saved successfully.\n";
	// Close file
	file.close();
}

// Load world data from a file
void World::loadWorld(const std::string& path, const std::vector<Material> blockMats) {
	// Debug output
	std::cout << "Loading world from " << path << "\n";
	// Open file for reading
	std::ifstream file(path);
	// Sanity check
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for reading: " + path);
	}

	// Read header
	std::string header;
	file >> header;
	// Sanity check
	if (header != "WorldData") {
		throw std::runtime_error("Invalid world file header: " + header);
	}

	// Read cube count
	std::string cubesLabel;
	char colon;
	size_t cubeCount;

	// Reads: CUBES: <count>
	file >> cubesLabel >> colon >> cubeCount;
	// Sanity check
	if (cubesLabel != "CUBES" || colon != ':') {
		throw std::runtime_error("Invalid CUBES line in world file");
	}

	// Clear existing cubes
	cubes.clear();
	// Reserve space for new cubes
	cubes.reserve(cubeCount);

	// Read each cube's data
	for (size_t i = 0; i < cubeCount; ++i) {
		float x, y, z;
		int matIndex;
		// Sanity check
		if (!(file >> x >> y >> z >> matIndex)) {
			throw std::runtime_error("Failed to read cube position at index " + std::to_string(i));
		}

		// Create and initialize cube
		placedCube cube;
		// Initialize transform
		cube.transform.position = glm::vec3(x, y, z);
		cube.transform.scale = glm::vec3(1.0f);
		cube.transform.rotation = glm::vec3(0.0f);

		// Validate material index
		if (matIndex < 0 || matIndex >= (int)blockMats.size()) {
			matIndex = 0; // Default to first material if out of range
		}
		// Set material index
		cube.materialIndex = matIndex;
		// Add cube to world
		cubes.push_back(cube);
	}

	// Debug output
	std::cout << "World loaded successfully with " << cubes.size() << " cubes.\n";
	// Close file
	file.close();
}