
#include "log.h"

#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void err(const char* msg) {
  printf("%sError: %s%s\n", RED, END, msg);
  exit(EXIT_FAILURE);
}

void err_pos(const char* msg, const char* filename, pos p) {
  printf("%sError%s: %s [%s%s%s:%s%d%s:%s%d%s]\n", RED, END, msg, YELLOW,
         filename, END, MAGENTA, p.row, END, MAGENTA, p.col, END);
  exit(EXIT_FAILURE);
}
