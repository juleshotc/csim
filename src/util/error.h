#ifndef _ERROR_H_
#define _ERROR_H_

/* void warn (const char *msg); */
/* void error (const char *msg); */
void panic (const char *fmt, ...);
void epanic (const char *msg);

#endif /* #ifndef ERROR_H*/
