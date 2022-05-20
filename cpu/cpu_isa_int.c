#include "cpu/cpu_isa.h"

void isa_int(inst_t inst, cpu_t* cpu, bus_t* bus) {
  word_t pc;

  pc = cpu->pc;
  cpu->flags.IF = 1;
  cpu->pc = IRQ_BACKUP;
  while (cpu->pc != PROG_EXIT)
    cpu_tick(cpu, bus);

  cpu->pc = inst.operands.w;
  while (cpu->pc != PROG_EXIT)
    cpu_tick(cpu, bus);

  cpu->pc = IRQ_RESTORE;
  while (cpu->pc != PROG_EXIT)
    cpu_tick(cpu, bus);
  cpu->pc = pc + sizeof(inst_t);
}
