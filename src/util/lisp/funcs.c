#include "funcs.h"

#include <stdio.h>

static OBJECT fnwriteline (OBJECT *);

const OBJECT funs[] = {
  {
    .type = FUNCTION,
    .function.name = "write-line",
    .function.argc = 1,
    .function.ptr = fnwriteline,
  },
};
const unsigned int funcount = sizeof (funs);

static OBJECT
fnwriteline (OBJECT *objs)
{
  if (objs[0].type == INTEGER)
    printf ("[echo] %lld\n", objs[0].integer);
  else if (objs[0].type == STRING)
    printf ("[echo] %s\n", objs[0].string);
  else if (objs[0].type == FUNCTION)
    {
      printf ("[echo (%s", objs[0].function.name);
      char argletter = 'a';
      for (int i = 0; i < objs[0].function.argc; ++i)
        printf (" %c", argletter++);
      printf (")\n");
    }
  return (OBJECT) { .type = NONE }; 
}
