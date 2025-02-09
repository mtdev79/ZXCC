/*
 *  Change the directories in these #defines if necessary. Note trailing slash.
 */

#include "config.h"

#ifdef __MSDOS__

	#define BINDIR80 "d:/tools/cpm/bin80/"
	#define LIBDIR80 "d:/tools/cpm/lib80/"
	#define INCDIR80 "d:/tools/cpm/include/"
#else
/* Unless overridden, these are defined by autoconf. Note trailing slash.
 	#undef BINDIR80
 	#undef LIBDIR80
 	#undef INCDIR80
	#define BINDIR80 "/usr/local/lib/cpm/bin80/"
	#define LIBDIR80 "/usr/local/lib/cpm/lib80/"
	#define INCDIR80 "/usr/local/lib/cpm/include80/"
*/
#endif

char bindir80[1024];
char libdir80[1024];
char incdir80[1024];

#define SERIAL "ZXCC05"

/* System include files */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#ifdef __MSDOS
#include <dos.h>
#endif

/* Library includes */

#ifdef USE_CPMIO
#include "cpmio.h"
#endif

#ifdef USE_CPMGSX
#include "cpmgsx.h"
#endif

#include <cpmredir.h>	/* BDOS disc simulation */

typedef unsigned char byte;	/* Must be exactly 8 bits */
typedef unsigned short word;	/* Must be exactly 16 bits */

/* Prototypes */

void ed_fe  (byte *a, byte *b, byte *c, byte *d, byte *e, byte *f,
             byte *h, byte *l, word *pc, word *ix, word *iy);
void cpmbdos(byte *a, byte *b, byte *c, byte *d, byte *e, byte *f, 
             byte *h, byte *l, word *pc, word *ix, word *iy);
void cpmbios(byte *a, byte *b, byte *c, byte *d, byte *e, byte *f, 
             byte *h, byte *l, word *pc, word *ix, word *iy);
void dump_regs(FILE *fp, byte a, byte b, byte c, byte d, byte e, byte f, 
             byte h, byte l, word pc, word ix, word iy);
void Msg(char *s, ...);
int zxcc_term(void);
void zxcc_exit(int code);

/* Global variables */

extern char *progname;
extern char **argv;
extern int argc;
extern byte RAM[65536]; /* The Z80's address space */

/* Z80 CPU emulation */

#include "z80.h"

