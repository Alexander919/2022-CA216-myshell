#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *xmalloc(size_t nmemb, size_t size)
{
  void *ptr = malloc(size * nmemb);

  if(ptr == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  return ptr;
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

enum {
  darray_init_length = 8
};
/* dynamic array */
struct darray {
  size_t index;         /* current index inside the array */
  size_t length;        /* total length of the array */
  void *value;          /* array of values */
  size_t value_size;    /* size of one value element in bytes */
};

typedef struct darray Darray;

/* return current length */
int darray_push(Darray *darr, void *member)
{
  /* need to allocate more memory */
  if(darr->index == darr->length) {
    /* double the memory */
    size_t new_len = darr->length * 2;

    darr->value = xrealloc(darr->value, new_len, darr->value_size);
    darr->length = new_len; /* update length */
  }
  memcpy((char *) darr->value + darr->index * darr->value_size, member, darr->value_size);

  return ++darr->index;
}

Darray *darray_create(size_t member_size)
{
  Darray *darr = xmalloc(1, sizeof(Darray));
  darr->index = 0;
  darr->length = darray_init_length;
  darr->value = xmalloc(darray_init_length, member_size);
  darr->value_size = member_size;

  return darr;
}

void darray_destroy(Darray *darr)
{
  if(darr != NULL) {
    if(darr->value != NULL) {
      size_t i;
      char *bytes = darr->value;
      for(i = 0; i < darr->index; i++) {
        bytes = bytes + i * darr->value_size;
        free(bytes);
      }
      free(darr->value);
    }
    free(darr);
  }
}
