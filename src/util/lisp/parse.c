#include "parse.h"

#include "defs.h"
#include "funcs.h"
#include "../error.h"
#include "../log.h"
#include "../../lib/strtonum.h" /* isinteger */
#include <limits.h> /* isinteger */
#include <string.h> /* stringcmp */

#define VARSIZE 128
static OBJECT varlow[VARSIZE];
static OBJECT *varhigh = &varlow[VARSIZE];
static OBJECT *varptr = varlow;
#define FUNSIZE 32
#if 0
static OBJECT funlow[FUNSIZE];
static OBJECT *funhigh = &funlow[FUNSIZE];
static OBJECT *funptr = funlow;
#endif

#if 0
static void newfun (OBJECT *function);
#endif
static void newvar (OBJECT variable);
#if 0
static void runfunc (void);
#endif
static int isinteger (const char *, OBJECT *);
static int isfunction (const char *, OBJECT *);

int
parse (const char *token)
{
  OBJECT object;
  if (isinteger (token, &object))
    printl ("[parse] Read integer %lld from token %s\n",
            object.integer, token);
  else if (isfunction (token, &object))
    printl ("[parse] Read function %s from token %s\n",
            object.function.name, token);
  else
    panic ("[parse] Can't handle token: %s\n", token);
  newvar (object);
  return 0;
}

static int
isinteger (const char *str, OBJECT *object)
{
  const char *err = 0;
  long long num = strtonum (str, LLONG_MIN, LLONG_MAX, &err);
  if (err)
    return 0;
  object->type = INTEGER;
  object->integer = num;
  return 1;
}

static int
isfunction (const char *str, OBJECT *object)
{
  for (unsigned int i = 0; i < funcount; ++i)
    {
      OBJECT funcmp = funs[i];
      if (!strcmp (str, funcmp.function.name))
        {
          object->type = FUNCTION;
          object->function.name = funcmp.function.name;
          object->function.argc = funcmp.function.argc;
          object->function.ptr = funcmp.function.ptr;
            return 1;
        }
    }
  return 0;
}

#if 0

static void
newfun (OBJECT *function)
{
  if (funptr >= funhigh)
    panic ("[newfun] stack overflow\n");
  if (function->type != FUNCTION)
    panic ("[newfun] not a variable");
  *funptr = *function;
  ++funptr;
}

#endif

static void
newvar (OBJECT variable)
{
  /* printl ("varlow: %x\nvarptr: %x\nvarhigh: %x\n", varlow, varptr, varhigh); */
  printl ("Size: %d\tThing: %d\n", sizeof (OBJECT), (int) ((varptr - varlow) / sizeof (OBJECT)));
  if (varptr >= varhigh)
    panic ("[newvar] stack overflow\n");
  if (variable.type >= _LAST)
    panic ("[newvar] bogus type: %d\n", variable.type);
  *varptr = variable;
  ++varptr;
}

#if 0

static void
runfunc (void)
{
  --funptr;
  varptr -= funptr->argc;
  funptr->ptr (varptr);
}

#endif
