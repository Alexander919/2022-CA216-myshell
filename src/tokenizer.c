#include <stdio.h>
#include "util.h"
/* $ ~ are handled later, at parser stage as word expansion */
/* need to recognize \ "" and '' */
/*
 Character	Name	                Purpose
 \	        Backslash	            Escapes the next character (with some exceptions)
 "	        Double quote	        Groups text into a word while allowing certain expansions
 '	        Single quote	        Treats enclosed characters literally

 hello'$USER'"$HOME"world - is a single word
 */
enum token_type {
  word_e,
  redirect_input_e,     /* < */
  redirect_output_e,    /* > */
  redirect_append_e,    /* >> */
  pipe_e,               /* | */
  logical_and_e,        /* && */
  logical_or_e,         /* || */
  background_e,         /* & */
  separator_e,          /* ; */
  end_e
};

const char *token_operator[] = {
  NULL,
  "<",
  ">",
  ">>",
  "|",
  "&&",
  "||",
  "&",
  ";",
  NULL
};

enum lexer_state {
  normal_e,
  single_quoted_e,
  double_quoted_e
};

struct token {
  char *value;
  enum token_type type;
  int position;
  int length;
};

struct token *tokenize(const char *input_string)
{
  int *test = xmalloc(10 * sizeof(int));
  *test = 5;
  printf("%s %d\n", input_string, *test);
  return NULL;
}

void parse()
{

}

void execute()
{

}

int main(void)
{
  printf("Hello, World!\n");
  tokenize("echo \"hello world\"");
  return 0;
}
