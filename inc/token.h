#ifndef H_TOKEN
#define H_TOKEN

#include "file.h"

typedef enum {
  /* raw token */
  tt_unk,
  tt_eof,
  tt_break,
  tt_word,
  tt_int,
  tt_bin,
  tt_hex,
  tt_float,
  /* pair token */
  tp_inv,
} t_token;

typedef struct s_token {
  t_token type;
  char* value;
  unsigned int length;
  pos head;
  pos tail;
} token;

void tkn_reset(token* t);

#endif
