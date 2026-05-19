#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Material.h"
#include "Entity.h"
#include <vector>

struct Transforms {
	// World position
    glm::vec3 position{ 0.0f };  
	// Local position relative to parent
    glm::vec3 localPosition{ 0.0f };  
	// Rotation in radians
    glm::vec3 rotation{ 0.0f };
	// Scale
    glm::vec3 scale{ 1.0f };
	// Initial spawn position
	glm::vec3 initialPosition{ 0.0f };
	// Compute model matrix from position, rotation, and scale
    glm::mat4 getModelMatrix() const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
        model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
        model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
        model = glm::scale(model, scale);
        return model;
    }
};

struct Velocity {
	// Velocity vector
    glm::vec3 velocity{ 0.0f };
};

struct Input {
	// Movement input vector
    glm::vec3 move{ 0.0f };
	// Jump action
    bool jump = false;
};

// Renderable component linking to mesh and material
struct Renderable {
    Mesh* mesh = nullptr;
    Material* material = nullptr;
};

// Tag components for identifying entity types
struct PlayerTag {};
struct EnemyTag {};

// Physics body component for movement and collision
struct PhysicsBody {
    glm::vec3 velocity{ 0.0f };
    bool grounded{ false };
    float mass{ 1.0f };
    int direction{ 1 };
	// Half-size for AABB collision
	glm::vec3 halfSize{ 0.5f, 0.5f, 0.5f };
};

// Parent component to establish hierarchy
struct Parent {
    Entity parent;
};
// ChildList component to hold child entities
struct ChildList {
    std::vector<Entity> children;
};