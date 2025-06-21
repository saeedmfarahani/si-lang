#ifndef H_ALOC
#define H_ALOC

#include "list.h"

extern list trash;

void *new(unsigned long size);
void del(list *l, node *n, bool should_free_addr);
void delete_all();

#endif
