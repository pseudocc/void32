#ifndef VOID32_CPU_H
#define VOID32_CPU_H

#include <bus.h>
#include <vtypes.h>

#define N_REGISTERS 16
#define N_IRQS 8
#define N_CYCLES 8

#define IRQ_BACKUP 0x000001000
#define IRQ_RESTORE 0x000001004

#define IVT_ADDR 0x000001000
#define PROG_EXIT 0xFFFFFFFF

typedef struct irq_node {
  byte_t opcode;
  word_t data;
} irq_node_t;

typedef struct {
  u64_t clock;

  word_t pc;
  word_t sp;

  word_t regs[N_REGISTERS];
  irq_node_t irqs[N_IRQS];
  
  byte_t n_irqs;

  struct {
    byte_t ZF : 1;
    byte_t SF : 1;
    byte_t IF : 1;
  } flags;

  byte_t cycles;
} cpu_t;

cpu_t* cpu();
void _cpu(cpu_t* this);

void cpu_tick(cpu_t* this, bus_t* b);
byte_t cpu_irq(cpu_t* this, byte_t opcode, word_t data);

#endif
