#include "util.h"

SYMBOL
fnerror (unsigned int argc, SYMBOL *syms)
{
  if (argc == 0 || syms[0].type != STRING)
    return rawerror ("Error raised");

  return rawerror (syms[1].string);
}

SYMBOL
fnwrite (unsigned int argc, SYMBOL *syms)
{
  if (argc == 0)
    return rawerror ("write: no arguments");
  for (unsigned int i = 0; i < argc; ++i)
    {
      if (syms[i].type == BOOLEAN)
        rawprint ("%s", syms[i].boolean ? "t" : "nil");
      else if (syms[i].type == INTEGER)
        rawprint ("%lld", syms[i].integer);
      else if (syms[i].type == FLOATING)
        rawprint ("%Lf", syms[i].floating);
      else if (syms[i].type == STRING)
        rawprint ("%s", syms[i].string);
      else if (syms[i].type == FUNCTION)
        {
          rawprint ("(%s)", syms[i].function.name);
        }
    }
  rawprint ("\n");
  return nullsym;
}
