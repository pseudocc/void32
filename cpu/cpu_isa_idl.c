#include "cpu/cpu_isa.h"

void isa_idl(cpu_t* cpu) {
  cpu->pc += sizeof(opcode_t);
}
