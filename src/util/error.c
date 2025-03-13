#include "error.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void
panic (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  vfprintf (stderr, fmt, args);
  va_end (args);
  exit (1);
}

void
epanic (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  vfprintf (stderr, fmt, args);
  va_end (args);
  
  perror ("");
  exit (1);
}
