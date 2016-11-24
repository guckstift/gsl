#ifndef numbertypes_H
#define numbertypes_H

#include "basetypes.h"

typedef struct Int {
	Base_HEAD
	gint value;
} Int;

Int* IntNew(gint init);

extern Base intType[1];

#endif
