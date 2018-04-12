#ifndef MEM_H
#define MEM_H

#include <iostream>

class Memory
{
  public:
    Memory(uint16_t size);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t b);

  private:
    unsigned int size;
    uint8_t *arr;
};

#endif