#include <stdlib.h>
#include <bus.h>

static hw_t* bus_find_device(bus_t* this, word_t addr) {
  byte_t i;
  hw_t* device;

  for (i = 0; i < this->n_devices; i++) {
    device = &this->devices[i];
    if (device->begin <= addr && addr < device->end)
      return device;
  }

  return NULL;
}

#define BUS_INLINE_IO(type) \
  hw_t* device;\
  ioparams_t params;\
  device = bus_find_device(this, from);\
  if (device == NULL)\
    return;\
  if (from + size > device->end) {\
    cpu_irq(this->cpu, 0x90, 0);\
    return;\
  }\
  params = {\
    .this = device->inst,\
    .bus = this,\
    .from = from - device->begin,\
    .size = size,\
    .buf = buf\
  };\
  if (device->type != NULL)\
    device->type(&params)

void bus_read(bus_t* this, word_t from, word_t size, vptr_t buf) {
  BUS_INLINE_IO(read);
}

void bus_write(bus_t* this, word_t from, word_t size, vptr_t buf) {
  BUS_INLINE_IO(write);
}
