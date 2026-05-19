#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <fstream>
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Transform.h"
#include "World.h"
#include "Components.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Registry.h"
#include "Systems.h"

enum class GameMode {
	Editor,
	Play
};

enum class EditorTool {
	Block,
	Enemy
};

class Game
{
public:
	Game();
	~Game();

	bool init();
	void run();
	void shutdown();

private:
	void processEvents();
	void update(double dt);
	void render();

	void updateEditor(double dt);
	void updatePlay(double dt);

	void handleEditorInput(SDL_Event& e);
	void handlePlayInput(SDL_Event& e);

	void updateCursor();

	bool rayPlaneIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,glm::vec3& outHit);
	glm::vec3 snapToGrid(const glm::vec3& position, float gridSize);

private:
    GameMode mode = GameMode::Editor;
    bool isRunning = true;
    bool mouseCaptured = false;

    // --- World / ECS ---
    World* world = nullptr;
    Registry ecs;

    // --- Rendering ---
    Window window;
    Renderer renderer;
    Camera camera;

    Shader* shader = nullptr;
    Shader* skyboxShader = nullptr;
    Texture* texture = nullptr;

    Material material;
    std::vector<Material> blockMats;

    Mesh cubeMesh;
    Mesh uiQuadMesh;

    // --- World Data ---
    std::vector<placedCube> placedCubes;
    Transforms cursorTransform{};
    bool hasCursor = false;

    int selectedBlock = 0;
    EditorTool currentTool = EditorTool::Block;

    // --- Sky Colours ---
    glm::vec3 skyTopColour = glm::vec3(0.294f, 0.000, 0.510f);
    glm::vec3 skyBottomColour = glm::vec3(0.294f, 0.000, 0.510f);

    // --- Player ---
    Transforms playerTransform{};

    // --- Timing ---
    Uint64 now = 0;
    Uint64 last = 0;
    double deltaTime = 0.0;

    float moveSpeed = 5.0f;

    // --- Grid / Skybox ---
    GLuint gridVBO = 0;
    GLuint gridVAO = 0;

    GLuint skyboxVAO = 0;
    GLuint skyboxVBO = 0;

    std::vector<glm::vec3> gridLines;

    glm::vec3 cameraLastPos = glm::vec3(0.0f);
    glm::vec3 cameraLastForward = glm::vec3(0.0f);


};

