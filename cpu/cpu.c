#include <stdlib.h>
#include <cpu.h>

cpu_t* cpu() {
  cpu_t* p;
  byte_t i;

  p = malloc(sizeof(cpu_t));
  if (p == NULL)
    return NULL;
  
  p->clock = 0;
  p->pc = 0;
  p->sp = 0;

  p->n_irqs = 0;

  p->flags = {
    .ZF = 0,
    .SF = 0,
    .IF = 0
  };

  p->cycles = 0;

  return p;
}

void _cpu(cpu_t* this) {
  free(this);
}

byte_t cpu_irq(cpu_t* this, byte_t opcode, word_t data) {
  byte_t next_free, last_used;
  if (this->n_irqs >= N_IRQS)
    return 0;
  
  this->irqs[this->n_irqs++] = {
    .opcode = opcode,
    .data = data
  };

  return 1;
}
