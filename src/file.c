#include "file.h"

#include <stdio.h>

void push(file *f) {
  if (f->value == EOF) return;
  f->pos_lst = f->pos;
  f->value = fgetc(f->fp);
  f->pos.col++;
  f->pos.index++;
  if (f->value == '\n') {
    f->pos.row++;
    f->pos.col = 0;
  }
}

file open(const char *filename) {
  file f;
  f.fp = fopen(filename, "r");
  f.pos = (pos){1, 1, 0};
  f.value = fgetc(f.fp);
  f.filename = filename;
  return f;
}
