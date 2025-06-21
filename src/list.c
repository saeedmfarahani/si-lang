
#include "list.h"

#include <stdlib.h>
#include <string.h>

#include "aloc.h"

node *list_add(list *l, void *a) {
  node *n = (node *)new (sizeof(node));
  n->trash = trash.tail;

  if (l->tail != NULL) {
    n->prev = l->tail;
    l->tail->next = n;
  }
  l->tail = n;
  n->address = a;

  if (l->head == NULL) {
    l->head = n;
    n->prev = NULL;
  }
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

void list_del(list *l, node *n) {
  if (l->head == n) l->head = n->next;
  if (l->tail == n) l->tail = n->prev;
  if (n->prev) n->prev->next = n->next;
  if (n->next) n->next->prev = n->prev;
}
