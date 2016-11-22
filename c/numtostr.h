#ifndef numtostr_H
#define numtostr_H

#include "basetypes.h"

char* ulToDec(guint x, char* buf);
char* ulToHex(guint x, char* buf);
char* ulToBin(guint x, char* buf);
char* slToDec(gint x, char* buf);
char* slToHex(gint x, char* buf);
char* slToBin(gint x, char* buf);

#endif
