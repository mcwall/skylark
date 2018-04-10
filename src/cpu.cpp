#include "cpu.h"
#include "mem.h"
#include <iostream>

Processor::Processor(Memory *memory)
{
    this->memory = memory;
};

Processor::~Processor()
{
    free(this->memory);

    this->memory = NULL;
}