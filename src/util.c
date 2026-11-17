#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size)
{
  void *ptr = malloc(size);

  if(ptr == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  return ptr;
}
