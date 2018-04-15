#ifndef CPU_H
#define CPU_H

#include "timer.h"
#include "mem.h"
#include "frame.h"
#include <vector>

using namespace std;

class Processor
{
public:
  Processor(Memory *memory, Timer *delay_timer, Timer *sound_timer, FrameBuffer *frame_buffer);
  ~Processor();

  bool ExecuteNext();

private:
  Memory *memory;
  Timer *delay_timer;
  Timer *sound_timer;
  FrameBuffer *frame_buffer;

  uint16_t pc;
  uint16_t i;
  vector<uint8_t> v;

  void inc();

  void exec_0(uint16_t opcode);
  void exec_1(uint16_t opcode);
  void exec_2(uint16_t opcode);
  void exec_3(uint16_t opcode);
  void exec_4(uint16_t opcode);
  void exec_5(uint16_t opcode);
  void exec_6(uint16_t opcode);
  void exec_7(uint16_t opcode);
  void exec_8(uint16_t opcode);
  void exec_9(uint16_t opcode);
  void exec_a(uint16_t opcode);
  void exec_b(uint16_t opcode);
  void exec_c(uint16_t opcode);
  void exec_d(uint16_t opcode);
  void exec_e(uint16_t opcode);
  void exec_f(uint16_t opcode);
};

#endif
