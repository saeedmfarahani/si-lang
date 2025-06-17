#include "merger.h"

#include <stddef.h>
#include <stdint.h>

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

static role grammer[] = {
    {0, tt_unknown, 0, 0},
};

list tree = {0};

void merger(char* filename) {
  file f = open(filename);
  token* t = lexer(&f);
  while (t->type != tt_eof) {
    node* n = (node*)aloc(sizeof(node));
    n->address = t;
    add_to_list(&tree, &n);
  }

  for (size_t i = 0; i < sizeof(grammer) / sizeof(role); i++) {
    node* leaf = tree.head;
    while (leaf->next != NULL) {
      t_token t = *(t_token*)leaf->address;
      if (t != grammer[i].join) continue;
      if ()
      leaf = leaf->next;
    }
  }
}
