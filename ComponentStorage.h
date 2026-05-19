#pragma once
#include <unordered_map>
#include "Entity.h"
#include <glm/glm.hpp>
template<typename T>
class ComponentStorage {
public:
	// Map of entity to component
	std::unordered_map<Entity, T> components;
	// Add component to entity
	void addComponent(Entity entity, const T& component) {
		components[entity] = component;
	}
	// Check if entity has component
	bool hasComponent(int entity) {
		return components.find(entity) != components.end();
	}
	// Get component of entity
	T& getComponent(int entity) {
		return components[entity];
	}

};

