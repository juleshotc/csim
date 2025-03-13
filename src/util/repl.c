#include "repl.h"
#include <ctype.h>
#include "error.h"
#include "log.h"

#define TOKENMAX 256
static char buf[TOKENMAX];
static int err;

#define TOKEN_READ 0
#define END_FILE   1
#define LONG_TOKEN 2

static char *errmsg[] =
  {
    "Token read successfully",
    "End of file reached",
    "Token too long",
  };

static int
token (int (*read) (void), int (*divider) (int))
{
  static int c = 0;

  /* Read first non-whitespace character */
  if (!c)
    c = read ();

  while (isspace (c))
    c = read ();

  /* Ensure c isn't EOF */
  if (c == -1)
    return err = END_FILE;
  
  /* Parse the 'rule' of c, which divides it
     from other chars */
  const int rule = divider (c);
  
  int length = 0;
  do
    {
      buf[length++] = c;
      if (length + 1 >= TOKENMAX)
        return err = LONG_TOKEN;
      c = read ();
    }
  while (rule == divider (c));
  
  buf[length] = '\0';
  return 0;
}

int
repl (int (*read) (void),
      int (*divider) (int),
      int (*eval) (const char *),
      void (*print) (const char *, ...))
{
  print ("[repl] Reading new file\n");
  while (!token (read, divider))
      eval (buf);
  if (err != END_FILE)
    panic ("[repl] %s: %s\n", errmsg[err], buf);
    
  return 0;
}
