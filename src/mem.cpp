#include "mem.h"
#include <iostream>

Memory::Memory(unsigned int size)
{
    this->size = size;
    this->arr = (uint8_t *)malloc(sizeof(uint8_t) * size);
}

uint8_t Memory::read(unsigned int address)
{
    return this->arr[address];
}

void Memory::write(unsigned int address, uint8_t byte)
{
    this->arr[address] = byte;
}