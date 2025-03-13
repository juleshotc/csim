#include "reserve.h"

#include "error.h"
#include <stdlib.h>

void *
reserve (unsigned long size)
{
  void *ptr = malloc (size);
  if (!ptr)
    panic ("[reserve] malloc failed for size %ld\n", size);
  return ptr;
}
