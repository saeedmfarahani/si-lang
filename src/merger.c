#include "merger.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "aloc.h"
#include "file.h"
#include "lexer.h"
#include "list.h"
#include "token.h"

#define b 1 <<

/* mereger order *
 * [tuple]
 * [call]
 * data
 * arithmic
 * assignment
 */

static role si_lang[] = {
    {tt_unknown, tt_unknown, tt_unknown, tt_unknown, NULL},
};


void mrg_apply(list* tree, role r, node* n) {
  if (n == NULL || tree == NULL) exit(EXIT_FAILURE);

  t_token join = *(t_token*)n->address;
  node* prev = n->prev;
  pair* p = new (sizeof(pair));

  if (r.join != join) return;
  if (r.left) {
    if (n->prev == NULL) return;
    if (r.left != *(t_token*)n->prev->address) return;
    prev = n->prev->prev;
    p->left = (token_pair)n->prev->address;
  }
  if (r.right) {
    if (n->next == NULL) return;
    if (r.right != *(t_token*)n->next->address) return;
    p->right = (token_pair)n->next->address;
  }
  if (r.join_value != NULL) {
    if (join >= tp_invalid) exit(EXIT_FAILURE);
    token* t = n->address;
    if (strcmp(t->value, r.join_value) != 0) return;
  }

  p->join = (token_pair)n->address;
  p->type = r.type;

  if (r.left) delete (n->prev, false);
  if (r.right) delete (n->next, false);
  delete (n, false);

  list_insert(tree, p, prev);
  prev = NULL;
  p = NULL;
}

void merger(char* filename) {
  list tree = {0};

  file f = open(filename);
  token* t = lexer(&f);

  while (t->type != tt_eof) {
    list_add(&tree, &t);
    t = lexer(&f);
  }

  for (size_t i = 0; i < sizeof(si_lang) / sizeof(role); i++) {
    node* leaf = tree.head;
    while (leaf != NULL) {
      mrg_apply(&tree, si_lang[i], leaf);
      leaf = leaf->next;
    }
  }
}
