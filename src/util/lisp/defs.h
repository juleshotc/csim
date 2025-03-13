#ifndef _LISP_DEFS_H_
#define _LISP_DEFS_H_

typedef enum {
  NONE,
  BOOLEAN,
  STRING,
  INTEGER,
  FLOATING,
  FUNCTION,
  _LAST,
} TYPE;

typedef struct _sym SYMBOL;
typedef SYMBOL (*FUNPTR) (unsigned int, SYMBOL *);

struct _sym {
  int            type;
  union {
    int          boolean;
    char        *string;
    long long    integer;
    long double  floating;
    struct {
      char      *name;
      FUNPTR     ptr;
    } function;
  };
};

#endif /* #ifndef _LISP_DEFS_H_ */
