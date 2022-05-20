#include <mem.h>
#include <stdlib>

mem_t* mem(byte_t* data, word_t size) {
  mem_t* p = malloc(sizeof(mem_t));
  if (p == NULL)
    return NULL;
  
  p->data = data;
  p->size = size;

  return p;
}

void _mem(mem_t* this) {
  free(this);
}
