#include "cpu/cpu_isa.h"

void cpu_tick(cpu_t* this, bus_t* bus) {
  byte_t i;
  inst_t inst;
  
  bus_read(bus, this->pc, sizeof(inst), &inst);
  switch (inst.opcode.high) {
    case OP_MOV:
      isa_mov(inst, this, bus);
      break;
    case OP_ARI:
      isa_ari(inst, this, bus);
      break;
    case OP_JMP:
      isa_jmp(inst, this);
      break;
    case OP_INT:
      isa_int(inst, this, bus);
      break;
    case OP_CLF:
      isa_cli(this);
      break;
    case OP_IDL:
    default:
      isa_idl(this);
      break;
  }

  if (this->flags.IF == 0 && ++this->cycles == N_CYCLES) {
    this->cycles = 0;
    for (i = 0; i < this->n_irqs; i++) {
      inst.opcode.low = this->irqs[i].opcode;
      inst.operands.d = this->irqs[i].data;
      isa_int(inst, this, bus);
    }
    this->flags.IF == 0;
  }

  this->clock++;
}

word_t* cpu_reg(cpu_t* cpu, byte_t ri) {
  i32_t i;
  if (ri < N_REGISTERS)
    i = ri;
  else {
    switch (ri) {
    case N_REGISTERS:
      i = -2;
      break;
    case N_REGISTERS + 1:
      i = -1;
      break;
    default:
      i = N_REGISTERS - 1;
      break;
    }
  }
  return &cpu->regs[i];
}
