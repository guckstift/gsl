#ifndef math_H
#define math_H

#include "basetypes.h"

guint nextPowerOf2(guint val);
guint normalize(guint x);
guint clz(guint x);

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))
#define clamp(x,l,u) min(max(x, l), u)

#endif
