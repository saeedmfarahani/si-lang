#include "token.h"

void tkn_reset(token* t) {
  t->head = (pos){1, 1, 0};
  t->tail = t->head;
  t->length = 0;
  t->type = tt_unknown;
}
