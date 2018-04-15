#include "display.h"
#include <iostream>
#include <vector>

using namespace std;

FrameBuffer::FrameBuffer(int width, int height)
{
    this->w = width;
    this->h = height;
    this->buffer = vector<vector<bool>>(width, vector<bool>(height));
}

FrameBuffer::~FrameBuffer()
{
    for (int x = 0; x < w; x++)
        buffer[x].clear();

    buffer.clear();
}

void FrameBuffer::clear()
{
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            buffer[x][y] = false;
}

bool FrameBuffer::draw(int x, int y, bool value)
{
    // TODO: be smarter about when to mark changes, since it causes an expensive re-render
    changed = true;
    const bool origScreenPixel = buffer[x][y];
    
    buffer[x][y] = buffer[x][y] ^ value;

    // true iff screen pixel was flipped from set to unset
    return origScreenPixel && !buffer[x][y];
}

bool FrameBuffer::draw(int x, int y, vector<uint8_t> sprite)
{
    // TODO: be smarter about when to mark changes, since it causes an expensive re-render
    changed = true;

    bool result = false;
    for (int i = 0; i < sprite.size(); i++)
    {
        uint8_t row = sprite[i];
        for (int j = 0; j < 8; j++)
        {
            bool value = (row << j) & 0x80;
            result = draw((x + j) % w, (y + i) % h, value) && result;
        }
    }

    return result;
}

void FrameBuffer::begin_frame()
{
    changed = false;
}

bool FrameBuffer::has_changes()
{
    return changed;
}

int FrameBuffer::width()
{
    return w;
}

int FrameBuffer::height()
{
    return h;
}

bool FrameBuffer::get(int x, int y)
{
    return buffer[x][y];
}
