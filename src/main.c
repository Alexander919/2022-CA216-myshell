#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024                        /* max line buffer */
#define MAX_ARGS 64                            /* max # args */
#define SEPARATORS " \t\n"                     /* token separators */

int split(char **dest, char *src)
{
  char **dest_start = dest;

  *dest = strtok(src, SEPARATORS);
  while(*dest) {
    *++dest = strtok(NULL, SEPARATORS);
  }
  return dest - dest_start;
}
/* set buffer to all \0 */
void clear_buf(void *buffer, size_t nmemb, size_t max_nmemb, size_t size)
{
  if(buffer != NULL)
    memset(buffer, 0, (nmemb == 0 ? max_nmemb : nmemb) * size);
}

void print_tokens(char **tokens, int length)
{
  int i;
  for(i = 0; i < length; i++) {
    printf("%s ", tokens[i]);
  }
  printf("\n");
}
/* print chars irrespective of \0 if len > 0 */
void print_char_values(char *chars, int len)
{
  int i;
  if(len <= 0) /* don't know the length, print until \0 */
    while(*chars) {
      printf("%d ", *chars++);
      len++;
    }
  else
    for(i = 0; i < len; i++) {
      printf("%d ", chars[i]);
    }
  printf("\nLength of chars = %d\n", len);
}

void prompt(int is_file)
{
  char *prompt = "==> ";
  if(!is_file)
    fputs(prompt, stdout);
}

int main(int argc, char ** argv)
{
  char buf[MAX_BUFFER];
  char *args[MAX_ARGS];

  int buf_len = 0;
  int args_len = 0;
  int is_file = 0;

  FILE *input = stdin;

  if(argc > 1) { /* reading from a file */
    char *file = argv[1];
    /* open file for reading */
    FILE *fp = fopen(file, "r");

    if(fp == NULL) {
      perror(file);
      exit(EXIT_FAILURE);
    }
    is_file = 1;
    input = fp;
  }

  /* read from stdin or a file */
  while(1) {
    prompt(is_file);

    clear_buf(buf, buf_len, MAX_BUFFER, sizeof(char));
    clear_buf(args, args_len, MAX_ARGS, sizeof(char *));

    if(fgets(buf, MAX_BUFFER, input) != NULL) {
      /* read a line word by word into args */
      buf_len = strlen(buf);
      args_len = split(args, buf);
    } else {
      /* inspect fgets return value */
      if(is_file && feof(input)) { /* EOF */
        printf("End of File\n");
        goto abort;
      }

      if(ferror(input)) { /* Error */
        perror("Reading error.");
      }
      abort: break;
    }

    print_tokens(args, args_len);

  }

  return 0;
}
