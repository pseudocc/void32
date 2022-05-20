#ifndef VOID32_CPU_ISA_H
#define VOID32_CPU_ISA_H

#include <cpu.h>

typedef union __attribute__((packed)) {
  struct __attribute__((packed)) {
    word_t d;
    byte_t r;
  } dr;
  struct __attribute__((packed)) {
    byte_t r;
    word_t d;
  } rd;
  struct __attribute__((packed)) {
    byte_t r0;
    byte_t r1;
  } rr;
  word_t d;
  byte_t r;
} operands_t;

typedef struct {
  byte_t low : 4;
  byte_t high: 4;
} opcode_t;

typedef struct __attribute__((packed)) {
  opcode_t opcode;
  operands_t operands;
} inst_t;

enum {
  OP_MOV,
  OP_ARI,
  OP_JMP,
  OP_INT,
  OP_CLI,
  OP_IDL
};

word_t* cpu_reg(cpu_t* cpu, byte_t ri);
void isa_mov(inst_t inst, cpu_t* cpu, bus_t* bus);
void isa_ari(inst_t inst, cpu_t* cpu);
void isa_jmp(inst_t inst, cpu_t* cpu);
void isa_int(inst_t inst, cpu_t* cpu, bus_t* bus);
void isa_cli(cpu_t* cpu);
void isa_idl(cpu_t* cpu);

#endif