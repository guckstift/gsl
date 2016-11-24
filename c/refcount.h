#ifndef refcount_H
#define refcount_H

#include "basetypes.h"

void _incRefCount(Base* obj);
void _decRefCount(Base* obj);
void _lockRefCount(Base* obj);

#define incRefCount(obj) \
	_incRefCount((Base*)(obj))
	
#define decRefCount(obj) \
	_incRefCount((Base*)(obj))
	
#define lockRefCount(obj) \
	_incRefCount((Base*)(obj))

#define NO_REFCOUNT MAX_UINT

#endif
