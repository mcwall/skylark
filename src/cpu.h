#ifndef CPU_H
#define CPU_H

#include "mem.h"

class Processor
{
  public:
    Processor(Memory *memory);
    ~Processor();

  private:
    Memory *memory;
    unsigned int pc;
};

#endif
