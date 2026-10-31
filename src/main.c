#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

#define SEPARATORS " \t\n"                     /* token separators */
extern char **environ;
/* compile time constants */
enum {
  icmd_len = 8,       /* length of interal commands array */
  max_buffer = 1024,  /* max line buffer */
  max_args = 64       /* max number of args */
};
/* internal commands enum */
enum icmd             { cd_e, clr_e, dir_e, environ_e, echo_e, help_e, pause_e, quit_e  };
const char *icmd[] =  { "cd", "clr", "dir", "environ", "echo", "help", "pause", "quit" };

volatile __sig_atomic_t running = 1;

void handle_signal(int sig)
{
  (void) sig;
  running = 0;
}

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

void print_environ()
{
  int i;
  for(i = 0; environ[i] != NULL; i++) {
    printf("%s\n", environ[i]);
  }
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
  printf("Bye!\n");
  running = 0;
}

void external_cmd()
{

}

void change_directory(char **dir_name)
{
  char *cwd = getcwd(NULL, 0);
  /* check if empty, if it is report the current directory */
  /* check if dir_name exists, if not print error */
  /* change PWD env variable */
  if(*dir_name == NULL) { /* no arguments */
    printf("%s\n", cwd);
    return;
  }
  const char *path = *dir_name;
  struct stat st;

  if(stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
      printf("Directory exists\n");
  } else {
      printf("Directory does not exist or is inaccessible\n");
  }
}

void run_cmd(char **arguments)
{
  char *command = *arguments++;
  /* get internal command enum code */
  enum icmd eicmd = get_icmd(command);

  switch(eicmd) {
    case cd_e:
      change_directory(arguments);
      break;
    case clr_e:
      system("clear");
      break;
    case dir_e:
      system("ls -la");
      break;
    case environ_e:
      print_environ();
      break;
    case echo_e:
      break;
    case help_e:
      break;
    case pause_e:
      break;
    case quit_e:
      quit_app();
      break;
    default:
      external_cmd();
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

  if(signal(SIGINT, handle_signal) == SIG_ERR) {
    fprintf(stderr, "Cannot install signal handler\n");
    exit(EXIT_FAILURE);
  }
  /* read from stdin or a file */
  while(running) {
    prompt(is_file);

    clear_buf(buf, buf_len, max_buffer, sizeof(char));
    clear_buf(args, args_len, max_args, sizeof(char *));

    if(fgets(buf, max_buffer, input) != NULL) {
      /* read a line word by word into args */
      buf_len = strlen(buf);
      args_len = split(args, buf);
    } else {
      /* fgets returns NULL due to EOF or error */
      if(feof(input)) {
        quit_app();
        continue;
      }

      if(ferror(input)) { /* Error */
        perror("myshell");
        break;
      }
    }
#if 0
    print_tokens(args, args_len);
#endif
    run_cmd(args);
  }

  return 0;
}
