#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t nmemb, size_t size)
{
  void *ptr = malloc(size * nmemb);

  if(ptr == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

int is_whitespace(char ch)
{
  return ch == ' ' || ch == '\t';
}

int is_end(char ch)
{
  return ch == '\0' || ch == '\n';
}
