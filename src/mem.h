#ifndef MEM_H
#define MEM_H

#include <iostream>

class Memory
{
  public:
    Memory(unsigned int size);

    uint8_t read(unsigned int address);
    void write(unsigned int address, uint8_t b);

  private:
    unsigned int size;
    uint8_t *arr;
};

#endif