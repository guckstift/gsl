#include "gtable.h"

gtable* gtableNew ()
{
	gtable* res;
	
	res = (gtable*)gmalloc (sizeof (gtable));
	res->capacity = 4;
	res->usage = 0;
	res->entries = (gtable*)gmalloc (res->capacity * sizeof (gentry));
}
