#include "renderer.h"
#include <iostream>

WindowRenderer::WindowRenderer(int width, int height)
{
    this->width = width;
    this->height = height;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Skylark", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
};

void WindowRenderer::Render(DisplayBuffer *buffer)
{
    int res_width = buffer->getWidth();
    int res_height = buffer->getHeight();

    int blockgetWidth = width / buffer->getWidth();
    int blockHeight = height / buffer->getHeight();

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF); // BLACK
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // WHITE

    // Draw blocks (x,y,w,h)
    for (int x = 0; x < res_width; x++)
    {
        for (int y = 0; y < res_height; y++)
        {
            if (buffer->get(x, y))
            {
                SDL_Rect block = {x * blockgetWidth, y * blockHeight, blockgetWidth, blockHeight};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

WindowRenderer::~WindowRenderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
}