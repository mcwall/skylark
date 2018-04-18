#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include <SDL2/SDL.h>
#include <map>
using namespace std;

class Keyboard
{
  public:
    Keyboard();
    ~Keyboard();

    // return whether the key is pressed
    bool pressed(uint8_t key);

    // return the currently pressed key (or 0x10 if none pressed)
    uint8_t current();

  private:
    map<uint8_t, SDL_Scancode> key_mapping;
};

#endif