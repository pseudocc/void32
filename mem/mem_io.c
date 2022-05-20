#include <stdlib.h>
#include <mem.h>

void mem_read(ioparams_t* params) {
  mem_t* this;
  if (params == NULL)
    return;
  this = params->this;
  if (params->from > this->size)
    return;
  if (params->from + params->size > this->size)
    params->size = this->size - params->from;

  memcpy(buf, &this->data[from], params->size);
}

void mem_write(ioparams_t* params) {
  mem_t* this;
  if (params == NULL)
    return;
  this = params->this;
  if (params->from > this->size)
    return;
  if (params->from + params->size > this->size)
    params->size = this->size - params->from;
  
  memcpy(&this->data[from], buf, params->size);
}
