#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include "error.h"

/* Lazy loaded log file */
FILE *stream;

static void notready (const char *fmt, ...);
static void ready (const char *fmt, ...);

void (*printl) (const char *, ...) = notready;

void
notready (const char *fmt, ...)
{
  stream = fopen ("log.txt", "w");
  if (!stream)
    epanic ("[printl] log file failed to open");
  printl = ready;
  
  fprintf (stream, "[printl] lazy-loaded log file\n");

  va_list args;
  va_start (args, fmt);
  vfprintf (stream, fmt, args);
  va_end (args);
  fflush (stdout);
}

void
ready (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  vfprintf (stream, fmt, args);
  va_end (args);
  fflush (stdout);
}
