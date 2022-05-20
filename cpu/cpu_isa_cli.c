#include "cpu/cpu_isa.h"

void isa_cli(cpu_t* cpu) {
  cpu->flags.IF = 0;
  cpu->pc += sizeof(opcode_t);
}
