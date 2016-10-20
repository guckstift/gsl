#pragma once

#include "Abstract.h"
#include "gtable.h"

struct Object {
	Abstract abstract;
	gtable table;
};

Object* ObjectNew ();
void ObjectInit (Object* obj);
void ObjectSetValue (Object* obj, gstring* name, Object* value);
Object* ObjectGetValue (Object* obj, gstring* name);

extern Abstract gtObject;
