#include "Components.h"
#include "Registry.h"

// System to update entity positions based on their velocities
inline void movementSystem(Registry& registry, float dt) {
	// Get component storages
	auto& transforms = registry.getStorage<Transforms>();
	auto& velocities = registry.getStorage<Velocity>();

	// Update positions
	for (auto& pair : velocities.components) {
		Entity entity = pair.first;
		Velocity& velocity = pair.second;
		if (transforms.hasComponent(entity)) {
			Transforms& transform = transforms.getComponent(entity);
			transform.position += velocity.velocity * dt;
		}
	}
}

// System to handle player input and update Input component
inline void inputSystem(Registry& registry) {
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// Get Input component storage
	auto& inputs = registry.getStorage<Input>();
	// Update Input components based on keyboard state
	for (auto& pair : inputs.components) {
		Entity entity = pair.first;
		Input& input = pair.second;
		glm::vec3 move(0.0f);
		if (state[SDL_SCANCODE_W]) {
			move.y += 1.0f;
		}
		if (state[SDL_SCANCODE_S]) {
			move.y -= 1.0f;
		}
		if (state[SDL_SCANCODE_A]) {
			move.x -= 1.0f;
		}
		if (state[SDL_SCANCODE_D]) {
			move.x += 1.0f;
		}
		input.move = move;
	}
}

// System to control player movement based on Input component
inline void playerControlSystem(Registry& registry, float dt)
{
	// Get component storages
	auto& inputs = registry.getStorage<Input>();
	auto& physicsBodies = registry.getStorage<PhysicsBody>();

	// Get keyboard state
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// Update PhysicsBody based on Input
	for (auto& pair : inputs.components)
	{
		// Get entity and input component
		Entity entity = pair.first;
		Input& input = pair.second;

		// Ensure entity has PhysicsBody component
		if (!physicsBodies.hasComponent(entity)) {
			continue;
		}

		// Get PhysicsBody component
		PhysicsBody& body = physicsBodies.getComponent(entity);

		float speed = 5.0f;

		// Horizontal movement
		body.velocity.x = input.move.x * speed;

		// No Z movement
		body.velocity.z = 0.0f;

		// Jumping
		if (state[SDL_SCANCODE_SPACE] && body.grounded)
		{
			// Apply jump velocity
			body.velocity.y = 7.0f;   
			body.grounded = false;
		}
	}
}

// Simple enemy AI system to move enemies back and forth
inline void enemyAISystem(Registry& registry, float dt)
{
	// Get component storages
	auto& enemyTags = registry.getStorage<EnemyTag>();
	auto& physicsBodies = registry.getStorage<PhysicsBody>();

	// Update enemy movement
	for (auto& pair : enemyTags.components)
	{
		// Get entity
		Entity entity = pair.first;

		// Ensure entity has PhysicsBody component
		if (!physicsBodies.hasComponent(entity)) {
			continue;
		}
		// Get PhysicsBody component
		PhysicsBody& body = physicsBodies.getComponent(entity);

		float speed = 2.0f;

		// Flip direction when physics stops movement
		if (body.velocity.x == 0.0f && body.grounded)
			body.direction *= -1;

		// Move enemy in current direction
		body.velocity.x = body.direction * speed;
	}
}

// System to render all entities with
inline void renderSystem(Registry& registry, Renderer& renderer, Shader& shader) {
	// Get component storages
	auto& renderables = registry.getStorage<Renderable>();
	auto& transforms = registry.getStorage<Transforms>();
	// Render all renderable entities
	for (auto& pair : renderables.components) {
		// Get entity and renderable component
		Entity entity = pair.first;
		Renderable& renderable = pair.second;
		// Ensure entity has Transforms component
		if (!transforms.hasComponent(entity)) {
			continue;
		}
		// Get transform component
		Transforms& transform = transforms.getComponent(entity);
		// Draw the mesh with its transform and material
		renderer.drawMesh(*renderable.mesh, transform, shader, *renderable.material);
	}
	
	
}

// System to make the camera follow the player entity
inline void cameraFollowSystem(Registry& registry, Camera& camera) {
	// Get component storage
	auto& transforms = registry.getStorage<Transforms>();
	// Find player entity and update camera position
	for (auto& pair : transforms.components) {
		// Check if entity is the player
		if (registry.hasComponent<PlayerTag>(pair.first)) {
			// Update camera to follow player
			Transforms& transform = pair.second;
			camera.setPosition(transform.position + glm::vec3(0.0f, 0.0f, 8.0f));
			camera.lookAt(glm::vec3(transform.position.x, transform.position.y, transform.position.z));
			break;
		}
	}
}

// System to handle player stomping on enemies
inline void stompSystem(Registry& registry, Entity entity, glm::vec3 pos, PhysicsBody& body)
{
	// Get component storages
	auto& enemyTags = registry.getStorage<EnemyTag>();
	auto& transforms = registry.getStorage<Transforms>();
	auto& physicsBodies = registry.getStorage<PhysicsBody>();

	// Ensure entity is player
	if (!registry.hasComponent<PlayerTag>(entity)) {
		return;
	}
	// Check for stomping on enemies
	for (auto& pair : enemyTags.components)
	{
		// Get enemy entity
		Entity enemy = pair.first;

		// Ensure enemy has required components
		if (!transforms.hasComponent(enemy) || !physicsBodies.hasComponent(enemy)) {
			continue;
		}
		// Get enemy components
		Transforms& enemyT = transforms.getComponent(enemy);
		PhysicsBody& enemyB = physicsBodies.getComponent(enemy);

		// AABB calculations
		glm::vec3 enemyMin = enemyT.position - enemyB.halfSize;
		glm::vec3 enemyMax = enemyT.position + enemyB.halfSize;

		glm::vec3 playerMin = pos - body.halfSize;
		glm::vec3 playerMax = pos + body.halfSize;

		float playerFeet = pos.y - body.halfSize.y;
		float enemyHead = enemyT.position.y + enemyB.halfSize.y;
		float enemyCenter = enemyT.position.y;

		bool falling = body.velocity.y < 0.0f;

		bool horizontalOverlap = playerMax.x > enemyMin.x && playerMin.x < enemyMax.x && playerMax.z > enemyMin.z && playerMin.z < enemyMax.z;

		// Player feet must be below enemy head 
		// but above enemy center (not hitting from below)
		bool stompWindow = playerFeet <= enemyHead + 0.05f && playerFeet >= enemyCenter;           

		if (falling && horizontalOverlap && stompWindow)
		{
			// Make player bounce
			body.velocity.y = 10.0f;
			return;
		}
	}

}

// Physics system to update entity positions and handle collisions
inline void physicsSystem(Registry& registry, float dt, const std::vector<placedCube>& cubes)
{
	// Get component storages
	auto& transforms = registry.getStorage<Transforms>();
	auto& physicsBodies = registry.getStorage<PhysicsBody>();

	// Update physics bodies
	for (auto& pair : physicsBodies.components)
	{
		// Get entity and physics body
		Entity entity = pair.first;
		PhysicsBody& body = pair.second;

		// Ensure entity has Transforms component
		if (!transforms.hasComponent(entity)) {
			continue;
		}
		// Get transform component
		Transforms& transform = transforms.getComponent(entity);

		// Half-size for AABB collision
		glm::vec3 half = body.halfSize;

		// Apply gravity
		body.velocity.y += -9.81f * dt;
		// Reset grounded state
		body.grounded = false;
		// Get EnemyTag storage for stomp checks
		auto& enemyTags = registry.getStorage<EnemyTag>();
		// Collision detection lambda
		auto collides = [&](const glm::vec3& pos)
		{
			// AABB for testing
			glm::vec3 minP = pos - half;
			glm::vec3 maxP = pos + half;

			// Check cubes
			for (const auto& cube : cubes)
			{
				glm::vec3 cMin = cube.transform.position - glm::vec3(0.5f);
				glm::vec3 cMax = cube.transform.position + glm::vec3(0.5f);

				if (Collision::AABB(minP, maxP, cMin, cMax)) {
					return true;
				}
			}

			// Check ALL physics bodies (player, enemies, NPCs, etc.)
			for (auto& otherPair : physicsBodies.components)
			{
				Entity other = otherPair.first;

				// Skip self
				if (other == entity) {
					continue;
				}
				// Skip enemies if player (handled in stomp)
				if (!transforms.hasComponent(other)) {
					continue;
				}

				// Get other components
				Transforms& oT = transforms.getComponent(other);
				PhysicsBody& oB = physicsBodies.getComponent(other);

				// AABB for other entity
				glm::vec3 oMin = oT.position - oB.halfSize;
				glm::vec3 oMax = oT.position + oB.halfSize;

				if (Collision::AABB(minP, maxP, oMin, oMax)) {
					return true;

				}
			}
			return false;
		};

		glm::vec3 pos = transform.position;

		// x Axis
		glm::vec3 testPos = pos;
		// update test position
		testPos.x += body.velocity.x * dt;

		// if no collision, update position
		if (!collides(testPos)) {
			pos.x = testPos.x;
		}
		else {
			body.velocity.x = 0.0f;
		}

		// Check for stomping on enemies
		stompSystem(registry, entity, pos, body);

		// y Axis
		testPos = pos;
		// update test position
		testPos.y += body.velocity.y * dt;

		// if no collision, update position
		if (!collides(testPos))
		{
			pos.y = testPos.y;
		}
		else
		{
			// If colliding while falling, set grounded
			if (body.velocity.y < 0) {
				body.grounded = true;
			}
			body.velocity.y = 0.0f;
		}

		// z Axis
		testPos = pos;
		// update test position
		testPos.z += body.velocity.z * dt;

		// if no collision, update position
		if (!collides(testPos)) {
			pos.z = testPos.z;
		}
		else {
			body.velocity.z = 0.0f;
		}
		// Update transform position
		transform.position = pos;

	}
	
}

// System to update child entity positions based on their parents
inline void hierarchySystem(Registry& registry)
{
	// Get component storages
	auto& parents = registry.getStorage<Parent>();
	auto& transforms = registry.getStorage<Transforms>();

	// Update child positions
	for (auto& pair : parents.components)
	{
		// Get child and parent entities
		Entity child = pair.first;
		Entity parent = pair.second.parent;

		// Check if both have Transforms component
		if (!transforms.hasComponent(child) || !transforms.hasComponent(parent)) {
			continue;
		}
		// Get Transforms components
		Transforms& childT = transforms.getComponent(child);
		Transforms& parentT = transforms.getComponent(parent);

		// Update child position based on parent
		childT.position = parentT.position + childT.localPosition;
	}
}
