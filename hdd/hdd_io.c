#include <stdlib>
#include <pthread.h>
#include <hdd.h>
#include <kernel.h>

static void vf_read(ioparams_t* params) {
  hdd_t* this;
  word_t n_bytes;
  if (params == NULL)
    return;
  pthread_mutex_lock(params->bus->mutex);
  this = params->this;
  fseek(this->file, params->from, SEEK_SET);
  n_bytes = fread(params->buf, sizeof(byte_t), params->size, this->file);
  while (!cpu_irq(bus->cpu, HDD_R_IDLE, n_bytes));
  pthread_mutex_unlock(params->bus->mutex);
}

static void vf_write(ioparams_t* params) {
  hdd_t* this;
  if (params == NULL)
    return;
  pthread_mutex_lock(params->bus->mutex);
  this = params->this;
  fseek(this->file, params->from, SEEK_SET);
  n_bytes = fwrite(params->buf, sizeof(byte_t), params->size, this->file);
  while (!cpu_irq(bus->cpu, HDD_W_IDLE, key));
  pthread_mutex_unlock(params->bus->mutex);
}

void hdd_read(ioparams_t* params) {
  pthread_t thread;
  pthread_create(&thread, NULL, vf_read, params); 
}

void hdd_write(ioparams_t* params) {
  pthread_t thread;
  pthread_create(&thread, NULL, vf_write, params); 
}
