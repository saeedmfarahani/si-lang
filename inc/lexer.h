#ifndef H_LEXER
#define H_LEXER

#include "file.h"
#include "token.h"

token* lexer(file* f);
bool lxr_is_end(token* t, file* f);
bool lxr_is_gap(token* t, file* f);
bool lxr_is_word(token* t, file* f);
bool lxr_is_num(token* t, file* f);

#endif
