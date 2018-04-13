#include <SDL2/SDL.h>
#include <iostream>

#include "display.h"
#include "renderer.h"
#include "mem.h"
#include "cpu.h"
#include "loader.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 480;

const int RES_WIDTH = 128;
const int RES_HEIGHT = 64;

const uint16_t MEMORY_SIZE = 0x1000;
const uint16_t PROGRAM_OFFSET = 0x200;

const double REFRESH_RATE = 10;

void DrawHeart(DisplayBuffer *buffer)
{
	buffer->Clear();

	for (int x = 0; x < buffer->getWidth(); x++)
	{
		for (int y = 0; y < buffer->getHeight(); y++)
		{
			double xt = (x - 70) / 17.0;
			double yt = (y - 24) / -22.0;
			double exp1 = xt * xt + yt * yt - 1;
			double exp = exp1 * exp1 * exp1 - (xt * xt - yt * yt * yt);
			double thresh = 0.3;
			if (exp <= thresh)
			{
				buffer->Draw(x, y, true);
			}
		}
	}
}

void WindowTest()
{

	DisplayBuffer *displayBuffer = new DisplayBuffer(RES_WIDTH, RES_HEIGHT);
	WindowRenderer *renderer = new WindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	const double millisPerCycle = 1000 / REFRESH_RATE;
	string s = "sdfASDF";

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
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l)
			{
				DrawHeart(displayBuffer);
			}
		}

		renderer->Render(displayBuffer);
	}
}

void TestCpu()
{

	string fileName = "../roms/test.ch8";

	cout << "---- Started loading ROM---- \n\n";

	Memory *memory = new Memory(MEMORY_SIZE);
	DisplayBuffer *displayBuffer = new DisplayBuffer(RES_WIDTH, RES_HEIGHT);
	Processor *cpu = new Processor(memory, displayBuffer);
	RomLoader *loader = new RomLoader();

	loader->LoadFromFile(fileName, memory, PROGRAM_OFFSET);

	cout << "---- Successfully loaded ROM---- \n\n\n";

	cout << "---- Started executing CPU---- \n\n";

	while (cpu->ExecuteNext())
		;

	cout << "\n---- Finished executing CPU---- \n";
}

int main(int argc, char *argv[])
{
	TestCpu();
}
