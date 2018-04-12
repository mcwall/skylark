#ifndef LOADER_H
#define LOADER_H

#include "mem.h"
using namespace std;

class RomLoader
{
public:
  RomLoader();
  ~RomLoader();

  void LoadFromFile(string fileName, Memory *memory, uint16_t offset);
};

#endif
