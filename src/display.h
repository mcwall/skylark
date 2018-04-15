#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>
#include <vector>

using namespace std;

class FrameBuffer
{

public:
  FrameBuffer(int width, int height);
  ~FrameBuffer();

  void clear();
  bool draw(int x, int y, bool value);
  bool draw(int x, int y, vector<uint8_t> sprite);

  int width();
  int height();
  bool get(int x, int y);

  void begin_frame();
  bool has_changes();

private:
  int w, h;
  vector<vector<bool>> buffer;
  bool changed;
};

#endif
