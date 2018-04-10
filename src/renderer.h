#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "display.h"

class WindowRenderer
{
public:
  WindowRenderer(int width, int height);
  ~WindowRenderer();

  void Render(DisplayBuffer *buffer);

private:
  int width, height;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif
