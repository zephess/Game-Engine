#include "Game.h"

static float skyboxVertices[] = {
	// positions
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

static std::vector<vertex> cubeVertices = {
	// Front (+Z)
	{{-0.5f, -0.5f,  0.5f}, {1,1,1}, {0,0}, {0,0,1}},
	{{ 0.5f, -0.5f,  0.5f}, {1,1,1}, {1,0}, {0,0,1}},
	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, {1,1}, {0,0,1}},
	{{-0.5f,  0.5f,  0.5f}, {1,1,1}, {0,1}, {0,0,1}},

	// Back (-Z)
	{{ 0.5f, -0.5f, -0.5f}, {1,1,1}, {0,0}, {0,0,-1}},
	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, {1,0}, {0,0,-1}},
	{{-0.5f,  0.5f, -0.5f}, {1,1,1}, {1,1}, {0,0,-1}},
	{{ 0.5f,  0.5f, -0.5f}, {1,1,1}, {0,1}, {0,0,-1}},

	// Left (-X)
	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, {0,0}, {-1,0,0}},
	{{-0.5f, -0.5f,  0.5f}, {1,1,1}, {1,0}, {-1,0,0}},
	{{-0.5f,  0.5f,  0.5f}, {1,1,1}, {1,1}, {-1,0,0}},
	{{-0.5f,  0.5f, -0.5f}, {1,1,1}, {0,1}, {-1,0,0}},

	// Right (+X)
	{{ 0.5f, -0.5f,  0.5f}, {1,1,1}, {0,0}, {1,0,0}},
	{{ 0.5f, -0.5f, -0.5f}, {1,1,1}, {1,0}, {1,0,0}},
	{{ 0.5f,  0.5f, -0.5f}, {1,1,1}, {1,1}, {1,0,0}},
	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, {0,1}, {1,0,0}},

	// Top (+Y)
	{{-0.5f,  0.5f,  0.5f}, {1,1,1}, {0,0}, {0,1,0}},
	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, {1,0}, {0,1,0}},
	{{ 0.5f,  0.5f, -0.5f}, {1,1,1}, {1,1}, {0,1,0}},
	{{-0.5f,  0.5f, -0.5f}, {1,1,1}, {0,1}, {0,1,0}},

	// Bottom (-Y)
	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, {0,0}, {0,-1,0}},
	{{ 0.5f, -0.5f, -0.5f}, {1,1,1}, {1,0}, {0,-1,0}},
	{{ 0.5f, -0.5f,  0.5f}, {1,1,1}, {1,1}, {0,-1,0}},
	{{-0.5f, -0.5f,  0.5f}, {1,1,1}, {0,1}, {0,-1,0}},
};

static std::vector<GLuint> cubeIndices = {
	// Front
	0, 1, 2,  2, 3, 0,
	// Back
	4, 5, 6,  6, 7, 4,
	// Left
	8, 9, 10, 10, 11, 8,
	// Right
	12, 13, 14, 14, 15, 12,
	// Top
	16, 17, 18, 18, 19, 16,
	// Bottom
	20, 21, 22, 22, 23, 20
};

static std::vector<vertex> uiQuad = {
		{{-0.5f, -0.5f, 0}, {1,1,1}, {0,0}, {0,0,1}},
	{{ 0.5f, -0.5f, 0}, {1,1,1}, {1,0}, {0,0,1}},
	{{ 0.5f,  0.5f, 0}, {1,1,1}, {1,1}, {0,0,1}},
	{{-0.5f,  0.5f, 0}, {1,1,1}, {0,1}, {0,0,1}},

};

static std::vector<GLuint> uiIndices = { 0,1,2,2,3,0 };

Game::Game() : mode(GameMode::Editor), isRunning(true), mouseCaptured(false), moveSpeed(5.0f), shader(nullptr), texture(nullptr) {
}

Game::~Game() {
	shutdown();
	// Cleanup resources if needed
}

bool Game::init() {
	
	// Initialize SDL and create window
	if(!window.InitSDL("ZENgine", 800, 600)) {
		return false;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Initialize world, renderer, camera, shaders, textures, materials, etc.
	world = new World();

	skyboxShader = new Shader("skyvertex.glsl", "skyfragment.glsl");
	shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
	shader->Use();
	shader->setVec3("uLight.direction", glm::vec3(0.0f, 0.0f, 1.0f));
	shader->setVec3("uLight.colour", glm::vec3(1.0f, 1.0f, 1.0f));
	
	renderer.init();
	
	texture = new Texture("brick.png");
	Texture* mushroomTexture = new Texture("muchroom.png");
	Texture* stoneTexture = new Texture("stone.jpg");
	Texture* grassTexture = new Texture("grass.jpg");
	Texture* woodTexture = new Texture("wood.jpg");
	Texture* leavesTexture = new Texture("foliage.png");
	Texture* metalTexture = new Texture("metal.jpg");
	blockMats.push_back(DiffuseMaterial(texture));
	blockMats.push_back(DiffuseMaterial(stoneTexture));
	blockMats.push_back(DiffuseMaterial(grassTexture));
	blockMats.push_back(DiffuseMaterial(woodTexture));
	blockMats.push_back(EmissiveMaterial(leavesTexture));
	blockMats.push_back(MetallicMaterial(metalTexture));
	blockMats.push_back(DiffuseMaterial(mushroomTexture));
	material = DiffuseMaterial(texture);
	shader->setInt("uTexture", 0);

	// Initialize camera
	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), 800.0f / 600.0f);

	// Generate grid lines
	int gridSize = 20;
	for (int i = -gridSize; i <= gridSize; ++i) {
		float f = i + 0.5f;

		// Lines parallel to X
		gridLines.push_back(glm::vec3(-gridSize, f, -0.001));
		gridLines.push_back(glm::vec3(gridSize, f, -0.001));

		// Lines parallel to Z
		gridLines.push_back(glm::vec3(f, -gridSize, -0.001));
		gridLines.push_back(glm::vec3(f, gridSize, -0.001));
	}
	
	// Setup skybox VAO and VBO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	
	// Setup grid VAO and VBO
	glGenVertexArrays(1, &gridVAO);
	glGenBuffers(1, &gridVBO);

	glBindVertexArray(gridVAO);
	glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
	glBufferData(GL_ARRAY_BUFFER, gridLines.size() * sizeof(glm::vec3), gridLines.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

	glBindVertexArray(0);


	// Initialize meshes
	uiQuadMesh.init(uiQuad, uiIndices);
	
	cubeMesh.init(cubeVertices, cubeIndices);

	// Initialize cursor transform
	cursorTransform.position = glm::vec3(0.0f);
	cursorTransform.scale = glm::vec3(1.0f);
	cursorTransform.rotation = glm::vec3(0.0f);

	// Initialize player entity
	Entity playerEntity = ecs.createEntity();
	Transforms playerTransform{};
	playerTransform.initialPosition = glm::vec3(0.0f, 1.0f, 0.0f);
	PhysicsBody playerPhysics{};
	playerPhysics.halfSize = glm::vec3(0.25f, 0.5f, 0.25f);
	// Add components to player entity
	ecs.addComponent(playerEntity, Transforms{});
	ecs.addComponent(playerEntity, PlayerTag{});
	ecs.addComponent(playerEntity, Input{});
	ecs.addComponent(playerEntity, PhysicsBody{playerPhysics});
	ecs.addComponent(playerEntity, ChildList{});
	
	// Create body and head entities as children of player
	Entity body = ecs.createEntity();
	Transforms bodyTransform{};
	bodyTransform.localPosition = glm::vec3(0.0f, 0.0f, 0.5f);
	bodyTransform.scale = glm::vec3(0.5f, 1.0f, 0.5f);
	ecs.addComponent(body, Renderable{ &cubeMesh, &blockMats[0] });
	ecs.addComponent(body, Transforms{ bodyTransform });
	ecs.addComponent(body, Parent{ playerEntity });
	ecs.getComponent<ChildList>(playerEntity).children.push_back(body);

	Entity head = ecs.createEntity();
	Transforms headTransform{};
	headTransform.localPosition = glm::vec3(0.0f, 0.75f, 0.5f);
	headTransform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
	ecs.addComponent(head, Renderable{ &cubeMesh, &blockMats[0] });
	ecs.addComponent(head, Transforms{ headTransform });
	ecs.addComponent(head, Parent{ playerEntity });
	ecs.getComponent<ChildList>(playerEntity).children.push_back(head);
	
	// get tick count for delta time calculation
	now = SDL_GetPerformanceCounter();
	last = now;

	return true;
}

void Game::run() {
	while(isRunning) {
		// Calculate delta time
		now = SDL_GetPerformanceCounter();
		deltaTime = static_cast<double>(now - last) / SDL_GetPerformanceFrequency();
		last = now;
		// Set clear color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		
		// Process events, update game state, and render
		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::shutdown() {
	// Cleanup resources
	window.Destroy();
}


// Ray-plane intersection to find cursor position on the ground plane (Z=0)
bool Game::rayPlaneIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, glm::vec3& outHit)
{
	// If ray is parallel to XY plane
	if (fabs(rayDirection.z) < 0.0001f)
		return false;

	// Calculate intersection t value
	float t = -rayOrigin.z / rayDirection.z;
	// If intersection is behind the ray origin
	if (t < 0)
		// no intersection
		return false;
	// Else calculate hit point
	outHit = rayOrigin + rayDirection * t;
	return true;
}

// Snap position to grid
glm::vec3 Game::snapToGrid(const glm::vec3& position, float gridSize) {
	// Snap x and y to nearest grid point, keep z unchanged
	return glm::vec3(
		std::round(position.x / gridSize) * gridSize,
		std::round(position.y / gridSize) * gridSize,
		position.z
	);
}

// Process SDL events
void Game::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Handle quit event
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		// Handle input based on game mode
		if (mode == GameMode::Editor) {
			handleEditorInput(event);
		}
		else {
			handlePlayInput(event);
		}
		
	}
}

// Handle input in editor mode
void Game::handleEditorInput(SDL_Event& e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		// Left click to place block or enemy
		if (e.button.button == SDL_BUTTON_LEFT) {
			if(currentTool == EditorTool::Block){
				world->placeBlock(cursorTransform.position, selectedBlock);
			}
			else if (currentTool == EditorTool::Enemy) {
				// create enemy entity at cursor position
				Entity enemyEntity = ecs.createEntity();
				PhysicsBody enemyPhysics{};
				enemyPhysics.halfSize = glm::vec3(0.45, 0.45, 0.45);
				ecs.addComponent(enemyEntity, Transforms{ cursorTransform.position, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.9f), cursorTransform.position});
				ecs.addComponent(enemyEntity, EnemyTag{});
				ecs.addComponent(enemyEntity, Renderable{ &cubeMesh, &blockMats[6] });
				ecs.addComponent(enemyEntity, PhysicsBody{ enemyPhysics });
				
			
			}
		}
		// Right click to remove block
		else if (e.button.button == SDL_BUTTON_RIGHT) {
			if (currentTool == EditorTool::Block) {
				world->removeBlock(cursorTransform.position);
			}
			
			
		}
		// Middle click to toggle mouse capture
		if(e.button.button == SDL_BUTTON_MIDDLE) {
			if(mouseCaptured) {
				SDL_SetRelativeMouseMode(SDL_FALSE);
				mouseCaptured = false;
			} else {
				SDL_SetRelativeMouseMode(SDL_TRUE);
				mouseCaptured = true;
			}
		}
		

	}
	
	// Mouse wheel to change selected block type
	if(e.type == SDL_MOUSEWHEEL) {
		if (e.wheel.y > 0) {
			selectedBlock--;
		} else if (e.wheel.y < 0) {
			selectedBlock++;
		}
		// Wrap around block selection
		// Hard coded so enemy texture is not selectable
		if(selectedBlock < 0) {
			selectedBlock = blockMats.size() - 2;
		}
		if(selectedBlock >= blockMats.size() - 1) {
			selectedBlock = 0;
		}
		
	}

	if(e.type == SDL_KEYDOWN) {
		// TAB to switch to play mode
		if (e.key.keysym.sym == SDLK_TAB) {
			// Save camera position
			cameraLastPos = camera.getPosition();
			cameraLastForward = camera.getForward();
			// Reset player position
			// Or meant to :(
			// resets all enemies though
			for (int i = 0; i < ecs.getAllEntities().size(); ++i) {
				ecs.getComponent<Transforms>(ecs.getAllEntities()[i]).position = ecs.getComponent<Transforms>(ecs.getAllEntities()[i]).initialPosition;
			}
			// Switch mode
			mode = GameMode::Play;
		}
		// F5 to save world
		if (e.key.keysym.sym == SDLK_F5) {
			
			world->saveWorld("world.zen");
		}
		// F9 to load world
		if (e.key.keysym.sym == SDLK_F9) {
			world->loadWorld("world.zen", blockMats);
			
		}
		// Q to switch tools
		if (e.key.keysym.sym == SDLK_q) {
			if(EditorTool::Block == currentTool) {
				currentTool = EditorTool::Enemy;
				std::cout << "Switched to Enemy Tool" << std::endl;
			} 
			else {
				currentTool = EditorTool::Block;
				std::cout << "Switched to Block Tool" << std::endl;
			}
		}
	}
	// Mouse motion to rotate camera
	if(e.type == SDL_MOUSEMOTION && mouseCaptured) {
		float sensitivity = 0.1f;
		float yawOffset = e.motion.xrel * sensitivity;
		float pitchOffset = -e.motion.yrel * sensitivity;
		camera.rotate(pitchOffset, yawOffset);
	}
}

// Handle input in play mode
void Game::handlePlayInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB) {
		mode = GameMode::Editor;
		// Again supposed to reset all entity positions
		// only does enemies though
		for (int i = 0; i < ecs.getAllEntities().size(); i++) {
			ecs.getComponent<Transforms>(ecs.getAllEntities()[i]).position = ecs.getComponent<Transforms>(ecs.getAllEntities()[i]).initialPosition;
		}
	}
}

// Update game state
void Game::update(double dt) {
	if (mode == GameMode::Editor) {
		updateEditor(dt);
	}
	else {
		updatePlay(dt);
	}
}

// Update in editor mode
void Game::updateEditor(double dt) {
	// Keyboard state for movement
	const Uint8* state = SDL_GetKeyboardState(NULL);
	float speed = moveSpeed * dt;

	if (state[SDL_SCANCODE_W]) camera.moveForward(speed);
	if (state[SDL_SCANCODE_S]) camera.moveForward(-speed);
	if (state[SDL_SCANCODE_A]) camera.moveRight(-speed);
	if (state[SDL_SCANCODE_D]) camera.moveRight(speed);
	if (state[SDL_SCANCODE_SPACE]) camera.moveUp(speed);
	if (state[SDL_SCANCODE_LCTRL]) camera.moveUp(-speed);

	// Update cursor position
	updateCursor();
}

// Update in play mode
void Game::updatePlay(double dt) {
	// Update ECS systems
	inputSystem(ecs);
	playerControlSystem(ecs, dt);
	std::vector<placedCube> cubes = world->getCubeList();
	physicsSystem(ecs, (float)dt, cubes);
	hierarchySystem(ecs);
	enemyAISystem(ecs, dt);
	cameraFollowSystem(ecs, camera);

}

// Update cursor position based on ray-plane intersection
void Game::updateCursor() {
	glm::vec3 rayOrigin = camera.getPosition();
	glm::vec3 rayDirection = camera.getForward();
	glm::vec3 hitPoint;
	if (rayPlaneIntersection(rayOrigin, rayDirection, hitPoint)) {
		cursorTransform.position = snapToGrid(hitPoint, 1.0f) + glm::vec3(0.5f, 0.5f, 0.5f);
		hasCursor = true;
	}
	else {
		hasCursor = false;
	}
	
}

void Game::render() {

	// Clear everything
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Skybox rendering setup
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);

	// Skybox shader
	// customisable sine wave gradient
	skyboxShader->Use();
	skyboxShader->setMat4("uView", camera.getViewMatrix());
	skyboxShader->setMat4("uProjection", camera.getProjectionMatrix());
	skyboxShader->setFloat("uTime", float(SDL_GetTicks()) / 1000.0f);
	skyboxShader->setVec3("topColor", skyTopColour);
	skyboxShader->setVec3("bottomColor", skyBottomColour);
	skyboxShader->setFloat("waveAmplitude", 0.3f);

	// Draw skybox
	glBindVertexArray(skyboxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Restore depth settings
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	// Clear depth so world draws over skybox
	glClear(GL_DEPTH_BUFFER_BIT);

	// Main shader setup
	shader->Use();
	shader->setVec3("uViewPos", camera.getPosition());
	shader->setMat4("uProjection", camera.getProjectionMatrix());
	shader->setMat4("uView", camera.getViewMatrix());
	renderer.startRendering(camera, *shader);

	// Render world
	world->render(renderer, *shader, cubeMesh, blockMats);
	
	// Render editor-specific elements
	if (mode == GameMode::Editor) {


		// Render cursor ghost block
		if (hasCursor) {
			Material ghost = blockMats[selectedBlock];
			ghost.emissive = 0.5f;
			renderer.drawMesh(cubeMesh, cursorTransform, *shader, ghost);
		}

		// Render grid lines
		world->renderGridLines(renderer, *shader, gridLines, gridVAO);
		glEnable(GL_DEPTH_TEST);

		// Render UI hotbar
		if (currentTool == EditorTool::Block) {
			world->renderUI(renderer, shader, blockMats, selectedBlock, uiQuadMesh);

		}
	}
	// Render all entities in ECS
	renderSystem(ecs, renderer, *shader);

	// Finish rendering
	renderer.stopRendering();
	window.SwapBuffers();
}




