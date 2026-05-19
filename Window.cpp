#include "Window.h"

bool Window::InitSDL(const std::string& title, int width, int height) {

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL Init failed: " << SDL_GetError() << "\n";
		return false;
	}

	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
		return false;
	}
	// Create OpenGL context
	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		std::cerr << "OpenGL context creation failed: " << SDL_GetError() << "\n";
		return false;
	}
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW Init failed\n";
		return false;
	}
	// Enable VSync
	SDL_GL_SetSwapInterval(1);
	std::cout << "SDL and OpenGL initialized successfully.\n";
	return true;
}

void Window::SwapBuffers() {
	SDL_GL_SwapWindow(window);
}

void Window::Destroy() {
	if (glContext) {
		SDL_GL_DeleteContext(glContext);
		glContext = nullptr;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	SDL_Quit();
}
