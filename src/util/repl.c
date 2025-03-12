#include "repl.h"
#include <ctype.h>
#include "error.h"

#define TOKENMAX 32
static char buf[TOKENMAX];
static int err = 0;

#define END_FILE 0
#define LONG_TOKEN 1

static char *errmsg[] =
  {
    "End of file reached",
    "Token too long",
  };

static int
token (int (*read) (void))
{
  int c;
  
  /* Read first non-whitespace character */
  while (isspace (c = read ())) { }

  /* Read until first whitespace character */
  int i = 0;
  do
    {
      if (c == -1)
        {
          err = END_FILE;
          return 1;
        }
      buf[i++] = c;
      /* (i + 1): 32nd char is always null */
      if (i + 1 >= TOKENMAX)
        {
          /* No need to add ending null because
             of (i + 1) check instead of i check */
          err = LONG_TOKEN;
          return 1;
        }
    } while (!isspace (c = read ()));
  buf[i] = '\0';
  return 0;
}

int
repl (int (*read) (void),
      int (*eval) (const char *),
      void (*print) (const char *, ...))
{
  print ("[repl] Reading new file\n");
  while (!token (read))
      eval (buf);
  if (err != END_FILE)
    panic ("[repl] %s: %s\n", errmsg[err], buf);
  print ("[repl] Read file successfully.\n\n");
    
  return 0;
}
