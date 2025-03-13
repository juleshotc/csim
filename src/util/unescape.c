#include <string.h>

char*
unescape (const char* src,
          void *(*alloc) (unsigned long))
{
  if (!src || *src != '"' || src[strlen(src) - 1] != '"')
    return 0;  /* Invalid string format */

  const size_t srclen = strlen(src);
  const char* start = src + 1;         /* Skip opening quote */
  const char* end = src + srclen - 1; /* Points to closing quote */
  size_t destlen = 0;

  /* First pass: calculate required length */
  const char* p = start;
  while (p < end)
    {
      if (*p == '\\' && (p + 1 < end))
        {
          switch (*(p + 1))
            {
            case 'n': case 't': case 'r': case 'b':
            case '\\': case '"': case '\'':
              destlen++;
              p += 2;
              break;
            default:
              destlen += 2;  // Treat invalid escape as literal
              p += 2;
              break;
            }
        }
      else
        {
          destlen++;
          p++;
        }
    }

  // Allocate exact required space + null terminator
  char* dest = alloc(destlen + 1);

  // Second pass: process escapes
  p = start;
  char* q = dest;
  while (p < end)
    {
      if (*p == '\\' && (p + 1 < end))
        {
          switch (*(p + 1))
            {
            case 'n':  *q++ = '\n'; p += 2; break;
            case 't':  *q++ = '\t'; p += 2; break;
            case 'r':  *q++ = '\r'; p += 2; break;
            case 'b':  *q++ = '\b'; p += 2; break;
            case '\\': *q++ = '\\'; p += 2; break;
            case '"':  *q++ = '\"'; p += 2; break;
            case '\'': *q++ = '\''; p += 2; break;
            default:
              *q++ = *p++;  // Copy backslash
              *q++ = *p++;  // Copy escaped character
              break;
            }
        }
      else
        {
          *q++ = *p++;
        }
    }
  *q = '\0';

  return dest;
}
