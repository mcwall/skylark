#include "font.h"

#include "mem.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

FontLoader::FontLoader()
{
}

FontLoader::~FontLoader()
{
}

void FontLoader::load(Memory *memory, uint16_t offset)
{
    // TODO: move this data to a proper data file

    // 0
    uint16_t addr = offset + 0x0;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x9); // 1001
    memory->write(addr + 2,  0x9); // 1001
    memory->write(addr + 3,  0x9); // 1001
    memory->write(addr + 4,  0xf); // 1111

    // 1
    addr += 5;
    memory->write(addr + 0,  0x2); // 0010
    memory->write(addr + 1,  0x6); // 0110
    memory->write(addr + 2,  0x2); // 0010
    memory->write(addr + 3,  0x2); // 0010
    memory->write(addr + 4,  0x7); // 0111

    // 2
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x1); // 0001
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x8); // 1000
    memory->write(addr + 4,  0xf); // 1111

    // 3
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x1); // 0001
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x1); // 0001
    memory->write(addr + 4,  0xf); // 1111

    // 4
    addr += 5;
    memory->write(addr + 0,  0x9); // 1001
    memory->write(addr + 1,  0x9); // 1001
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x1); // 0001
    memory->write(addr + 4,  0x1); // 0001

    // 5
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x8); // 1000
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x1); // 0001
    memory->write(addr + 4,  0xf); // 1111

    // 6
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x8); // 1000
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x9); // 1001
    memory->write(addr + 4,  0xf); // 1111

    // 7
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x1); // 0001
    memory->write(addr + 2,  0x2); // 0010
    memory->write(addr + 3,  0x4); // 0100
    memory->write(addr + 4,  0x4); // 0100

    // 8
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x9); // 1001
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x9); // 1001
    memory->write(addr + 4,  0xf); // 1111

    // 9
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x9); // 1001
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x1); // 0001
    memory->write(addr + 4,  0xf); // 1111

    // A
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x9); // 1001
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x9); // 1001
    memory->write(addr + 4,  0x9); // 1001

    // B
    addr += 5;
    memory->write(addr + 0,  0xe); // 1110
    memory->write(addr + 1,  0x9); // 1001
    memory->write(addr + 2,  0xe); // 1110
    memory->write(addr + 3,  0x9); // 1001
    memory->write(addr + 4,  0xe); // 1110

    // C
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x8); // 1000
    memory->write(addr + 2,  0x8); // 1000
    memory->write(addr + 3,  0x8); // 1000
    memory->write(addr + 4,  0xf); // 1111

    // D
    addr += 5;
    memory->write(addr + 0,  0xe); // 1110
    memory->write(addr + 1,  0x9); // 1001
    memory->write(addr + 2,  0x9); // 1001
    memory->write(addr + 3,  0x9); // 1001
    memory->write(addr + 4,  0xe); // 1110

    // E
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x8); // 1000
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x8); // 1000
    memory->write(addr + 4,  0xf); // 1111

    // F
    addr += 5;
    memory->write(addr + 0,  0xf); // 1111
    memory->write(addr + 1,  0x8); // 1000
    memory->write(addr + 2,  0xf); // 1111
    memory->write(addr + 3,  0x8); // 1000
    memory->write(addr + 4,  0x8); // 1000
}
