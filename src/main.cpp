#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

class Sprite
{

  public:
	Sprite(int width, int height)
	{
	}

  private:
	int width, height;
	bool **sprite;
};

// TODO: Rename this class
class DisplayBuffer
{

  public:
	DisplayBuffer(int width, int height)
	{
		this->width = width;
		this->height = height;

		this->buffer = new bool *[width];
		for (int x = 0; x < width; x++)
		{
			this->buffer[x] = new bool[height];
			for (int y = 0; y < height; y++)
				this->buffer[x][y] = false;
		}
	}

	void Clear()
	{
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
				buffer[x][y] = false;
	}

	bool DrawSprite(Sprite *sprite)
	{
		// TODO: Implement sprites
	}

	bool Draw(int x, int y, bool value)
	{
		const bool origScreenPixel = this->buffer[x][y];
		this->buffer[x][y] ^= value;

		// true iff screen pixel was flipped from set to unset
		return origScreenPixel && !this->buffer[x][y];
	}

	int Width()
	{
		return width;
	}

	int Height()
	{
		return height;
	}

	bool Get(int x, int y)
	{
		return buffer[x][y];
	}

  private:
	int width, height;
	bool **buffer;
};

class DiplayRenderer
{
  public:
	virtual ~DiplayRenderer() = default;

	DiplayRenderer(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	virtual void Render(DisplayBuffer *buffer) = 0;

  protected:
	int width, height;
};

class WindowDisplayRenderer : public DiplayRenderer
{
  public:
	WindowDisplayRenderer(int width, int height) : DiplayRenderer(width, height)
	{
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Skylark", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}

	void Render(DisplayBuffer *buffer) override
	{
		int res_width = buffer->Width();
		int res_height = buffer->Height();

		int block_width = width / buffer->Width();
		int block_height = height / buffer->Height();

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF); // BLACK
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // WHITE

		// Draw blocks (x,y,w,h)
		for (int x = 0; x < res_width; x++)
		{
			for (int y = 0; y < res_height; y++)
			{
				if (buffer->Get(x, y))
				{
					SDL_Rect block = {x * block_width, y * block_height, block_width, block_height};
					SDL_RenderFillRect(renderer, &block);
				}
			}
		}

		SDL_RenderPresent(renderer);
	}

	~WindowDisplayRenderer()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		renderer = NULL;
		window = NULL;
	}

  private:
	SDL_Window *window;
	SDL_Renderer *renderer;
};

class ConsoleOutputRenderer : public DiplayRenderer
{
  public:
	ConsoleOutputRenderer() : DiplayRenderer(0, 0)
	{
		// This class shouldn't care about width and height in general, move to SDLWindowDisplayRenderer only, not in the superclass
	}

	void Render(DisplayBuffer *buffer) override
	{
		// hack: draw enough whitespace to move the console down
		for (int i = 0; i < 100; i++)
			cout << "\r\n";
		const int width = buffer->Width();
		const int height = buffer->Height();

		for (int y = 0; y < buffer->Height(); y++)
		{
			char *str = new char[width];
			for (int x = 0; x < width; x++)
			{
				str[x] = buffer->Get(x, y) ? CHARACTER : ' ';
			}

			cout << str << "\r\n";
		}
	}

  private:
	const char CHARACTER = '#';
};

void DrawRandomPixels(DisplayBuffer *buffer)
{
	for (int x = 0; x < buffer->Width(); x++)
	{
		for (int y = 0; y < buffer->Height(); y++)
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
	DiplayRenderer *renderer = new WindowDisplayRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
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
