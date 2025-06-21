#include "merger.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aloc.h"
#include "file.h"
#include "lexer.h"
#include "list.h"
#include "token.h"

#define b(number) 1 << number
/* mereger order *
 * [tuple]
 * [call]
 * data
 * arithmic
 * assignment
 */

static role si_lang[] = {
    {tt_hex, tt_bin, tt_int, tp_inv, NULL},
};

node* mrg_apply(list* tree, role r, node* n) {
  if (n == NULL || tree == NULL) abort();

  t_token join = *(t_token*)n->address;
  pair* p = new (sizeof(pair));

  if (r.join != join) goto failed;
  if (r.join_value) {
    if (join >= tp_inv) exit(EXIT_FAILURE);
    token* t = n->address;
    if (strcmp(t->value, r.join_value) != 0) goto failed;
  }
  if (r.left) {
    if (n->prev == NULL) goto failed;
    bool match = *(t_token*)n->prev->address == r.left;
    if (!match) goto failed;
    p->left = *(token_pair*)n->prev->address;
  }
  if (r.right) {
    if (n->next == NULL) goto failed;
    bool match = *(t_token*)n->next->address == r.right;
    if (!match) goto failed;
    p->right = *(token_pair*)n->next->address;
  }

  p->join = *(token_pair*)n->address;
  p->type = r.type;

  if (r.left) del(tree, n->prev, false);
  if (r.right) del(tree, n->next, false);
  p = NULL;

  return n->next;

failed:
  free(p);
  return n->next;
}

void merger(const char* filename) {
  list l = {0};

  file f = open(filename);
  token* t = lexer(&f);

  while (t->type != tt_eof) {
    list_add(&l, t);
    t = lexer(&f);
  }

  for (size_t i = 0; i < sizeof(si_lang) / sizeof(role); i++) {
    node* n = l.head;
    while (n) {
      n = mrg_apply(&l, si_lang[i], n);
    }
  }
}
