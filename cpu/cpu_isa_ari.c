#include "cpu/cpu_isa.h"

enum {
  ADD,
  SUB,
  MUL,
  DIV,
  AND,
  OR,
  XOR,
  FADD,
  FSUB,
  FMUL,
  FDIV
};

void isa_ari(inst_t inst, cpu_t* cpu) {
  operands_t ops = inst.operands;
  vptr_t lhs, rhs;
  word_t t;

  lhs = cpu_reg(cpu, ops.rr.r0);
  rhs = cpu_reg(cpu, ops.rr.r1);

  switch (inst.opcode.low) {
  case ADD:
    *(word_t*)lhs = *(word_t*)lhs + *(word_t*)rhs;
    break;
  case SUB:
    *(word_t*)lhs = *(word_t*)lhs - *(word_t*)rhs;
    break;
  case MUL:
    *(word_t*)lhs = *(word_t*)lhs * *(word_t*)rhs;
    break;
  case DIV:
    t = *(word_t*)lhs / *(word_t*)rhs;
    *(word_t*)rhs = *(word_t*)lhs % *(word_t*)rhs;
    *(word_t*)lhs = t;
    break;
  case AND:
    *(word_t*)lhs = *(word_t*)lhs & *(word_t*)rhs;
    break;
  case OR:
    *(word_t*)lhs = *(word_t*)lhs | *(word_t*)rhs;
    break;
  case XOR:
    *(word_t*)lhs = *(word_t*)lhs ^ *(word_t*)rhs;
    break;
  case FADD:
    *(word_t*)lhs = *(word_t*)lhs + *(word_t*)rhs;
    break;
  case FSUB:
    *(f32_t*)lhs = *(f32_t*)lhs - *(f32_t*)rhs;
    break;
  case FMUL:
    *(f32_t*)lhs = *(f32_t*)lhs * *(f32_t*)rhs;
    break;
  case FDIV:
    *(f32_t*)lhs = *(f32_t*)lhs / *(f32_t*)rhs;
    break;
  }

  cpu->pc += sizeof(opcode_t) + sizeof(inst.operands.rr);
}
