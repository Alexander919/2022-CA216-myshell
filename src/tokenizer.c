#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* $ ~ are handled later, at parser stage as word expansion */
/* need to recognize \ "" and '' */
/*
 Character	Name	                Purpose
 \	        Backslash	            Escapes the next character (with some exceptions)
 "	        Double quote	        Groups text into a word while allowing certain expansions
 '	        Single quote	        Treats enclosed characters literally

 hello'$USER'"$HOME"world - is a single word
 */
/* token type enum, starts with 0 */
enum token_type {
  word_e              = 0,
  redirect_input_e,        /* < */
  redirect_output_e,       /* > */
  redirect_append_e,       /* >> */
  pipe_e,                  /* | */
  logical_and_e,           /* && */
  logical_or_e,            /* || */
  background_e,            /* & */
  separator_e,             /* ; */
  end_e
};

#if 0
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
#endif

/* struct to match operators */
static const struct
{
  const char *oper;       /* operator */
  const int length;       /* operator length */
  enum token_type type;   /* token type of the corresponding operator */
}
operators[] = {
  { ">>", 2, redirect_append_e  },
  { "&&", 2, logical_and_e      },
  { "||", 2, logical_or_e       },
  { "<" , 1, redirect_input_e   },
  { ">" , 1, redirect_output_e  },
  { "|" , 1, pipe_e             },
  { "&" , 1, background_e       },
  { ";" , 1, separator_e        }
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

static enum token_type match_operator(const char *input)
{
  int k, cmp;
  k = 0;
  cmp = strncmp(input, operators[k].oper, operators[k].length);
  if(cmp == 0) {
    printf("%s - %d\n", operators[k].oper, operators[k].type);
    return operators[k].type;
  }
  return word_e; /* no match */
}

struct token *tokenize(const char *input_string)
{
  int i;
  int ct_len = 0;
  int start = 0;

  char *current_token = xmalloc(max_data, sizeof(char));

  for(i = 0; ; i++) {
    char ch = input_string[i];
    int end = is_end(ch);

    if(end || is_whitespace(ch)) {
      if(ct_len != 0) {
        memcpy(current_token, input_string + start, ct_len);
        current_token[i] = '\0';
        ct_len = 0;
        printf("[%s]\n", current_token);
      }
      if(end) break;
    }
    else {
      enum token_type type = match_operator(input_string);
      if(type) { /* word_e = 0, so type must be > 0 */
        /* operator is found, act accordingly */
      }
      if(ct_len == 0) start = i;
      ct_len++;
    }
  }

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
  tokenize("   echo    xhello   ");
  return 0;
}
