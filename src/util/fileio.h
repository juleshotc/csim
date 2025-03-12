#ifndef FILEIO_H
#define FILEIO_H

extern int mount (const char *dirpath); /* Set folder */
extern void umount (void); /* Release folder */
extern int browse (const char *mode); /* Next open file */
extern const char *brname (void);
extern int read (void);

#endif /* #ifndef FILEIO_Hdefine FILEIO_H */
