#include "numtostr.h"

static int _ulToDec(guint x, char* buf)
{
	char c;
	int i;
	
	c = x % 10 + '0';
	x /= 10;
	i = x ? 1 + _ulToDec(x, buf) : 0;
	buf[i] = c;
	
	return i;
}

char* ulToDec(guint x, char* buf)
{
	int l;
	
	l = _ulToDec(x, buf) + 1;
	buf[l] = 0;
	
	return buf;
}

static int _ulToHex(guint x, char* buf)
{
	int h, i;
	char c;
	
	h = x % 16;
	c = h > 9 ? h - 10 + 'a' : h + '0';
	x /= 16;
	i = x ? 1 + _ulToHex(x, buf) : 0;
	buf[i] = c;
	
	return i;
}

char* ulToHex(guint x, char* buf)
{
	int l;
	
	l = _ulToHex(x, buf) + 1;
	buf[l] = 0;
	
	return buf;
}

static int _ulToBin(guint x, char* buf)
{
	char c;
	int i;
	
	c = x % 2 + '0';
	x >>= 1;
	i = x ? 1 + _ulToBin(x, buf) : 0;
	buf[i] = c;
	
	return i;
}

char* ulToBin(guint x, char* buf)
{
	int l;
	
	l = _ulToBin(x, buf) + 1;
	buf[l] = 0;
	
	return buf;
}

char* slToDec(gint x, char* buf)
{
	buf[0] = x < 0 ? '-' : '+';
	ulToDec(x < 0 ? -x : +x, &buf[1]);
	
	return buf;
}

char* slToHex(gint x, char* buf)
{
	buf[0] = x < 0 ? '-' : '+';
	ulToHex(x < 0 ? -x : +x, &buf[1]);
	
	return buf;
}

char* slToBin(gint x, char* buf)
{
	buf[0] = x < 0 ? '-' : '+';
	ulToBin(x < 0 ? -x : +x, &buf[1]);
	
	return buf;
}
