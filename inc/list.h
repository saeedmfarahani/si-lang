#ifndef H_LIST
#define H_LIST

typedef struct s_node {
  void* address;
  struct s_node* next;
  struct s_node* prev;
  struct s_node* trash;
} node;

typedef struct s_list {
  struct s_node* head;
  struct s_node* tail;
} list;

node* list_add(list* l, void* a);
node* list_insert(list* l, void* a, node* p);
void list_del(list* l, node* n);
#endif
