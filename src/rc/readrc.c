#include "readrc.h"

#include "../util/fileio.h"
#include "../util/repl.h"
#include "../util/log.h"
#include "../util/error.h"
#include "../util/lisp/parse.h"
#include "../util/lisp/divider.h"

void
readrc (void)
{
  const char *dirpath = "./data";
  if (mount (dirpath))
    panic ("[readrc] Failed to open %s", dirpath);
  if (browse ("r"))
    panic ("[readrc] Failed to find file");

  repl (read, tokenrule, parse, printl);
  
  umount ();
}
