#include "lexer.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "token.h"

token lexer(file* f) {
  token t;

  bool (*check[])(token*, file*) = {
      lxr_is_gap,
      lxr_is_word,
      lxr_is_end,
  };
  size_t c_len = sizeof(check) / sizeof(void*);
  for (size_t i = 0; i < c_len; i++) {
    tkn_reset(&t);
    if (check[i](&t, f)) return t;
  }

  exit(EXIT_FAILURE);
}

bool lxr_is_end(token* t, file* f) {
  if (f->value != EOF) return false;
  t->head = f->pos;
  t->tail = f->pos;
  return true;
}

bool lxr_is_word_start(file* f) {
  if (isalpha(f->value)) return true;
  if (f->value == '_') return true;
  return false;
}

bool lxr_is_word(token* t, file* f) {
  if (!lxr_is_word_start(f)) return false;
  t->head = f->pos;
  t->type = tt_word;
  do {
    t->value[t->length] = f->value;
    t->length++;
    push(f);
  } while (isalnum(f->value) || f->value == '_');
  t->tail = f->pos_lst;
  return true;
}

bool lxr_is_gap(token* t, file* f) {
  bool is_break = false;
  while (isspace(f->value)) {
    push(f);
    if (f->value != '\n') continue;
    if (!is_break) t->head = f->pos;
    t->tail = f->pos;
    t->type = tt_break;
    is_break = true;
  }
  return is_break;
}
