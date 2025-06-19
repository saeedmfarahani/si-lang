#include "aloc.h"

#include <stdlib.h>

#include "list.h"

void *new(unsigned long size) {
  void *p = calloc(0, size);
  if (p == NULL) abort();

  node *n = calloc(1, sizeof(node));
  if (n == NULL) abort();

  n->next = NULL;
  if (trash.head == NULL) {
    trash.head = n;
    trash.tail = n;
  }
  n->prev = trash.tail;
  trash.tail->next = n;
  trash.tail->address = p;
  trash.tail = n;

  return p;
}

void delete(node *n, bool should_free_addr) {
  node *t = n->trash;
  t->prev->next = t->next;
  t->next->prev = t->prev;
  if (should_free_addr) free(t->address);
  free(t);
  t = NULL;
}

void delete_all() {
  while (trash.head->next != NULL) {
    node *temp = trash.head;
    free(temp->address);
    trash.head = temp->next;
    free(temp);
  }
}
