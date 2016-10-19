#pragma once

#include "types.h"

#define GARRAY_MIN_CAPACITY    0
#define GARRAY_MAX_USAGE_N     1
#define GARRAY_MAX_USAGE_D     1
#define GARRAY_GROWTH_FACTOR_N 3
#define GARRAY_GROWTH_FACTOR_D 2

struct garray {
	guint capacity;
	guint usage;
	void** items;
};

garray* garrayNew ();
void garrayAppend (garray* array, void* item);
/* internals */
guint garrayNeededCapacity (guint usage, guint curCapacity);
