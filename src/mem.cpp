#include "mem.h"

#include <iostream>
#include <vector>
using namespace std;

Memory::Memory(uint16_t size)
{
    this->arr = vector<uint8_t>(size);
}

uint8_t Memory::read(uint16_t address)
{
    if (address >= this->arr.size())
    {
        throw "Invalid memory read access";
    }

    return this->arr[address];
}

void Memory::write(uint16_t address, uint8_t byte)
{
    if (address >= this->arr.size())
    {
        throw "Invalid memory write access";
    }

    this->arr[address] = byte;
}