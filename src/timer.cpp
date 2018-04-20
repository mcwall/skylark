#include "timer.h"

#include <ctime>
#include <chrono>
#include <iostream>
using namespace std::chrono;

Timer::Timer(uint8_t freq)
{
    this->start_val = 0;
    this->rate = 1000.0 / freq;
}

Timer::~Timer()
{
}

void Timer::set(uint8_t value)
{
    start_val = value;
    start_time = high_resolution_clock::now();
}

uint8_t Timer::get()
{
    if (start_val == 0)
        return 0;

    auto now = high_resolution_clock::now();

    double ellapsed_ms = duration_cast<milliseconds>(now - start_time).count();
    double new_value = start_val - (ellapsed_ms / rate);

    // if the timer expired, don't bother re-caluculating next time until we reset
    if (new_value <= 0 || new_value > start_val)
        start_val = 0;

    return new_value;
}