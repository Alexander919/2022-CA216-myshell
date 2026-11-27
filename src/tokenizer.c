#include "util.h"
#include "darray.h"
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
  redirect_input_e    = 1, /* < */
  redirect_output_e   = 2, /* > */
  redirect_append_e   = 3, /* >> */
  pipe_e              = 4, /* | */
  logical_and_e       = 5, /* && */
  logical_or_e        = 6, /* || */
  background_e        = 7, /* & */
  separator_e         = 8, /* ; */
  end_e
};

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
  char *name;
  enum token_type type;
  int position;
  int length;
};

typedef struct token Token ;

/* darray_print callback */
void token_printer(void *elem)
{
  Token *token = elem;
  printf("[%s]\n", token->name);
}

static enum token_type match_operator(const char *input)
{
  size_t k;
  for(k = 0; k < sizeof(operators) / sizeof(operators[0]); k++) {
    if(strncmp(input, operators[k].oper, operators[k].length) == 0) {
      return operators[k].type; /* operator found */
    }
  }
  return word_e; /* no match */
}

Darray *tokenize(const char *input_string)
{
  int i;
  int ct_len = 0;
  int start = 0;

  Darray *tokens = darray_create();

  for(i = 0; ; i++) {
    char ch = input_string[i];
    int end = is_end(ch);

    if(end || is_whitespace(ch)) {
      if(ct_len != 0) {
        enum token_type type;
        char *current_token_value = xmalloc(max_data, sizeof(char));
        Token *token = xmalloc(1, sizeof(struct token));

        strncpy2(current_token_value, input_string + start, ct_len);

        type = match_operator(current_token_value);

        token->name = current_token_value;
        token->type = type;
        token->length = ct_len;
        token->position = i;

        darray_push(tokens, token);

        ct_len = 0;
      }
      if(end) break;
    }
    else {
      if(ct_len == 0) start = i;
      ct_len++;
    }
  }

  return tokens;
}

void parse(void)
{

}

void execute(void)
{

}
/* callback for darray_destroy */
void token_cleaner(void *data)
{
  Token *token = data;
  free(token->name);
  free(token);
}

int main(void)
{
  Darray *arr1 = tokenize("   echo    xhello   ");
  Darray *arr2 = tokenize("echo || hello > test.txt &");

  darray_print(arr1, token_printer);
  darray_print(arr2, token_printer);

  darray_destroy(arr1, token_cleaner);
  darray_destroy(arr2, token_cleaner);

  return 0;
}
