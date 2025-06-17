
#include "list.h"

#include <stdlib.h>

void add_to_list(list *l, void *a) {
  node *n = (node *)calloc(1, sizeof(node));

  if (n == NULL) abort();

  n->next = NULL;
  if (l->head == NULL) {
    l->head = n;
    l->tail = n;
  }
  n->prev = l->tail;
  l->tail->next = n;
  l->tail->address = a;
  l->tail = n;
}
