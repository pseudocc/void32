#ifndef VOID32_BUS_H
#define VOID32_BUS_H

#include <cpu.h>
#include <pthread.h>

typedef void (*hwio_t)(ioparams_t*);

typedef struct {
  word_t begin;
  word_t end;
  hwio_t read;
  hwio_t write;
  vptr_t inst;
} hw_t;

typedef struct {
  vptr_t this;
  bus_t* bus;
  word_t from;
  word_t size;
  byte_t buf;
} ioparams_t;

#define N_DEVICES 8

typedef struct {
  cpu_t* cpu;
  pthread_mutex_t mutex;
  hw_t devices[N_DEVICES];
  byte_t n_devices;
} bus_t;

bus_t* bus();
void _bus(bus_t* this);

void bus_install(bus_t* this, hw_t device);

void bus_read(bus_t* this, word_t from, word_t size, vptr_t buf);
void bus_write(bus_t* this, word_t from, word_t size, vptr_t buf);

#endif
