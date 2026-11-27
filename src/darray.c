#include "darray.h"
#include <stdlib.h>

/* return current length */
int darray_push(Darray *darr, void *member)
{
  /* need to allocate more memory */
  if(darr->index == darr->length) {
    /* double the memory */
    size_t new_len = darr->length * 2;

    darr->value = xrealloc(darr->value, new_len, sizeof(*darr->value));
    darr->length = new_len; /* update length */
  }

  darr->value[darr->index++] = member;

  return darr->index;
}

Darray *darray_create(void)
{
  Darray *darr = xmalloc(1, sizeof(Darray));
  darr->index = 0;
  darr->length = darray_init_length;
  darr->value = xmalloc(darr->length, sizeof(*darr->value));

  return darr;
}

size_t darray_count(const Darray *darr)
{
  return darr->index;
}

int darray_get(const Darray *darr, size_t i, void **out)
{
  if(i < darr->index) {
    *out = darr->value[i];
    return 1;
  }
  return 0;
}
/* caller must call free */
int darray_pop(Darray *darr, void **out)
{
  if(darr->index == 0)
    return 0;

  *out = darr->value[--darr->index];

  return 1;
}

void darray_destroy(Darray *darr, void (*clean)(void *))
{
  if(darr != NULL) {
    if(darr->value != NULL) {
      size_t i;
      for(i = 0; i < darr->index; i++) {
        clean(darr->value[i]);
      }
      free(darr->value);
    }
    free(darr);
  }
}

void darray_print(Darray *darr, void (*cb)(void *elem))
{
  size_t i;
  for(i = 0; i < darr->index; i++) {
    cb(darr->value[i]);
  }
}
