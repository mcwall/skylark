#include "cpu.h"
#include "timer.h"
#include "mem.h"
#include <random>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <stdexcept>

using namespace std;

// TODO: Move this to consts file
const uint16_t FONT_OFFSET = 0x0;
const uint16_t FONT_WIDTH = 5;

const uint16_t STACK_MIN = 0xeA0;
// const uint16_t STACK_MAX = 0xfff;
const uint16_t STACK_MAX = 0x20;

Processor::Processor(Memory *memory, Timer *delay_timer, Timer *sound_timer, FrameBuffer *frame_buffer, Keyboard *keyboard)
{
    // TODO: Read from config or consts file, don't hardcode
    this->pc = 0x200;
    this->i = 0x0;
    this->v = vector<uint8_t>(16);
    // this->sp = STACK_MIN;
    this->s = stack<uint16_t>();
    this->wait = false;

    this->memory = memory;
    this->frame_buffer = frame_buffer;
    this->keyboard = keyboard;
    this->delay_timer = delay_timer;
    this->sound_timer = sound_timer;

    srand(time(NULL));
};

Processor::~Processor()
{
    free(memory);
    free(frame_buffer);

    memory = NULL;
    frame_buffer = NULL;
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
    // increment by 2 since mem words are 1-byte, but opcodes are 2-byte
    pc += 2;
}

void Processor::exec_0(uint16_t opcode)
{
    // clear display
    if (opcode == 0x00E0)
    {
        this->frame_buffer->clear();
        return;
    }

    // return from subroutine
    // if (opcode == 0x00EE)
    // {
    //     if (sp <= STACK_MIN)
    //         throw runtime_error("Stack underflow");

    //     pc = memory->read(--sp);
    //     return;
    // }

    // return from subroutine
    if (opcode == 0x00EE)
    {
        if (s.empty())
            throw runtime_error("Stack underflow");

        pc = s.top();
        s.pop();
        return;
    }

    throw runtime_error("Unsupported opcode");
}

void Processor::exec_1(uint16_t opcode)
{
    // jump
    pc = opcode & 0x0fff;
}

void Processor::exec_2(uint16_t opcode)
{
    // if (sp >= STACK_MAX)
    //     throw runtime_error("Stack overflow");

    // uint16_t n = opcode & 0xfff;
    // memory->write(sp++, pc);
    // pc = n;

    if (s.size() >= 0x20)
        throw runtime_error("Stack overflow");

    uint16_t n = opcode & 0xfff;
    s.push(pc);
    pc = n;
}

void Processor::exec_3(uint16_t opcode)
{
    // skip if v[x] == nn
    uint8_t x = (opcode >> 8) & 0xf;
    if (v[x] == (opcode & 0xff))
    {
        inc();
    }
}

void Processor::exec_4(uint16_t opcode)
{
    // skip if v[x] != nn
    uint8_t x = (opcode >> 8) & 0xf;
    if (v[x] != (opcode & 0xff))
    {
        inc();
    }
}

void Processor::exec_5(uint16_t opcode)
{
    // only valid opcode structure is 0x5XY0
    if (opcode & 0xF)
    {
        throw runtime_error("Invalid opcode");
    }

    uint8_t x = (opcode >> 8) & 0xf;
    uint8_t y = (opcode >> 4) & 0xf;

    // skip if v[x] == v[y]
    if (v[x] == v[y])
    {
        inc();
    }
}

void Processor::exec_6(uint16_t opcode)
{
    // v[x] = nn
    uint8_t x = (opcode >> 8) & 0xf;
    uint8_t n = opcode & 0xff;
    v[x] = n;
}

void Processor::exec_7(uint16_t opcode)
{
    // v[x] += nn
    uint8_t x = (opcode >> 8) & 0xf;
    uint8_t n = opcode & 0xff;
    v[x] += n;
}

void Processor::exec_8(uint16_t opcode)
{
    uint8_t x = (opcode >> 8) & 0xf;
    uint8_t y = (opcode >> 4) & 0xf;
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
    {
        unsigned int result = (unsigned int)v[x] + (unsigned int)v[y];
        v[0xf] = (uint8_t)((result >> 8) & 1); // carry flag
        v[x] = (uint8_t)result;
        break;
    }
    case 0x5:
    {
        int result = (unsigned int)v[x] - (unsigned int)v[y];
        v[0xf] = result < 0; // borrow flag
        v[x] = (uint8_t)result;
        break;
    }
    case 0x6:
    {
        v[0xf] = v[y] & 1; // LSB of v[y]
        uint8_t result = v[y] >> 1;
        v[x] = result;
        v[y] = result;
        break;
    }
    case 0x7:
    {
        int result = (unsigned int)v[y] - (unsigned int)v[x];
        v[0xf] = result < 0; // borrow flag
        v[x] = (uint8_t)result;
        break;
    }
    case 0xE:
    {
        v[0xf] = (v[y] >> 7) & 1; // MSB of v[y]
        uint8_t result = v[y] << 1;
        v[x] = result;
        v[y] = result;
        break;
    }
    default:
        throw runtime_error("Invalid opcode");
    }
}

void Processor::exec_9(uint16_t opcode)
{
    // only valid opcode structure is 0x9XY0
    if (opcode & 0xF)
    {
        throw runtime_error("Invalid opcode");
    }

    uint8_t x = (opcode >> 8) & 0xf;
    uint8_t y = (opcode >> 4) & 0xf;

    // skip if v[x] != v[y]
    if (v[x] != v[y])
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
    // vx = rand()
    uint8_t x = (opcode >> 8) & 0xf;
    uint8_t n = opcode & 0xff;
    v[x] = (rand() % 256) & n;
}

void Processor::exec_d(uint16_t opcode)
{
    // draw

    uint8_t x = (opcode >> 8) & 0xf;
    uint8_t y = (opcode >> 4) & 0xf;
    uint8_t h = opcode & 0xf;

    vector<uint8_t> sprite(h);
    for (int n = 0; n < h; n++)
        sprite[n] = memory->read(i + n);

    v[0xf] = frame_buffer->draw(v[x], v[y], sprite) ? 1 : 0;
}

void Processor::exec_e(uint16_t opcode)
{
    uint8_t x = (opcode >> 8) & 0xf;

    switch (opcode & 0xff)
    {
    case 0x9e:
        // skip if key pressed
        if (keyboard->pressed(v[x]))
            inc();
        break;
    case 0xa1:
        // skip if key not pressed
        if (!keyboard->pressed(v[x]))
            inc();
        break;
    default:
        throw runtime_error("Invalid opcode");
    }
}

void Processor::exec_f(uint16_t opcode)
{
    // TODO: timers and sound
    uint8_t x = (opcode >> 8) & 0xf;

    switch (opcode & 0xff)
    {
    case 0x07:
        // v[x] = get_timer()
        v[x] = delay_timer->get();
        break;
    case 0x0A:
    {
        // wait for key press
        uint8_t key_pressed = keyboard->current();
        if (key_pressed < 0x10)
        {
            // key actually pressed
            wait = false;
            v[x] = key_pressed & 0xf;
        }
        else
        {
            // key not pressed, wait for next key press
            wait = true;
        }
        break;
    }
    case 0x15:
        // set_timer(v[x])
        delay_timer->set(v[x]);
        break;
    case 0x18:
        // set_sound_timer(v[x])
        sound_timer->set(v[x]);
        break;
    case 0x1E:
        // I += v[x]
        i += v[x];
        break;
    case 0x29:
        i = FONT_OFFSET + (FONT_WIDTH * v[x]);
        break;
    case 0x33:
    {
        memory->write(i, 1);     // throw runtime_error("BCD not implemented");
        memory->write(i + 1, 2); // throw runtime_error("BCD not implemented");
        memory->write(i  +2, 3);     // throw runtime_error("BCD not implemented");
        break;
    }
    case 0x55:
        for (int k = 0; k <= x; k++)
            memory->write(i++, v[k]);
        break;
    case 0x65:
        for (int k = 0; k <= x; k++)
            v[k] = memory->read(i++);
        break;
    default:
        throw runtime_error("Invalid opcode");
        break;
    }
}

#pragma endregion

// return false if we read a 0x0 byte (indicate termination)
void Processor::ExecuteNext()
{
    // 2 bytes: mem[pc]+mem[pc+1]
    uint16_t opcode = (memory->read(pc) << 8) | memory->read(pc + 1);
    // log(pc, opcode);

    // TODO: try to make this less ugly
    // process instruction
    bool jump = false;
    switch ((opcode >> 12) & 0xf)
    {
    case 0x0:
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
    if (!jump && !wait)
    {
        inc();
    }
}