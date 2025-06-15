#ifndef H_TOKEN
#define H_TOKEN

#include "file.h"

typedef enum {
  tt_unknown,
  tt_eof,
  tt_break,
  tt_word,
} token_type;

typedef struct s_token {
  token_type type;
  char value[256];
  int length;
  pos head;
  pos tail;
} token;

void tkn_reset(token *t);

#endif
