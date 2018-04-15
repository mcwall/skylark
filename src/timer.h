#ifndef TIMER_H
#define TIMER_H

#include <iostream>
using namespace std;

class Timer
{
public:
  Timer(uint16_t freq);
  ~Timer();

  void set(uint16_t value);
  uint16_t get();

  private:
    double rate;
    uint16_t start_val;
    clock_t start_time;
};

#endif
