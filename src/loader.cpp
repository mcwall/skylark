#include "loader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

RomLoader::RomLoader()
{
}

RomLoader::~RomLoader()
{
}

// Offset should be 0x200
void RomLoader::LoadFromFile(string fileName, Memory *memory, uint16_t offset)
{
    // Read filestream as bytes
    basic_ifstream<uint8_t> file(fileName, ios::binary);
    vector<uint8_t> fileBytes = vector<uint8_t>(istreambuf_iterator<uint8_t>(file),
                                                istreambuf_iterator<uint8_t>());

    for (uint16_t addr = 0; addr < fileBytes.size(); addr++)
    {
        memory->write(addr + offset, fileBytes[addr]);
    }
}