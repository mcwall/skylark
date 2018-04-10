#include <SDL2/SDL.h>
#include <iostream>

#include "display.h"
#include "renderer.h"

using namespace std;

void DrawRandomPixels(DisplayBuffer *buffer)
{
	for (int x = 0; x < buffer->getWidth(); x++)
	{
		for (int y = 0; y < buffer->getHeight(); y++)
		{
			if ((x + y) % 2 == 1)
			{
				buffer->Draw(x, y, true);
			}
		}
	}
}

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 480;

const int RES_WIDTH = 64;
const int RES_HEIGHT = 32;

const double REFRESH_RATE = 10;

int main(int argc, char *argv[])
{
	DisplayBuffer *displayBuffer = new DisplayBuffer(RES_WIDTH, RES_HEIGHT);
	WindowRenderer *renderer = new WindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	DrawRandomPixels(displayBuffer);

	const double millisPerCycle = 1000 / REFRESH_RATE;

	// Main loop
	bool quit = false;
	SDL_Event e;
	int factor = 0;
	while (!quit)
	{
		// Process events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
			{
				quit = true;
			}
		}

		renderer->Render(displayBuffer);
	}

	return 0;
}
