#ifndef _LISP_DEFS_H_
#define _LISP_DEFS_H_

typedef enum
{
  NONE,
  STRING,
  INTEGER,
  FUNCTION,
  _LAST,
} TYPE;

typedef struct _obj
{
  int type;
  union
  {
    char *string;
    long long integer;
    struct
    {
      char *name;
      int argc;
      struct _obj (*ptr) (struct _obj *);
    } function;
  };
} OBJECT;

#endif /* #ifndef _LISP_DEFS_H_ */
