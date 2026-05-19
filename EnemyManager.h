#pragma once
#include "Transform.h"
#include "World.h"
#include <vector>
#include <glm/glm.hpp>
#include "Collision.h"
#include <fstream>

struct Enemy {
	Transforms transform;
	glm::vec3 velocity;
	float speed;
	float width;
	float height;
	bool grounded;
	bool movingRight;
};

class EnemyManager
{
public:
	EnemyManager() = default;
	void spawnEnemy(const glm::vec3& position);
	
	void renderEnemies(Renderer& renderer, Shader& shader, Mesh& cubeMesh, Material& enemyMaterial);
	void saveEnemies(std::ofstream& file);
	void loadEnemies(std::ifstream& file, size_t count);
	std::vector<Enemy> enemies;
private:

};

