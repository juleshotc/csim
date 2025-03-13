#include "../lib/tinydir.h"

#include "fileio.h"
#include "error.h"
#include <stdio.h> /* fopen */

#define NAMEMAX 32

static tinydir_dir  dir;
static FILE        *file;
static char         namebuf[NAMEMAX];

int
mount (const char *dirpath)
{
  return tinydir_open (&dir, dirpath);
}

void
umount (void)
{
  tinydir_close (&dir);
  if (file)
    fclose (file);
}

int
browse (const char *mode)
{
  tinydir_file tmpfile;
  while (dir.has_next)
    {
      tinydir_readfile (&dir, &tmpfile);
      tinydir_next (&dir);
      if (tmpfile.is_dir)
        continue;
      if (file)
        fclose (file);
      file = fopen (tmpfile.path, mode);
      if (!file)
        epanic ("[browse] Error opening %s", tmpfile.path);
      int length = snprintf (namebuf, NAMEMAX, "%s", tmpfile.path);
      if (length >= NAMEMAX)
        {
          /* snprintf (&namebuf[NAMEMAX - 4], 4, "..."); */
          namebuf[NAMEMAX - 1] = '\0';
          namebuf[NAMEMAX - 2] = '.';
          namebuf[NAMEMAX - 3] = '.';
          namebuf[NAMEMAX - 4] = '.';
        }
      return 0;
    }
  return 1;
}

int
read (void)
{
  if (feof (file))
    return -1;
  int letter = fgetc (file);
  if (ferror (file))
    panic ("[read] ferror hit\n");
  return letter;
}

const char *
brname (void)
{
  return namebuf;
}
