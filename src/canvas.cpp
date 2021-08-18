#include "canvas.h"

#ifdef _WIN32
#include <SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

canvas::canvas(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1,0);
	SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);

	texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);

}

canvas::~canvas() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void canvas::Update(uint32_t buffer[], int pitch)
{
	pixels = new uint32_t[160 * 100];
	for (int i = 0; i < 160 * 100; ++i) {
		uint8_t pixel = buffer[i];
		pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
	}

	SDL_UpdateTexture(texture, nullptr, pixels, pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
	delete[] pixels;
}


bool canvas::ProcessInput() {

	bool quit = false;

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			quit = true;
		} break;

		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			{
				quit = true;
			} break;
			}
		} break;
		}
	}

	return quit;

}