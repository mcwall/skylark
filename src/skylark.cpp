#include <SDL2/SDL.h>
#include <iostream>

#include "timer.h"
#include "frame.h"
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

const int RES_WIDTH = 64;
const int RES_HEIGHT = 32;

const uint16_t MEMORY_SIZE = 0x1000;
const uint16_t PROGRAM_OFFSET = 0x200;

const double FRAMERATE_CAP = 60;

void test_full()
{
	string fileName = "../roms/vf_test.ch8";

	cout << "---- Started loading ROM---- \n\n";

	Memory *memory = new Memory(MEMORY_SIZE);
	Timer *delay_timer = new Timer(60);
	Timer *sound_timer = new Timer(60);

	FrameBuffer *frame_buffer = new FrameBuffer(RES_WIDTH, RES_HEIGHT);
	WindowRenderer *renderer = new WindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	Processor *cpu = new Processor(memory, delay_timer, sound_timer, frame_buffer);

	RomLoader *loader = new RomLoader();

	loader->LoadFromFile(fileName, memory, PROGRAM_OFFSET);

	cout << "---- Successfully loaded ROM---- \n\n\n";

	cout << "---- Started executing CPU---- \n\n";

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

		frame_buffer->begin_frame();

		cpu->ExecuteNext();
		if (frame_buffer->has_changes())
			renderer->Render(frame_buffer);
	}
}

void test_timer()
{
	Timer *timer = new Timer(60);
	while (1)
	{
		uint16_t timer_val = timer->get();
		if (timer_val == 0)
		{
			cout << "TIMER\n";
			timer->set(20);
		}
	}
}

int main(int argc, char *argv[])
{
	test_full();
}
