#include "display.h"
#include <iostream>

DisplayBuffer::DisplayBuffer(int width, int height)
{
    this->width = width;
    this->height = height;

    this->buffer = new bool *[width];
    for (int x = 0; x < width; x++)
    {
        this->buffer[x] = new bool[height];
        for (int y = 0; y < height; y++)
            this->buffer[x][y] = false;
    }
}

DisplayBuffer::~DisplayBuffer()
{
}

bool DisplayBuffer::Draw(int x, int y, bool value)
{
    const bool origScreenPixel = this->buffer[x][y];
    this->buffer[x][y] ^= value;

    // true iff screen pixel was flipped from set to unset
    return origScreenPixel && !this->buffer[x][y];
}

void DisplayBuffer::Clear()
{
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            buffer[x][y] = false;
}

int DisplayBuffer::getWidth()
{
    return width;
}

int DisplayBuffer::getHeight()
{
    return height;
}

bool DisplayBuffer::get(int x, int y)
{
    return buffer[x][y];
}

// bool DisplayBuffer::DrawSprite(Sprite *sprite)
// 	{
// 		// TODO: Implement sprites
// 	}