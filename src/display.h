#ifndef DISPLAY_H
#define DISPLAY_H

class DisplayBuffer
{

public:
  DisplayBuffer(int width, int height);
  ~DisplayBuffer();
  bool Draw(int x, int y, bool value);
  void Clear();
  // bool DrawSprite(Sprite *sprite);
  int getWidth();
  int getHeight();
  bool get(int x, int y);

private:
  int width, height;
  bool **buffer;
};

#endif
