#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ctime>
#include <iostream>
using namespace std::chrono;

class Timer
{
public:
  Timer(uint8_t freq);
  ~Timer();

  void set(uint8_t value);
  uint8_t get();

  private:
    double rate;
    uint8_t start_val;
    high_resolution_clock::time_point start_time;
};

#endif
