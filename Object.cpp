#include "Object.h"
#include "memory.h"

Object* ObjectNew ()
{
	Object* res;
	
	res = gnew (Object, 1);
	ObjectInit (res);
	
	return res;
}

void ObjectInit (Object* obj)
{
	gtableInit (&obj->table);
}

void ObjectSetValue (Object* obj, gstring* name, Object* value)
{
	gtableSetValue (&obj->table, name, value);
}

Object* ObjectGetValue (Object* obj, gstring* name)
{
	return (Object*)gtableGetValue (&obj->table, name);
}
