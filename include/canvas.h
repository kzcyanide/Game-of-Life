#pragma once

#include <stdio.h> /* printf and fprintf */
#include<iostream>
#include <cstdint>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class canvas {

public:
	canvas(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
	void Update(uint32_t buffer[], int pitch);
	bool ProcessInput();
	~canvas();

private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
	uint32_t* pixels;


};