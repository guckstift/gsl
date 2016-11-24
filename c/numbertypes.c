#include "numbertypes.h"
#include "memory.h"

Base intType[1];

Int* IntNew(gint init)
{
	Int* res;
	
	res = newobj(Int);
	BaseInit(res, intType);
	res->value = init;
	
	return res;
}
