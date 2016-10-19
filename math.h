#pragma once

#include "types.h"

guint nextPowerOf2 (guint val);
guint normalize (guint x);
guint clz (guint x);

#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define CLAMP(x,l,u) MIN (MAX (x, l), u)
