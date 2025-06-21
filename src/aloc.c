#include "aloc.h"

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list trash = {0};

void *new(unsigned long size) {
  void *p = calloc(1, size);
  if (p == NULL) abort();

  node *n = calloc(1, sizeof(node));
  if (n == NULL) abort();

  if (trash.tail != NULL) {
    n->prev = trash.tail;
    trash.tail->next = n;
  }

  trash.tail = n;
  n->address = p;

  if (trash.head == NULL) {
    trash.head = n;
    n->prev = NULL;
  }
  return p;
}

void del(list *l, node *n, bool should_free_addr) {
  node *t = n->trash;
  list_del(&trash, t);
  list_del(l, n);
  if (should_free_addr) free(n->address);
  free(n);
  free(t);
  t = NULL;
}

void delete_all() {
  printf("clean up memory ...\n");
  while (trash.head != NULL) {
    node *t = trash.head;
    trash.head = t->next;
    if (t->address != NULL) free(t->address);
    free(t);
  }
}
