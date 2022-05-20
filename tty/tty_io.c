#include <tty.h>
#include "cpu/cpu_isa.h"

void tty_key(bus_t* bus, byte_t key) {
  while (!cpu_irq(bus->cpu, OP_INT, key));
}

void tty_write(ioparams_t* params) {
  fputs(params->buf, params->this);
}
