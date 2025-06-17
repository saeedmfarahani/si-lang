#include <stdlib.h>

#include "list.h"

static list trash = {0};

void *aloc(unsigned long size) {
  void *p = calloc(0, size);
  if (p == NULL) abort();
  add_to_list(&trash, p);
  return p;
}

void daloc_all() {
  while (trash.head->next != NULL) {
    node *temp = trash.head;
    free(temp->address);
    trash.head = temp->next;
    free(temp);
  }
}
