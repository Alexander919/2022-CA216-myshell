#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void *xmalloc(size_t nmemb, size_t size)
{
  return xrealloc(NULL, nmemb, size);
}

void *xrealloc(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;

  if(nmemb == 0 || size == 0) {
    free(ptr);
    return NULL;
  }

  if(nmemb > SIZE_MAX / size) {
    errno = ENOMEM;
    perror("realloc");
    exit(EXIT_FAILURE);
  }

  new_ptr = realloc(ptr, nmemb * size);
  if(new_ptr == NULL) {
    perror("realloc");
    exit(EXIT_FAILURE);
  }

  return new_ptr;
}

int is_whitespace(char ch)
{
  return ch == ' ' || ch == '\t';
}

int is_end(char ch)
{
  return ch == '\0' || ch == '\n';
}
