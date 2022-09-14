#include <cstdio>
#include "newtop.h"
#include <stdlib.h>
#include <cstring>
#include <cassert>

extern uint8_t program_start, program_end;
uint8_t* program = &program_start;
int program_sz;

newtop cpu;

int main(int argc, char** argv) {
  // Load program
  program_sz = (int)(&program_end - &program_start);
  memcpy(cpu.mem.ram, program, program_sz);

  // Reset and flush design
  cpu.reset = UInt<1>(1);
  cpu.eval(false, false, false);
  for (int i = 0; i < 5; i++) {
    cpu.eval(true, false, false);
    cpu.reset = UInt<1>(0);
    cpu.eval(false, false, false);
  }

  while(1){
    cpu.eval(true, true, true);
    if(cpu.cpu.writeback.valid_r && (cpu.cpu.writeback.inst_r.as_single_word() == 0x6b)){
      if(cpu.cpu.regs.regs_10.as_single_word() == 0)
        printf("\33[1;32mCPU HIT GOOD TRAP\033[0m\n");
      else
        printf("\33[1;31mCPU HIT BAD TRAP\033[0m\n");
      break;
    }
  }

  return 0;
}