#include "util.h"

SYMBOL
fnif (unsigned int argc, SYMBOL *syms)
{
  if (argc != 2 && argc != 3)
    return rawerror ("if: wrong number of arguments");
  
  if (syms[0].type != BOOLEAN)
    return rawerror ("if: non-boolean first argument");
  if (syms[0].boolean)
    return syms[1];
  if (argc == 3)
    return syms[2];
  return nullsym;
}
