#include "Object.h"
#include "memory.h"

Abstract gtObject;

Object* ObjectNew ()
{
	Object* res;
	
	res = gnew (Object, 1);
	ObjectInit (res);
	
	return res;
}

void ObjectInit (Object* obj)
{
	AbstractInit (&res->abstract, &gtObject);
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
