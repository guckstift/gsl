#include <stdio.h>
#include "numtostr.h"

void printNl()
{
	fputs("\n", stdout);
}

void printUlDec(guint x)
{
	char buf[32];
	fputs(ulToDec(x, buf), stdout);
}

void printUlHex(guint x)
{
	char buf[32];
	fputs(ulToHex(x, buf), stdout);
}

void printUlBin(guint x)
{
	char buf[128];
	fputs(ulToBin(x, buf), stdout);
}

void printSlDec(gint x)
{
	char buf[32];
	fputs(slToDec(x, buf), stdout);
}

void printSlHex(gint x)
{
	char buf[32];
	fputs(slToHex(x, buf), stdout);
}

void printSlBin (gint x)
{
	char buf[128];
	fputs(slToBin(x, buf), stdout);
}
