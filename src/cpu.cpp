#include "cpu.h"
#include "mem.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Processor::Processor(Memory *memory, DisplayBuffer *displayBuffer)
{
    // TODO: Read from config or consts file, don't hardcode
    this->pc = 0x200;
    this->i = 0x0;
    this->v = vector<uint8_t>(16);

    this->memory = memory;
    this->displayBuffer = displayBuffer;
};

Processor::~Processor()
{
    free(memory);

    memory = NULL;
}

static void log(string message)
{
    cout << "[CPU] " << message << "\n";
}

static void log(uint16_t pc, uint16_t opcode)
{
    stringstream s;
    s << "Processing instruction 0x" << hex << opcode << " at 0x" << pc;
    log(s.str());
}

#pragma region exec functions

// increment pc
void Processor::inc()
{
    // increment by 2 since mem is 8-bit aligned, but opcodes are 16-bit
    pc += 2;
}

void Processor::exec_0(uint16_t opcode)
{
    // clear display
    if (opcode == 0x00E0)
    {
        this->displayBuffer->Clear();
        return;
    }

    // TODO: implement stack and subroutines
    // return from subroutine
    if (opcode == 0x00EE)
    {
        throw "Subroutines not implemented";
    }

    throw "RCA 1802 program call not implemented";
}

void Processor::exec_1(uint16_t opcode)
{
    // jump
    pc = opcode & 0x0fff;
}

void Processor::exec_2(uint16_t opcode)
{
    throw "Subroutines not implemented";
}

void Processor::exec_3(uint16_t opcode)
{
    // skip if v[x] == nn
    if (v[opcode & 0x0f00] == opcode & 0xff)
    {
        inc();
    }
}

void Processor::exec_4(uint16_t opcode)
{
    // skip if v[x] != nn
    if (v[opcode & 0x0f00] != opcode & 0xff)
    {
        inc();
    }
}

void Processor::exec_5(uint16_t opcode)
{
    // only valid opcode structure is 0x5XY0
    if (opcode & 0xF)
    {
        throw "Invalid opcode";
    }

    // skip if v[x] == v[y]
    if (v[opcode & 0x0f00] == v[opcode & 0xf0])
    {
        inc();
    }
}

void Processor::exec_6(uint16_t opcode)
{
    // v[x] = nn
    v[opcode & 0x0f00] = (opcode & 0xff);
}

void Processor::exec_7(uint16_t opcode)
{
    // v[x] += nn
    v[opcode & 0x0f00] += (opcode & 0xff);
}

void Processor::exec_8(uint16_t opcode)
{
    uint8_t x = opcode & 0x0f00;
    uint8_t y = opcode & 0x00f0;
    uint8_t op = opcode & 0x000f;

    switch (op)
    {
    case 0x0:
        v[x] = v[y];
        break;
    case 0x1:
        v[x] |= v[y];
        break;
    case 0x2:
        v[x] &= v[y];
        break;
    case 0x3:
        v[x] ^= v[y];
        break;
    case 0x4:
        // TODO:  VF carry flag
        v[x] += v[y];
        break;
    case 0x5:
        // TODO:  VF borrow flag
        v[x] -= v[y];
        break;
    case 0x6:
        // TODO:  VF flag
        v[x] = v[y] >> 1;
        break;
    case 0x7:
        // TODO:  VF flag
        v[x] = v[y] - v[x];
        break;
    case 0x8:
        // TODO:  VF flag
        v[x] = v[y];
        break;
    case 0xE:
        // TODO:  VF flag
        v[x] = v[y] << 1;
        break;
    default:
        throw "Invalid opcode";
    }
}

void Processor::exec_9(uint16_t opcode)
{
    // only valid opcode structure is 0x5XY0
    if (opcode & 0xF)
    {
        throw "Invalid opcode";
    }

    // skip if v[x] == v[y]
    if (v[opcode & 0x0f00] == v[opcode & 0xf0])
    {
        inc();
    }
}

void Processor::exec_a(uint16_t opcode)
{
    // i = nnn
    i = opcode & 0x0fff;
}

void Processor::exec_b(uint16_t opcode)
{
    // jump to v[0] + nnn
    pc = v[0] + (opcode & 0x0fff);
}

void Processor::exec_c(uint16_t opcode)
{
    // TODO: random
    // v[x] = rand() & nn
}

void Processor::exec_d(uint16_t opcode)
{
    // TODO: draw sprites
}

void Processor::exec_e(uint16_t opcode)
{
    // TODO: keyboard input
}

void Processor::exec_f(uint16_t opcode)
{
    // TODO: timers and sound
}

#pragma endregion

// Return false if we read a 0x0 byte (indicate termination)
bool Processor::ExecuteNext()
{
    // 2 bytes: mem[pc]+mem[pc+1]
    uint16_t opcode = (memory->read(pc) << 8) | memory->read(pc + 1);
    log(pc, opcode);

    // TODO: try to make this less appallingly ugly
    // process instruction
    bool jump = false;
    switch ((opcode >> 12) & 0xf)
    {
    case 0x0:
        jump = opcode != 0x00E0; // 0x00E0 is display clear, all others are jumps
        exec_0(opcode);
        break;
    case 0x1:
        jump = true;
        exec_1(opcode);
        break;
    case 0x2:
        jump = true;
        exec_2(opcode);
        break;
    case 0x3:
        exec_3(opcode);
        break;
    case 0x4:
        exec_4(opcode);
        break;
    case 0x5:
        exec_5(opcode);
        break;
    case 0x6:
        exec_6(opcode);
        break;
    case 0x7:
        exec_7(opcode);
        break;
    case 0x8:
        exec_8(opcode);
        break;
    case 0x9:
        exec_9(opcode);
        break;
    case 0xA:
        exec_a(opcode);
        break;
    case 0xB:
        jump = true;
        exec_b(opcode);
        break;
    case 0xC:
        exec_c(opcode);
        break;
    case 0xD:
        exec_d(opcode);
        break;
    case 0xE:
        exec_e(opcode);
        break;
    case 0xF:
        exec_f(opcode);
        break;
    }

    // increment pc iff we aren't branching/jumping
    if (!jump)
    {
        inc();
    }

    return opcode;
}