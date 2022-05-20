#include <stdlib.h>
#include <bus.h>

bus_t* bus() {
  bus_t* p;
  p = malloc(sizeof(bus_t));
  if (p == NULL)
    return NULL;
  
  p->cpu = cpu();
  p->n_devices = 0;
  pthread_mutex_init(&p->mutex, NULL);
  return p;
}

void _bus(bus_t* this) {
  if (this == NULL)
    return;

  pthread_mutex_destory(&this->mutex);
  _cpu(this->cpu);
  free(this);
}

void bus_install(bus_t* this, hw_t device) {
  if (this == NULL || this->n_devices >= N_DEVICES)
    return;
  
  this->devices[this->n_devices++] = device;
}
