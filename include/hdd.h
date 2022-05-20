#ifndef VOID32_HDD_H
#define VOID32_HDD_H

#include <stdio.h>
#include <bus.h>

typedef struct {
  FILE* file;
  word_t size;
} hdd_t;

hdd_t* hdd(FILE* file, word_t size);
void _hdd(hdd_t* this);

void hdd_read(ioparams_t* params);
void hdd_write(ioparams_t* params);

#endif
