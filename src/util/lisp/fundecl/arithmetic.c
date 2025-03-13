#include "util.h"

SYMBOL
fnsum (unsigned int argc, SYMBOL *syms)
{
  if (argc <= 1)
    return rawerror ("+: too few arguments");

  long long   intsum   = 0;
  long double floatsum = 0;

  int isfloat = 0;
  for (unsigned int i = 0; i < argc; ++i)
    {
      SYMBOL sym = syms[i];
      if (sym.type == INTEGER)
        {
          if (isfloat)
            {
              floatsum += sym.integer;
            }
          else
            {
              intsum += sym.integer;
              floatsum += sym.integer;
            }
        }
      else if (sym.type == FLOATING)
        {
          isfloat = 1;
          floatsum += sym.floating;
        }
      else
        {
          return rawerror ("+: cannot add type");
        }
    }
  if (isfloat)
    return (SYMBOL) { .type = FLOATING, .floating = floatsum, };
  return (SYMBOL) { .type = INTEGER, .integer = intsum, };
}

SYMBOL
fnsub (unsigned int argc, SYMBOL *syms)
{
  if (argc <= 1)
    return rawerror ("-: too few arguments");

  long long   intsub = 0;
  long double floatsub = 0;
  int isfloat = 0;

  if (syms[0].type == INTEGER)
    {
      isfloat = 0;
      intsub = syms[0].integer;
      floatsub = syms[0].integer;
    }
  else if (syms[0].type == FLOATING)
    {
      isfloat = 1;
      floatsub = syms[0].floating;
    }
  
  for (unsigned int i = 1; i < argc; ++i)
    {
      SYMBOL sym = syms[i];
      if (sym.type == INTEGER)
        {
          if (isfloat)
            {
              floatsub -= sym.integer;
            }
          else
            {
              intsub -= sym.integer;
              floatsub -= sym.integer;
            }
        }
      else if (sym.type == FLOATING)
        {
          isfloat = 1;
          floatsub -= sym.floating;
        }
      else
        {
          return rawerror ("-: cannot subtract type");
        }
    }
  if (isfloat)
    return (SYMBOL) { .type = FLOATING, .floating = floatsub, };
  return (SYMBOL) { .type = INTEGER, .integer = intsub, };
}

SYMBOL
fnmul (unsigned int argc, SYMBOL *syms)
{
  if (argc <= 1)
    return rawerror ("*: too few arguments");

  long long   intmul   = 1;
  long double floatmul = 1;

  int isfloat = 0;
  for (unsigned int i = 0; i < argc; ++i)
    {
      SYMBOL sym = syms[i];
      if (sym.type == INTEGER)
        {
          if (isfloat)
            {
              floatmul *= sym.integer;
            }
          else
            {
              intmul *= sym.integer;
              floatmul *= sym.integer;
            }
        }
      else if (sym.type == FLOATING)
        {
          isfloat = 1;
          floatmul *= sym.floating;
        }
      else
        {
          return rawerror ("*: cannot multiply type");
        }
    }
  if (isfloat)
    return (SYMBOL) { .type = FLOATING, .floating = floatmul, };
  return (SYMBOL) { .type = INTEGER, .integer = intmul, };
}

SYMBOL
fndiv (unsigned int argc, SYMBOL *syms)
{
  if (argc <= 1)
    return rawerror ("-: too few arguments");

  long long   intdiv = 0;
  long double floatdiv = 0;
  int isfloat = 0;

  if (syms[0].type == INTEGER)
    {
      isfloat = 0;
      intdiv = syms[0].integer;
      floatdiv = syms[0].integer;
    }
  else if (syms[0].type == FLOATING)
    {
      isfloat = 1;
      floatdiv = syms[0].floating;
    }
  
  for (unsigned int i = 1; i < argc; ++i)
    {
      SYMBOL sym = syms[i];
      if (sym.type == INTEGER)
        {
          if (sym.integer == 0)
            {
              return rawerror ("/: divide by zero operation");
            }
          if (isfloat)
            {
              floatdiv /= sym.integer;
            }
          else
            {
              intdiv /= sym.integer;
              floatdiv /= sym.integer;
            }
        }
      else if (sym.type == FLOATING)
        {
          if (sym.floating == 0)
            {
              return rawerror ("/: divide by zero operation");
            }
          isfloat = 1;
          floatdiv /= sym.floating;
        }
      else
        {
          return rawerror ("/: cannot divide type");
        }
    }
  if (isfloat)
    return (SYMBOL) { .type = FLOATING, .floating = floatdiv, };
  return (SYMBOL) { .type = INTEGER, .integer = intdiv, };
}
