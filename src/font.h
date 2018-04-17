#ifndef FONT_LOADER_H
#define FONT_LOADER_H

#include "mem.h"
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class FontLoader
{

public:
  FontLoader();
  ~FontLoader();

  void load(Memory *memory, uint16_t offset);

};

#endif
