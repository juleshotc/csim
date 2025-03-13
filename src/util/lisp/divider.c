#include "divider.h"

#include <ctype.h>

enum
{
  _UNKNOWN = 0,
  PARENS,
  SYMCHAR,
  STRLIT,
  QUOTE,
};

#define FLAGSTR (1 << 0)
#define FLAGESC (1 << 1)

static char mask;

int
tokenrule (int c)
{
  if (mask & FLAGSTR)
    {
      if (mask & FLAGESC)
        mask &= ~FLAGESC;
      else if (c == '\\')
        mask |= FLAGESC;
      else if (c == '\"')
        mask &= ~FLAGSTR;
      return STRLIT;
    }

  if (c == '\"')
    {
      mask |= FLAGSTR;
      return STRLIT;
    }
  
  if (c == '(' || c == ')')
    return PARENS;
  
  
  if (c == '\'')
    return QUOTE;
  
  if (isalnum (c) || c == '-' || c == '_' || c == '+' || c == '/' || c == '*' || c == '.' || c == '=' || c == '<' || c == '>')
    return SYMCHAR;
  
  return _UNKNOWN;
}
