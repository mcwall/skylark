#include "mem.h"
#include <iostream>

Memory::Memory(uint16_t size)
{
    this->size = size;
    this->arr = (uint8_t *)malloc(sizeof(uint8_t) * size);
}

uint8_t Memory::read(uint16_t address)
{
    return this->arr[address];
}

void Memory::write(uint16_t address, uint8_t byte)
{
    this->arr[address] = byte;
}