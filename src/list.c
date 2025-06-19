
#include "list.h"

#include <stdlib.h>

#include "aloc.h"

node *list_add(list *l, void *a) {
  node *n = (node *)new (sizeof(node));
  n->trash = trash.tail;
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
  return n;
}

node *list_insert(list *l, void *a, node *p) {
  if (p == l->tail) {
    return list_add(l, p);
  }
  node *n = (node *)new (sizeof(node));
  if (n == NULL) abort();
  n->trash = trash.tail;
  n->address = a;
  n->next = p->next;
  n->prev = p;
  p->next->prev = n;
  p->next = n;

  return n;
}
