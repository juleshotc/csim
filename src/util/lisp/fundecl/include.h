#ifndef _FUNDECL_INCLUDES_H_
#define _FUNDECL_INCLUDES_H_

#include "../defs.h"

inline SYMBOL
rawerror (char *str)
{
  printf ("[ERROR] %s\n", str);
  return nullsym;
}

#endif /* #ifndef _FUNDECL_INCLUDES_H_ */
