#include <hdd.h>
#include <stdlib>

hdd_t* hdd(FILE* file, word_t size) {
  hdd_t* p = malloc(sizeof(hdd_t));
  if (p == NULL)
    return NULL;
  
  p->file = file;
  p->size = size;

  return p;
}

void _hdd(hdd_t* this) {
  free(this);
}
