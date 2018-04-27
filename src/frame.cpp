#include "frame.h"
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

bool FrameBuffer::draw(int x, int y, vector<uint8_t> sprite)
{
    // TODO: be smarter about when to mark changes, since it causes an expensive re-render
    changed = true;

    // TODO: Clean this up a bit

    bool result = false;
    for (int i = 0; i < sprite.size(); i++)
    {
        uint8_t row = sprite[i];
        for (int j = 0; j < 8; j++)
        {
            // if the j-th pixel is set, flip the corresponding pixel
            if ((row & (0x80 >> j)) != 0)
            {
                uint8_t frame_x = (x + j) % w;
                uint8_t frame_y = (y + i) % h;
                if (buffer[frame_x][frame_y])
                {
                    result = true;
                    buffer[frame_x][frame_y] = false;
                }
                else
                {
                    buffer[frame_x][frame_y] = true;
                }
            }
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
