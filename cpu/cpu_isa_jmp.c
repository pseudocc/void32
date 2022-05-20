#include "cpu/cpu_isa.h"

enum {
  JUMP_ALWAYS,
  JUMP_EQ,
  JUMP_NEQ,
  JUMP_LT,
  JUMP_NLT,
  JUMP_GT,
  JUMP_NGT
};

void isa_jmp(inst_t inst, cpu_t* cpu, bus_t* bus) {
  operands_t ops = inst.operands;
  byte_t jump = 0;
  switch (inst.opcode.low & 0x7) {
    case JUMP_ALWAYS:
      jump = 1;
      break;
    case JUMP_EQ:
      jump = !cpu->flags.ZF;
      break;
    case JUMP_NEQ:
      jump = cpu->flags.ZF;
      break;
    case JUMP_LT:
      jump = cpu->flags.ZF && cpu->flags.SF;
      break;
    case JUMP_NLT:
      jump = !cpu->flags.ZF || !cpu->flags.SF;
      break;
    case JUMP_GT:
      jump = cpu->flags.ZF && !cpu->flags.SF;
      break;
    case JUMP_NGT:
      jump = !cpu->flags.ZF || cpu->flags.SF;
      break;
    default:
      break;
  }

  if (jump) {
    if (inst.opcode.low & 0x8)
      cpu->pc = cpu->pc + ops.w;
    else
      cpu->pc = ops.w;
  }
  else
    cpu->pc += sizeof(opcode_t);
}