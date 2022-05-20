#ifndef VOID32_MEM_H
#define VOID32_MEM_H

#include <bus.h>

typedef struct {
  byte_t* data;
  word_t size;
} mem_t;

mem_t* mem(byte_t* data, word_t size);
void _mem(mem_t* this);

void mem_read(ioparams_t* params);
void mem_write(ioparams_t* params);

#endif
