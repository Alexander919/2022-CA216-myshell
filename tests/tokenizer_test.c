#include "../src/tokenizer.c"

int main(void)
{
  static const struct {
     const char *input;
     enum token_type expected;
   } cases[] = {
     { "<input.txt",      redirect_input_e  },
     { ">output.txt",     redirect_output_e },
     { ">>output.txt",    redirect_append_e },
     { "|wc",             pipe_e            },
     { "&&echo ok",       logical_and_e     },
     { "||echo fallback", logical_or_e      },
     { "&",               background_e      },
     { ";echo next",      separator_e       },

     /* Prefer a two-character match when both prefixes match. */
     { ">>>",             redirect_append_e },
     { "&&&",             logical_and_e     },
     { "|||",             logical_or_e      },
     { "<<",              redirect_input_e  },

     /* The function doesn't skip whitespace or scan ahead. */
     { "",                word_e            },
     { "hello",           word_e            },
     { " >",              word_e            },
     { "hello>out.txt",   word_e            }
   };
   size_t i;
   int failed = 0;

   for (i = 0; i < sizeof cases / sizeof cases[0]; i++) {
     enum token_type actual = match_operator(cases[i].input);

     if (actual != cases[i].expected) {
       fprintf(stderr, "match_operator(\"%s\"): expected %d, got %d\n",
               cases[i].input, (int)cases[i].expected, (int)actual);
       failed = 1;
     }
   }

   if (!failed)
     puts("All match_operator tests passed.");

  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
