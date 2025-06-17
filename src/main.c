#include <argp.h>
#include <stdlib.h>

#include "aloc.h"

const char *argp_program_version = "Alpha 0.0.0";
const char *argp_program_bug_address =
    "https://github.com/SaeedMFarahani/si-lang/issus";
const char doc[] = "small languge powered by c inspired by go";
const char args_doc[] = "program.si";

const struct argp_option options[] = {{0}};

static error_t opt_parser(int key, char *argp, struct argp_state *state) {
  static char *program = NULL;
  switch (key) {
    case ARGP_KEY_ARG:
      if (program) argp_usage(state);
      program = argp;
      break;
    case ARGP_KEY_END:
      if (!program) argp_usage(state);
      break;
    default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

const struct argp argp = {options, opt_parser, args_doc, doc, 0, 0, 0};

int main(int argc, char **argv) {
  atexit(daloc_all);
  return argp_parse(&argp, argc, argv, 0, 0, 0);
}
