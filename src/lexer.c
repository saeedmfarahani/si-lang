#include "lexer.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "aloc.h"
#include "const.h"
#include "file.h"
#include "log.h"
#include "token.h"

#define push_on(exp)  \
  do {                \
    t->tail = f->pos; \
    t->length++;      \
    push(f);          \
  } while (exp);

token* lexer(file* f) {
  token* t = new (sizeof(token));

  bool (*check[])(token*, file*) = {
      lxr_is_gap,
      lxr_is_end,
      lxr_is_word,
      lxr_is_num,
  };
  size_t c_len = sizeof(check) / sizeof(void*);
  for (size_t i = 0; i < c_len; i++) {
    tkn_reset(t);
    if (check[i](t, f)) return t;
  }

  err_pos(ERR_SINTAX_UNKNOWN, f->filename, f->pos);
}

bool lxr_is_end(token* t, file* f) {
  if (f->value != EOF) return false;
  t->head = f->pos;
  t->tail = f->pos;
  t->type = tt_eof;
  fclose(f->fp);
  return true;
}

bool lxr_is_frac(token* t, file* f) {
  if (f->value != '.') return false;
  unsigned int len = t->length + 1;
  push_on(isdigit(f->value));
  if (t->length == len) err_pos(ERR_INV_NUM_FLOAT_DOT, f->filename, f->pos);
  if (f->value == '.') err_pos(ERR_INV_NUM_FLOAT_DDOT, f->filename, f->pos);
  return true;
}

bool lxr_is_hex(token* t, file* f) {
  if (f->value != 'x') return false;
  push(f);
  if (!isxdigit(f->value)) err_pos(ERR_INV_NUM_HEX, f->filename, f->pos);
  t->type = tt_hex;
  push_on(isxdigit(f->value));
  return true;
}

bool lxr_is_bin(token* t, file* f) {
  if (f->value != 'b') return false;
  push(f);
  if (!(f->value == '0' || f->value == '1'))
    err_pos(ERR_INV_NUM_BIN, f->filename, f->pos);
  t->type = tt_bin;
  push_on(f->value == '0' || f->value == '1');
  return true;
}

bool lxr_is_num(token* t, file* f) {
  if (!isdigit(f->value)) return false;
  t->head = f->pos;
  t->type = tt_int;

  char base = f->value == '0';
  push_on(isdigit(f->value));
  base = base && t->length == 1;

  if (base && lxr_is_hex(t, f)) return true;
  if (base && lxr_is_bin(t, f)) return true;
  if (lxr_is_frac(t, f)) return true;
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
  push_on(isalnum(f->value) || f->value == '_');
  return true;
}

bool lxr_is_gap(token* t, file* f) {
  bool is_break = false;
  while (isspace(f->value)) {
    if (!is_break && f->value == '\n') {
      t->head = f->pos;
      t->type = tt_break;
      is_break = true;
    }
    t->tail = f->pos;
    push(f);
  }
  return is_break;
}
