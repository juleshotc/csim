#include "defs.h"
#include <stdio.h>

extern SYMBOL fnerror (unsigned int, SYMBOL *);
extern SYMBOL fnwrite (unsigned int, SYMBOL *);
extern SYMBOL fnif (unsigned int, SYMBOL *);
extern SYMBOL fnsum (unsigned int, SYMBOL *);
extern SYMBOL fnsub (unsigned int argc, SYMBOL *syms);
extern SYMBOL fnmul (unsigned int, SYMBOL *);
extern SYMBOL fndiv (unsigned int argc, SYMBOL *syms);
extern SYMBOL fngre (unsigned int argc, SYMBOL *syms);
extern SYMBOL fngeq (unsigned int argc, SYMBOL *syms);
extern SYMBOL fnlss (unsigned int argc, SYMBOL *syms);
extern SYMBOL fnleq (unsigned int argc, SYMBOL *syms);
extern SYMBOL fnequ (unsigned int argc, SYMBOL *syms);

SYMBOL funs[] = {
  {
    .type = FUNCTION,
    .function.name = "error",
    .function.ptr = fnerror,
  },
  {
    .type = FUNCTION,
    .function.name = "write",
    .function.ptr = fnwrite,
  },
  {
    .type = FUNCTION,
    .function.name = "if",
    .function.ptr = fnif,
  },
  {
    .type = FUNCTION,
    .function.name = "+",
    .function.ptr = fnsum,
  },
  {
    .type = FUNCTION,
    .function.name = "-",
    .function.ptr = fnsub,
  },
  {
    .type = FUNCTION,
    .function.name = "*",
    .function.ptr = fnmul,
  },
  {
    .type = FUNCTION,
    .function.name = "/",
    .function.ptr = fndiv,
  },
  {
    .type = FUNCTION,
    .function.name = ">",
    .function.ptr = fngre,
  },
{
  .type = FUNCTION,
  .function.name = ">=",
  .function.ptr = fngeq,
},
{
  .type = FUNCTION,
  .function.name = "<",
  .function.ptr = fnlss,
},
{
  .type = FUNCTION,
  .function.name = "<=",
  .function.ptr = fnleq,
},
{
  .type = FUNCTION,
  .function.name = "=",
  .function.ptr = fnequ,
},
};
const unsigned int funcount = (sizeof (funs) / sizeof (SYMBOL));
