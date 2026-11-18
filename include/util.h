#ifndef UTIL_H_SENTRY
#define UTIL_H_SENTRY

#include <stddef.h>

/* compile time constants */
enum {
  icmd_len = 8,       /* length of interal commands array */
  max_buffer = 1024,  /* max line buffer */
  max_args = 64,      /* max number of args */
  max_data = 512
};

void *xmalloc(size_t nmemb, size_t size);

#endif
