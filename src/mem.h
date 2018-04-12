#ifndef MEM_H
#define MEM_H

#include <iostream>
#include <vector>
using namespace std;

class Memory
{
  public:
    Memory(uint16_t size);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t b);

  private:
    vector<uint8_t> arr;
};

#endif