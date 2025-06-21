#ifndef H_LOG
#define H_LOG

#include "file.h"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BLACK "\033[0;30m"
#define END "\033[0m"

void err(const char* msg) __THROW __attribute__((__noreturn__));
void err_pos(const char* msg, const char* filename, pos p) __THROW __attribute__((__noreturn__));

#endif
