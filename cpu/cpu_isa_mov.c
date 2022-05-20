#include "cpu/cpu_isa.h"

enum {
  LOAD_CONST,
  LOAD_REG,
  LOAD_MEMB,
  LOAD_MEMW,
  LOAD_MEMB,
  LOAD_MEMW,
  STORE_MEMB,
  STORE_MEMW
};

void isa_mov(inst_t inst, cpu_t* cpu, bus_t* bus) {
  operands_t ops = inst.operands;
  switch (inst.opcode.low) {
    case LOAD_CONST:
      *cpu_reg(cpu, ops.rd.r) = ops.d;
      break;
    case LOAD_REG:
      *cpu_reg(cpu, ops.rr.r0) = *cpu_reg(cpu, ops.rr.r1);
      break;
    case LOAD_MEMB:
      *cpu_reg(cpu, ops.rd.r) = 0;
      bus_read(bus, ops.rw.w, sizeof(byte_t), cpu_reg(cpu, ops.rd.r));
      break;
    case LOAD_MEMW:
      bus_read(bus, ops.rw.w, sizeof(word_t), cpu_reg(cpu, ops.rd.r));
      break;
    case STORE_MEMB:
      *cpu_reg(cpu, ops.rd.r) = 0;
      bus_write(bus, ops.rw.w, sizeof(byte_t), cpu_reg(cpu, ops.rd.r));
      break;
    case STORE_MEMW:
      bus_write(bus, ops.rw.w, sizeof(word_t), cpu_reg(cpu, ops.rd.r));
      break;
    default:
      break;
  }

  if (ops.rd.r != N_REGISTERS)
    cpu->pc += sizeof(inst_t);
}
