#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

int split(char **dest, char *src)
{
  char **dest_start = dest;

  *dest = strtok(src, SEPARATORS);
  while(*dest) {
    *++dest = strtok(NULL, SEPARATORS);
  }
  return dest - dest_start;
}

void clear_buf(void *buffer, size_t nmemb, size_t size)
{
  if(buffer != NULL)
    memset(buffer, 0, size * nmemb);
}

void print_tokens(char **tokens, int length)
{
  int i;
  for(i = 0; i < length; i++) {
    printf("%s ", tokens[i]);
  }
  printf("\n");
}

int main(int argc, char ** argv)
{
  char buf[MAX_BUFFER];                     // line buffer
  char *args[MAX_ARGS];                     // pointers to arg strings
  int args_len = 0;
  int buf_len = 0;
  char *prompt = "==> " ;    // shell prompt

  FILE *input = stdin;

  if(argc > 1) { /* reading from a file */
    char *file = argv[1];
    /* open file for reading */
    FILE *fp = fopen(file, "r");

    if(fp == NULL) {
      perror(file);
      exit(EXIT_FAILURE);
    }
    input = fp;
  }

  /* read from stdin or a file */
  while(1) {
    fputs(prompt, stdout);

    clear_buf(buf, buf_len == 0 ? MAX_BUFFER : buf_len, sizeof(char));
    clear_buf(args, args_len == 0 ? MAX_ARGS : args_len, sizeof(char *));

    if(fgets(buf, MAX_BUFFER, input) != NULL) {
      /* read a line word by word into args */
      args_len = split(args, buf);
    }
    print_tokens(args, args_len);
  }

  return 0;
}
