#include "EnemyManager.h"
#include <iostream>
//////////////////////////////
// 
// OBSOLETE CLASS - EnemyManager now uses ECS architecture
// NEED TO REWORK ENEMY SAVE SYSTEM TO USE REGISTRY AND COMPONENTS
// 
//////////////////////////////
void EnemyManager::spawnEnemy(const glm::vec3& position) {
	Enemy newEnemy;
	newEnemy.transform.position = position;
	newEnemy.transform.scale = glm::vec3(0.8f, 0.9f, 0.8f);
	newEnemy.transform.rotation = glm::vec3(0.0f);
	newEnemy.transform.localPosition = glm::vec3(0.0f);
	newEnemy.velocity = glm::vec3(0.0f);
	newEnemy.speed = 2.0f;
	newEnemy.width = 0.8f;
	newEnemy.height = 0.9f;
	newEnemy.grounded = false;
	newEnemy.movingRight = true;
	enemies.push_back(newEnemy);
}


void EnemyManager::renderEnemies(Renderer& renderer, Shader& shader, Mesh& cubeMesh, Material& enemyMaterial) {
	for (auto& enemy : enemies) {
		renderer.drawMesh(cubeMesh, enemy.transform, shader, enemyMaterial);
	}
}

void EnemyManager::saveEnemies(std::ofstream& file) {
	file << "ENEMIES : " << enemies.size() << "\n";
	for (const auto& enemy : enemies) {
		file << enemy.transform.position.x << " "
			<< enemy.transform.position.y << " "
			<< enemy.transform.position.z << "\n";
	}
	std::cout << "Saved " << enemies.size() << " enemies.\n";
}

void EnemyManager::loadEnemies(std::ifstream& file, size_t count) {
	enemies.clear();
	for(size_t i = 0; i < count; ++i) {
		Enemy enemy;
		file >> enemy.transform.position.x
			 >> enemy.transform.position.y
			 >> enemy.transform.position.z;
		enemy.transform.scale = glm::vec3(0.8f, 0.9f, 0.8f);
		enemy.transform.rotation = glm::vec3(0.0f);
		enemy.transform.localPosition = glm::vec3(0.0f);
		enemy.velocity = glm::vec3(0.0f);
		enemy.speed = 2.0f;
		enemy.width = 0.8f;
		enemy.height = 0.9f;
		enemy.grounded = false;
		enemy.movingRight = true;
		enemies.push_back(enemy);
	}
	std::cout << "Loaded " << enemies.size() << " enemies.\n";
}