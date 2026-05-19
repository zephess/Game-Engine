#pragma once
#include "Entity.h"
#include "ComponentStorage.h"
#include <vector>

class Registry {
public:
	// Create a new entity and return its ID
	Entity createEntity() { return nextEntity++; }

	// Get a list of all entities
	std::vector<Entity> getAllEntities() {
		// Implementation to return all entities
		std::vector<Entity> entities;
		// This is a placeholder implementation. In a real implementation, you would track created entities.
		for (Entity e = 1; e < nextEntity; ++e) {
			entities.push_back(e);
		}
		return entities;
	}

	// Add a component of type T to an entity
	template<typename T>
	void addComponent(Entity entity, const T& component) {
		getStorage<T>().addComponent(entity, component);
		// Implementation to add component to the entity
	}

	// Check if an entity has a component of type T
	template<typename T>
	bool hasComponent(Entity entity) {
		return getStorage<T>().hasComponent(entity);
		// Implementation to check if entity has component T
	}

	// Get a reference to the component of type T for an entity
	template<typename T>
	T& getComponent(Entity entity) {
		return getStorage<T>().getComponent(entity);
		// Implementation to get component T of the entity
	}

	// Get the storage for component type T
	template<typename T>
	ComponentStorage<T>& getStorage() {
		static ComponentStorage<T> storage;
		return storage;
	}

private:
	// Next available entity ID
	Entity nextEntity = 0;
};