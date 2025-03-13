#include "util.h"
#include <stdio.h>
#include <stdarg.h>

SYMBOL nullsym = { .type = NONE };

SYMBOL
rawerror (char *fmt, ...)
{
  printf ("[ERROR] ");
  va_list args;
  va_start (args, fmt);
  vprintf (fmt, args);
  va_end (args);
  printf ("\n");
  return nullsym;
}

void
rawprint (char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  vprintf (fmt, args);
  va_end (args);
}
