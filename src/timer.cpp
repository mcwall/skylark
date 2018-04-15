#include "timer.h"

#include <iostream>

using namespace std;

Timer::Timer(uint16_t freq)
{
    this->start_val = 0;
    this->rate = 1000.0 / freq;
}

Timer::~Timer()
{
}

void Timer::set(uint16_t value)
{
    start_val = value;
    start_time = clock();
}

uint16_t Timer::get()
{
    if (start_val == 0)
        return 0;

    double ellapsed_ms = (clock() - start_time) / (CLOCKS_PER_SEC / 1000);
    double new_value = start_val - (ellapsed_ms / rate);

    // if the timer expired, don't bother re-caluculating next time until we reset
    if (new_value <= 0 || new_value > start_val)
        start_val = 0;

    return new_value;
}