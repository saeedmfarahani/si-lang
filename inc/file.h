#ifndef H_FILE
#define H_FILE

#include <stdio.h>

#define nil_pos (pos){1, 1, 0}
typedef struct s_pos {
  int col;
  int row;
  int index;
} pos;

typedef struct s_file {
  FILE *fp;
  const char *filename;
  char value;
  pos pos;
  pos pos_lst;
} file;

file open(const char *filename);
void push(file *f);
void pop(file *f);
#endif
