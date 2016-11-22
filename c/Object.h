#ifndef Object_H
#define Object_H

#include "basetypes.h"
#include "String.h"
#include "Array.h"

typedef struct Property {
	String* name;
	Base* value;
} Property;

typedef struct Object {
	VarBase_HEAD
	guint usage;
	Property* props;
} Object;

#define OBJECT_MIN_CAPACITY    4
#define OBJECT_MAX_USAGE_N     3
#define OBJECT_MAX_USAGE_D     4
#define OBJECT_GROWTH_FACTOR_N 2
#define OBJECT_GROWTH_FACTOR_D 1

Object* ObjectNew();
void ObjectInit(Object* obj);
void ObjectSetValue(Object* obj, String* name, Base* value);
Base* ObjectGetValue(Object* obj, String* name);
Array* ObjectGetKeys(Object* obj);
Array* ObjectGetValues(Object* obj);
/* internals */
guint ObjectProbeSeq(guint hash, guint capacity, guint pos);
guint ObjectGetCorrectPos(Object* obj, guint oldIndex);
gbool ObjectLookup(Object* obj, String* name, guint* index);
guint ObjectNeededCapacity(guint capacity, guint usage);
gbool ObjectFindFreePos(Object* obj, guint hash, guint* index);
void ObjectDemo();
void ObjectPrintInfo(Object* obj);

#endif
