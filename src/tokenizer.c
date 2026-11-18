#include "util.h"
#include <stdio.h>
#include <stdlib.h>
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
  "\0"
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
  int ct, i;
  char *current_token = xmalloc(max_data, sizeof(char));

  for(ct = 0, i = 0; input_string[i] && input_string[i] != '\n'; ct++, i++) {
    while(ct == 0 && (input_string[i] == ' ' || input_string[i] == '\t')) {
      i++;
    }
    current_token[ct] = input_string[i];
    if(input_string[i] == ' ' || input_string[i] == '\t') {
      current_token[ct] = '\0';
      ct = -1;
      printf("%s\n", current_token);
    }
  }
  current_token[ct] = '\0';
  printf("%s\n", current_token);

  free(current_token);

  return NULL;
}

void parse(void)
{

}

void execute(void)
{

}

int main(void)
{
  tokenize("   echo    xhello");
  return 0;
}
