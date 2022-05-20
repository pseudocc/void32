#include <tty.h>
#include <stdlib>

tty_t* tty() {
  tty_t* p = malloc(sizeof(tty_t));
  if (p == NULL)
    return NULL;
  
  *p = stdout;
  return p;
}

void _tty(tty_t* this) {
  free(this);
}
