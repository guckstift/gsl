#ifndef Array_H
#define Array_H

#include "basetypes.h"

#define ARRAY_MIN_CAPACITY    0
#define ARRAY_MAX_USAGE_N     1
#define ARRAY_MAX_USAGE_D     1
#define ARRAY_GROWTH_FACTOR_N 3
#define ARRAY_GROWTH_FACTOR_D 2

typedef struct Array {
	VarBase_HEAD
	guint usage;
	Base** elms;
} Array;

extern Base arrayType[1];

Array* ArrayNew();
void ArrayAppend(Array* array, Base* elm);
/* internals */
guint ArrayNeededCapacity(guint usage, guint curCapacity);

#endif
