#include "garray.h"
#include "memory.h"
#include "math.h"

/* internals */

/*
	Give the minimum needed capacity for an array with a specific usage and a current capacity
	curCapacity that can be achieved with the growth factor.
*/
guint garrayNeededCapacity (guint usage, guint curCapacity)
{
	guint expandCapacity, shrinkCapacity, maxUsage, minUsage;
	
	expandCapacity = curCapacity * GARRAY_GROWTH_FACTOR_N / GARRAY_GROWTH_FACTOR_D;
	shrinkCapacity = curCapacity * GARRAY_GROWTH_FACTOR_D / GARRAY_GROWTH_FACTOR_N;
	
	if (expandCapacity == curCapacity) expandCapacity ++;
	
	maxUsage = curCapacity * GARRAY_MAX_USAGE_N / GARRAY_MAX_USAGE_D;
	minUsage = shrinkCapacity * GARRAY_MAX_USAGE_N / GARRAY_MAX_USAGE_D;
	
	if (usage > maxUsage) {
		return garrayNeededCapacity (usage, expandCapacity);
	}
	else if (usage < minUsage) {
		return garrayNeededCapacity (usage, shrinkCapacity);
	}
	else {
		return MAX (GARRAY_MIN_CAPACITY, curCapacity);
	}
}

/* public */

garray* garrayNew ()
{
	garray* res;
	guint i;
	
	res = gnew (garray, 1);
	res->capacity = GARRAY_MIN_CAPACITY;
	res->usage = 0;
	res->items = gnew (void*, res->capacity);
	
	for (i = 0; i < res->capacity; i ++) {
		res->items[i] = 0;
	}
	
	return res;

}

void garrayAppend (garray* array, void* item)
{
	guint neededCapacity, oldCapacity;
	
	oldCapacity    = array->capacity;
	neededCapacity = garrayNeededCapacity (array->usage + 1, oldCapacity);
	
	if (oldCapacity < neededCapacity) {
		array->capacity = neededCapacity;
		gresize (array->items, void*, array->capacity);
	}

	array->items[array->usage] = item;
	array->usage ++;
}
