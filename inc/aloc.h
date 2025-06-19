#ifndef H_ALOC
#define H_ALOC

#include "list.h"

void *new(unsigned long size);
void delete(node *n,bool should_free_addr);
void delete_all();

static list trash = {0};

#endif
