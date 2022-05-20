#ifndef VOID32_TTY_H
#define VOID32_TTY_H

#include <bus.h>
#include <stdio>

#define TTY_MAXLEN 1024

typedef FILE* tty_t;

tty_t* tty();
void _tty(tty_t* this);

void tty_key(bus_t* bus, byte_t key);
void tty_write(ioparams_t* params);

#endif
