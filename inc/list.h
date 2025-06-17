#ifndef H_LIST
#define H_LIST

typedef struct s_node {
  void* address;
  struct s_node* next;
  struct s_node* prev;
} node;

typedef struct s_list {
  struct s_node* head;
  struct s_node* tail;
} list;

void add_to_list(list* l, void* a);

#endif
