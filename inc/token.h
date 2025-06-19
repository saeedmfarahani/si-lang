#ifndef H_TOKEN
#define H_TOKEN

#include "file.h"

typedef enum {
  /* raw token */
  tt_unknown,
  tt_eof,
  tt_break,
  tt_word,
  /* pair token */
  tp_invalid,
} t_token;

typedef struct s_token {
  t_token type;
  char* value;
  int length;
  pos head;
  pos tail;
} token;

void tkn_reset(token* t);

#endif
