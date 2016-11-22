#include "math.h"

guint nextPowerOf2(guint x)
{
	x --;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	x ++;
	
	return x;
}

guint normalize(guint x)
{
	if ((x & 0xffffffff00000000) == 0) x <<= 32;
	if ((x & 0xffff000000000000) == 0) x <<= 16;
	if ((x & 0xff00000000000000) == 0) x <<=  8;
	if ((x & 0xf000000000000000) == 0) x <<=  4;
	if ((x & 0xc000000000000000) == 0) x <<=  2;
	if ((x & 0x8000000000000000) == 0) x <<=  1;
	
	return x;
}

guint clz(guint x)
{
	int n;
	
	n = 0;
	if ((x & 0xffffffff00000000) == 0) { n += 32; x <<= 32; }
	if ((x & 0xffff000000000000) == 0) { n += 16; x <<= 16; }
	if ((x & 0xff00000000000000) == 0) { n +=  8; x <<=  8; }
	if ((x & 0xf000000000000000) == 0) { n +=  4; x <<=  4; }
	if ((x & 0xc000000000000000) == 0) { n +=  2; x <<=  2; }
	if ((x & 0x8000000000000000) == 0) { n +=  1; x <<=  1; }
	
	return n;
}
