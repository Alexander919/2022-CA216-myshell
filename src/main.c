#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SEPARATORS " \t\n"                     /* token separators */

/* compile time constants */
enum {
  icmd_len = 8,       /* length of interal commands array */
  max_buffer = 1024,  /* max line buffer */
  max_args = 64       /* max number of args */
};
/* internal commands enum */
enum icmd             {  cd = 0,   clr,   dir,   environ,   echo,   help,   pause,   quit  };
const char *icmd[] =  { "cd", "clr", "dir", "environ", "echo", "help", "pause", "quit" };

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
/* return -1 if command not found, else enum icmd */
int get_icmd(char *command)
{
  int i;
  for(i = 0; i < icmd_len; i++) {
    if(strcmp(icmd[i], command) == 0)
      return i;
  }
  return -1;
}

void prompt(int is_file)
{
  char *prompt = "==> ";
  if(!is_file)
    fputs(prompt, stdout);
}

void quit_app()
{
  /* clean everything */
  printf("Bye.\n");
  exit(EXIT_SUCCESS);
}

void internal_cmd(char *command)
{
  enum icmd eicmd = get_icmd(command);

  switch(eicmd) {
    case cd:
      break;
    case clr:
      system("clear");
      break;
    case dir:
      system("ls -la");
      break;
    case environ:
      break;
    case echo:
      break;
    case help:
      break;
    case pause:
      break;
    case quit:
      quit_app();
      break;
    default:
      return;
  }
}

int main(int argc, char ** argv)
{
  char buf[max_buffer];
  char *args[max_args];

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

    clear_buf(buf, buf_len, max_buffer, sizeof(char));
    clear_buf(args, args_len, max_args, sizeof(char *));

    if(fgets(buf, max_buffer, input) != NULL) {
      /* read a line word by word into args */
      buf_len = strlen(buf);
      args_len = split(args, buf);
    } else {
      /* inspect fgets return value */
      if(feof(input)) { /* EOF */
        quit_app();
      }

      if(ferror(input)) { /* Error */
        perror("Reading error.");
        break;
      }
    }
#if 0
    print_tokens(args, args_len);
#endif
    internal_cmd(args[0]);

  }

  return 0;
}
/* handle Ctrl+C */
#if 0
 #include <stdio.h>
 #include <signal.h>

 volatile sig_atomic_t running = 1;

 void handle_signal(int sig)
 {
   (void) sig;
   running = 0;
 }

 int main(void)
 {
   if(signal(SIGINT, handle_signal) == SIG_ERR) {
     fprintf(stderr, "Cannot install signal handler\n");
     return 1;
   }

   printf("Press Ctrl+C to stop.\n");

   while(running) {
     /* Perform work */
   }

   printf("Program terminated gracefully.\n");

   return 0;
 }
 #endif
