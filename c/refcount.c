#include "refcount.h"

void _incRefCount(Base* obj)
{
	if (obj && obj->refcount != NO_REFCOUNT) {
		obj->refcount ++;
	}
}

void _decRefCount(Base* obj)
{
	if (obj && obj->refcount != NO_REFCOUNT) {
		if (obj->refcount > 0) {
			obj->refcount --;
		}
	}
}

void _lockRefCount(Base* obj)
{
	if (obj) {
		obj->refcount = NO_REFCOUNT;
	}
}
