#include "parse.h"

#include "defs.h"
#include "funhead.h"
#include "../error.h"
#include "../log.h"
#include "../unescape.h"
#include "../reserve.h" /* reserve text */
#include "../../lib/strtonum.h" /* isinteger */

#include <limits.h> /* isinteger */
#include <string.h> /* stringcmp, strlen */
#include <stdio.h> /* snprintf */
#include <stdlib.h> /* strold */
#include <errno.h>

#define SYMSIZE 256
#define MARKSIZE 32

/* Two stacks: symbol stack and mark stack */
static SYMBOL symlow[SYMSIZE];
static SYMBOL *symhigh = &symlow[SYMSIZE];
static SYMBOL *symptr = symlow;

static SYMBOL *marklow[MARKSIZE];
static SYMBOL **markhigh = &marklow[MARKSIZE];
static SYMBOL **markptr = marklow;

/*
  symptr
    \
     \__
        SYMBOL
        SYMBOL
        SYMBOL
       FUNCTION              markptr
        SYMBOL \               /
        SYMBOL  \          ___/
       FUNCTION  \_____MARK
        SYMBOL \_______MARK
       FUNCTION________MARK

  When you encounter '(', mark the current symptr.
    To mark the current symptr, set (*markptr) to
    symptr, and increment markptr.
  When you encounter ')', run the last function.
    To run the last function, decrement markptr, set
    symptr to (*markptr), then run (*symptr)'s function,
    feeding it the pointer (symptr + 1) as an array.
 */

static SYMBOL *newsym (void);
static void mark (void);
static void runfunc (void);
static int isboolean (const char *, SYMBOL *);
static int isstring (const char *, SYMBOL *);
static int isinteger (const char *, SYMBOL *);
static int isfloating (const char *, SYMBOL *);
static int isfunction (const char *, SYMBOL *);
static int isbrackets (const char *token);

int
parse (const char *token)
{
  if (isbrackets (token))
    return 0;
  
  SYMBOL *symbol = newsym ();
  if (isboolean (token, symbol))
    printl ("[parse] Read boolean %d from token %s\n",
            symbol->boolean, token);
  else if (isstring (token, symbol))
    printl ("[parse] Read string %s from token %s\n",
            symbol->string, token);
  else if (isfunction (token, symbol))
    printl ("[parse] Read function %s from token %s\n",
            symbol->function.name, token);
  else if (isinteger (token, symbol))
    printl ("[parse] Read integer %lld from token %s\n",
            symbol->integer, token);
  else if (isfloating (token, symbol))
    printl ("[parse] Read float %Lf from token %s\n",
            symbol->floating, token);
  else
    panic ("[parse] Can't handle token: %s\n", token);
  return 0;
}

static int
isbrackets (const char *token)
{
  while (*token)
    {
      if (*token == '(')
        mark ();
      else if (*token == ')')
        runfunc ();
      else
        return 0;
      ++token;
    }
  return 1;
}

static int
isboolean (const char *str, SYMBOL *symbol)
{
  int boolval;
  if (!strcmp (str, "t"))
    boolval = 1;
  else if (!strcmp (str, "nil"))
    boolval = 0;
  else
    return 0;

  symbol->type = BOOLEAN;
  symbol->boolean = boolval;
  return 1;
}

static int
isstring (const char *str, SYMBOL *symbol)
{
  char *newstr = unescape (str, reserve);
  if (!newstr)
    return 0;
  
  symbol->type = STRING;
  symbol->string = newstr;
  return 1;
}

static int
isinteger (const char *str, SYMBOL *symbol)
{
  const char *err = 0;
  long long num = strtonum (str, LLONG_MIN, LLONG_MAX, &err);
  if (err)
    return 0;
  symbol->type = INTEGER;
  symbol->integer = num;
  return 1;
}

static int
isfloating (const char *str, SYMBOL *symbol)
{
  errno = 0;
  long double num = strtold (str, 0);
  if (errno)
    return 0;

  symbol->type = FLOATING;
  symbol->floating = num;
  return 1;
}

static int
isfunction (const char *str, SYMBOL *symbol)
{
  for (unsigned int i = 0; i < funcount; ++i)
    {
      SYMBOL *funcmp = funs + i;
      if (!strcmp (str, funcmp->function.name))
        {
          symbol->type = FUNCTION;
          symbol->function.name = funcmp->function.name;
          symbol->function.ptr = funcmp->function.ptr;
            return 1;
        }
    }
  return 0;
}

static SYMBOL *
newsym (void)
{
  if (symptr >= symhigh)
    panic ("[newsym] stack overflow");
  return symptr++;
}

static void
mark (void)
{
  *markptr = symptr;
  ++markptr;
  if (markptr >= markhigh)
    panic ("[mark] stack overflow");
}

static void
runfunc (void)
{
  if (markptr <= marklow)
    panic ("[runfunc] stack underflow");
  --markptr;
  int argc = symptr - (*markptr) - 1;
  /* symptr - (*markptr) includes function and args

              symptr
               /
         _____/
    ARG 3
    ARG 2    *markptr
    ARG 1      /
  FUNCTION____/

   (symptr - (*markptr) - 1), then, gives you the
   number of arguments to the function. */
  
  symptr = (*markptr);
  if (symptr->type != FUNCTION)
    panic ("[runfunc] Tried to run id %d", symptr->type);
  SYMBOL retval = symptr->function.ptr (argc, symptr + 1);
  if (retval.type == NONE)
    return;

  (*newsym ()) = retval;
  /* (*symptr) points to function symbol
     (*(symptr + 1)) points to argument 1 */
}
