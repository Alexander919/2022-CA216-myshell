#ifndef DARRAY_H_SENTRY
#define DARRAY_H_SENTRY

#include "util.h"
enum {
  darray_init_length = 8
};

/* dynamic array */
struct darray {
  size_t index;         /* current index inside the array */
  size_t length;        /* total length of the array */
  void **value;         /* array of values */
};

typedef struct darray Darray;

int darray_push(Darray *darr, void *member);
Darray *darray_create(void);
size_t darray_count(const Darray *darr);
int darray_get(const Darray *darr, size_t i, void **out);
int darray_pop(Darray *darr, void **out);
void darray_destroy(Darray *darr, void (*clean)(void *));
void darray_print(Darray *darr, void (*cb)(void *elem));
#endif
