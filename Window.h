#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

class Window
{
public:
	Window() = default;
	bool InitSDL(const std::string& title, int width, int height);
	void SwapBuffers();
	void Destroy();
private:
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = nullptr;
};

