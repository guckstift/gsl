#include "Array.h"
#include "memory.h"
#include "math.h"

/* internals */

/*
	Give the minimum needed capacity for an array with a specific usage and a current capacity
	curCapacity that can be achieved with the growth factor.
*/
guint ArrayNeededCapacity(guint usage, guint curCapacity)
{
	guint expandCapacity, shrinkCapacity, maxUsage, minUsage;
	
	expandCapacity = curCapacity * ARRAY_GROWTH_FACTOR_N / ARRAY_GROWTH_FACTOR_D;
	shrinkCapacity = curCapacity * ARRAY_GROWTH_FACTOR_D / ARRAY_GROWTH_FACTOR_N;
	
	if (expandCapacity == curCapacity) expandCapacity ++;
	
	maxUsage = curCapacity * ARRAY_MAX_USAGE_N / ARRAY_MAX_USAGE_D;
	minUsage = shrinkCapacity * ARRAY_MAX_USAGE_N / ARRAY_MAX_USAGE_D;
	
	if (usage > maxUsage) {
		return ArrayNeededCapacity(usage, expandCapacity);
	}
	else if (usage < minUsage) {
		return ArrayNeededCapacity(usage, shrinkCapacity);
	}
	else {
		return max(ARRAY_MIN_CAPACITY, curCapacity);
	}
}

/* public */

Array* ArrayNew()
{
	Array* res;
	guint i;
	
	res = newobj(Array);
	res->length = ARRAY_MIN_CAPACITY;
	res->usage = 0;
	res->elms = newvec(Base*, res->length);
	
	for (i = 0; i < res->length; i ++) {
		res->elms[i] = 0;
	}
	
	return res;

}

void ArrayAppend(Array* array, Base* elm)
{
	guint neededCapacity, oldCapacity;
	
	oldCapacity = array->length;
	neededCapacity = ArrayNeededCapacity (array->usage + 1, oldCapacity);
	
	if (oldCapacity < neededCapacity) {
		array->length = neededCapacity;
		resizevec(array->elms, Base*, array->length);
	}

	array->elms[array->usage] = elm;
	array->usage ++;
}
