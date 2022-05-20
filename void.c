#include <stdio.h>
#include <stdlib.h>
#include <bus.h>
#include <kernel.h>

void tty_bind_keyboard(bus_t* bus) {
  int c;
  while ((c = getc(stdin)) != EOF) {
    pthread_mutex_lock(bus->mutex);
    tty_key(bus, (byte_t)c);
    pthread_mutex_unlock(bus->mutex);
  }
}

void boot(bus_t* b) {
  byte_t buf[1024];
  word_t offset, bytes_read;
  FILE* f;
  
  f = fopen('kernel.img', 'r');
  offset = MEM_BEGIN;
  do {
    bytes_read = fread(buf, sizeof(byte_t),
      sizeof(buf) / sizeof(byte_t), f);
    bus_write(b, offset, bytes_read, buf);
    offset += bytes_read;
  } while (bytes_read);
}

int main(void) {
  int i;
  bus_t* b;
  mem_t* m;
  tty_t* t;
  hdd_t* d;
  hw_t hws[3];
  pthread_t tty_listener;

  b = bus();
  m = mem();
  t = tty();
  d = hdd();

  hws[0] = {
    .begin = MEM_BEGIN,
    .end = MEM_END,
    .read = &mem_read,
    .write = &mem_write,
    .inst = m
  };
  
  hws[1] = {
    .begin = TTY_BEGIN,
    .end = TTY_END,
    .read = NULL,
    .write = &tty_write,
    .inst = t
  };
  
  hws[2] = {
    .begin = HDD_BEGIN,
    .end = HDD_END,
    .read = &hdd_read,
    .write = &hdd_write,
    .inst = d
  };

  for (i = 0; i < sizeof(hws) / sizeof(hw_t); i++)
    bus_install(b, hws[i]);

  boot(b);
  pthread_create(&tty_listener, NULL, tty_bind_keyboard, b);
  while (b->cpu->pc != PROG_EXIT)
    cpu_tick(b->cpu, b);
  
  _bus(b);
  _mem(m);
  _tty(t);
  _hdd(h);

  return 0;
}
