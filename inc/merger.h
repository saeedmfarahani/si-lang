#ifndef H_MERGER
#define H_MERGER

#include "token.h"
typedef struct s_role {
  t_token left;
  t_token join;
  t_token right;
  t_token type;
  const char* join_value;
} role;

typedef struct s_pair {
  t_token type;
  void* left;
  void* join;
  void* right;
} pair;

#endif
