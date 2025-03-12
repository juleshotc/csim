#ifndef _REPL_H_
#define _REPL_H_

extern int repl (int (*read) (void),
                 int (*eval) (const char *),
                 void (*print) (const char *, ...));

#endif /* #include _REPL_H_ */
