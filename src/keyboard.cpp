#include "keyboard.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <map>
using namespace std;

Keyboard::Keyboard()
{
    // TODO: Define these in a config somewhere

    this->key_mapping = {
        {0x0, SDL_SCANCODE_X},
        {0x1, SDL_SCANCODE_1},
        {0x2, SDL_SCANCODE_2},
        {0x3, SDL_SCANCODE_3},
        {0x4, SDL_SCANCODE_Q},
        {0x5, SDL_SCANCODE_W},
        {0x6, SDL_SCANCODE_E},
        {0x7, SDL_SCANCODE_A},
        {0x8, SDL_SCANCODE_S},
        {0x9, SDL_SCANCODE_D},
        {0xa, SDL_SCANCODE_Z},
        {0xb, SDL_SCANCODE_C},
        {0xc, SDL_SCANCODE_4},
        {0xd, SDL_SCANCODE_R},
        {0xe, SDL_SCANCODE_F},
        {0xf, SDL_SCANCODE_V},
    };
};

Keyboard::~Keyboard(){};

bool Keyboard::pressed(uint8_t key)
{
    return SDL_GetKeyboardState(NULL)[key_mapping[key & 0xf]];
}

uint8_t Keyboard::current()
{
    auto keyboard_state = SDL_GetKeyboardState(NULL);

    // iterate through all allowed keys
    for (auto const &key : key_mapping)
    {
        // if we find one pressed, return it
        if (keyboard_state[key.second])
        {
            return key.first;
        }
    }

    return 0x10;
}
