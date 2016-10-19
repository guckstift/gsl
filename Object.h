#pragma once

#include "gtable.h"

struct Object {
	gtable table;
};

Object* ObjectNew ();
void ObjectInit (Object* obj);
void ObjectSetValue (Object* obj, gstring* name, Object* value);
Object* ObjectGetValue (Object* obj, gstring* name);
