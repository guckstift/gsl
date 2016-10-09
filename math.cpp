#include "math.h"

guint nextPowerOf2 (guint val)
{
	val --;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	val |= val >> 32;
	val ++;
	return val;
}
