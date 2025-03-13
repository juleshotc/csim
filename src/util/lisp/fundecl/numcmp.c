#include "util.h"

#define FIRSTINT (1 << 0)
#define FIRSTFLOAT (1 << 1)
#define SECONDINT (1 << 2)
#define SECONDFLOAT (1 << 3)

#define INTINT (FIRSTINT | SECONDINT)
#define INTFLOAT (FIRSTINT | SECONDFLOAT)
#define FLOATINT (FIRSTFLOAT | SECONDINT)
#define FLOATFLOAT (FIRSTFLOAT | SECONDFLOAT)

SYMBOL
fngre (unsigned int argc, SYMBOL *syms)
{
  if (argc != 2)
    return rawerror (">: needs two arguments");

  SYMBOL first = syms[0];
  SYMBOL second = syms[1];

  int condition = 0;
  if (first.type == INTEGER)
    condition |= FIRSTINT;
  else if (first.type == FLOATING)
    condition |= FIRSTFLOAT;
  else
    rawerror (">: non-number first argument");

  if (second.type == INTEGER)
    condition |= SECONDINT;
  else if (second.type == FLOATING)
    condition |= SECONDFLOAT;
  else
    rawerror (">: non-number second argument");

  int val = 0;
  switch (condition)
    {
    case INTINT: val = first.integer > second.integer; break;
    case INTFLOAT: val = first.integer > second.floating; break;
    case FLOATINT: val = first.floating > second.integer; break;
    case FLOATFLOAT: val = first.floating > second.floating; break;
    default:
      rawerror (">: bogus state");
    }

  return (SYMBOL) { .type = BOOLEAN, .boolean = val, };
}

SYMBOL
fngeq (unsigned int argc, SYMBOL *syms)
{
  if (argc != 2)
    return rawerror (">=: needs two arguments");

  SYMBOL first = syms[0];
  SYMBOL second = syms[1];

  int condition = 0;
  if (first.type == INTEGER)
    condition |= FIRSTINT;
  else if (first.type == FLOATING)
    condition |= FIRSTFLOAT;
  else
    rawerror (">=: non-number first argument");

  if (second.type == INTEGER)
    condition |= SECONDINT;
  else if (second.type == FLOATING)
    condition |= SECONDFLOAT;
  else
    rawerror (">=: non-number second argument");

  int val = 0;
  switch (condition)
    {
    case INTINT: val = first.integer >= second.integer; break;
    case INTFLOAT: val = first.integer >= second.floating; break;
    case FLOATINT: val = first.floating >= second.integer; break;
    case FLOATFLOAT: val = first.floating >= second.floating; break;
    default:
      rawerror (">=: bogus state");
    }

  return (SYMBOL) { .type = BOOLEAN, .boolean = val, };
}

SYMBOL
fnlss (unsigned int argc, SYMBOL *syms)
{
  if (argc != 2)
    return rawerror ("<: needs two arguments");

  SYMBOL first = syms[0];
  SYMBOL second = syms[1];

  int condition = 0;
  if (first.type == INTEGER)
    condition |= FIRSTINT;
  else if (first.type == FLOATING)
    condition |= FIRSTFLOAT;
  else
    rawerror ("<: non-number first argument");

  if (second.type == INTEGER)
    condition |= SECONDINT;
  else if (second.type == FLOATING)
    condition |= SECONDFLOAT;
  else
    rawerror ("<: non-number second argument");

  int val = 0;
  switch (condition)
    {
    case INTINT: val = first.integer < second.integer; break;
    case INTFLOAT: val = first.integer < second.floating; break;
    case FLOATINT: val = first.floating < second.integer; break;
    case FLOATFLOAT: val = first.floating < second.floating; break;
    default:
      rawerror ("<: bogus state");
    }

  return (SYMBOL) { .type = BOOLEAN, .boolean = val, };
}

SYMBOL
fnleq (unsigned int argc, SYMBOL *syms)
{
  if (argc != 2)
    return rawerror ("<=: needs two arguments");

  SYMBOL first = syms[0];
  SYMBOL second = syms[1];

  int condition = 0;
  if (first.type == INTEGER)
    condition |= FIRSTINT;
  else if (first.type == FLOATING)
    condition |= FIRSTFLOAT;
  else
    rawerror ("<=: non-number first argument");

  if (second.type == INTEGER)
    condition |= SECONDINT;
  else if (second.type == FLOATING)
    condition |= SECONDFLOAT;
  else
    rawerror ("<=: non-number second argument");

  int val = 0;
  switch (condition)
    {
    case INTINT: val = first.integer <= second.integer; break;
    case INTFLOAT: val = first.integer <= second.floating; break;
    case FLOATINT: val = first.floating <= second.integer; break;
    case FLOATFLOAT: val = first.floating <= second.floating; break;
    default:
      rawerror ("<=: bogus state");
    }

  return (SYMBOL) { .type = BOOLEAN, .boolean = val, };
}

SYMBOL
fnequ (unsigned int argc, SYMBOL *syms)
{
  if (argc != 2)
    return rawerror ("=: needs two arguments");

  SYMBOL first = syms[0];
  SYMBOL second = syms[1];

  int condition = 0;
  if (first.type == INTEGER)
    condition |= FIRSTINT;
  else if (first.type == FLOATING)
    condition |= FIRSTFLOAT;
  else
    rawerror ("=: non-number first argument");

  if (second.type == INTEGER)
    condition |= SECONDINT;
  else if (second.type == FLOATING)
    condition |= SECONDFLOAT;
  else
    rawerror ("=: non-number second argument");

  int val = 0;
  switch (condition)
    {
    case INTINT: val = first.integer == second.integer; break;
    case INTFLOAT: val = first.integer == second.floating; break;
    case FLOATINT: val = first.floating == second.integer; break;
    case FLOATFLOAT: val = first.floating == second.floating; break;
    default:
      rawerror ("=: bogus state");
    }

  return (SYMBOL) { .type = BOOLEAN, .boolean = val, };
}
