#include <string.h>
#include <stdio.h>
#include "Object.h"
#include "memory.h"
#include "math.h"
#include "print.h"
#include "refcount.h"
#include "numbertypes.h"

Base objectType[1];

/* private */

static void _initProp(Property* prop)
{
	prop->name = 0;
	prop->value = 0;
}

static void _copyProp(Property* dest, Property* src)
{
	dest->name = src->name;
	dest->value = src->value;
}

static void _setProp(Property* prop, String* name, void* value)
{
	prop->name = name;
	prop->value = value;
}

/*
	Reposition a table entry located at oldIndex to its appropriate position in the table
*/
static void _reposition(Object* obj, guint oldIndex)
{
	guint newIndex;
	
	newIndex = ObjectGetCorrectPos(obj, oldIndex);
	
	if (newIndex != oldIndex) {
		_copyProp(&obj->props[newIndex], &obj->props[oldIndex]);
		_initProp(&obj->props[oldIndex]);
	}
}

/*
	Resize the table to newCapacity and reposition each entry
*/
static void _resize(Object* obj, guint newCapacity)
{
	guint i, oldCapacity;
	
	oldCapacity = obj->length;
	obj->length = newCapacity;
	
	if (newCapacity > oldCapacity) {
		resizevec(obj->props, Property, obj->length);
	
		for (i = 0; i < oldCapacity; i ++) {
			if (obj->props[i].name) {
				_reposition(obj, i);
			}
		}
	}
	else if (newCapacity < oldCapacity) {
		for (i = 0; i < oldCapacity; i ++) {
			if (obj->props[i].name) {
				_reposition(obj, i);
			}
		}
		
		resizevec(obj->props, Property, obj->length);
	}
}

/* internals */

/*
	Give the nth probe position for a specific hash value in a table with a specific capacity
*/
guint ObjectProbeSeq(guint hash, guint capacity, guint n)
{
	return (hash + (n + n * n) / 2) % capacity;
}

/*
	Give the appropriate position for an entry located at oldIndex
*/
guint ObjectGetCorrectPos(Object* obj, guint oldIndex)
{
	guint hash, capacity, newIndex, i;
	
	hash = StringHash(obj->props[oldIndex].name);
	capacity = obj->length;
	newIndex = ObjectProbeSeq(hash, capacity, 0);
	
	for (i = 0; i < capacity && newIndex != oldIndex && obj->props[newIndex].name; i ++) {
		newIndex = ObjectProbeSeq(hash, capacity, i);
	}
	
	return newIndex;
}

/*
	Lookup an entry in the table
*/
gbool ObjectLookup(Object* obj, String* name, guint* index)
{
	guint _index, capacity, i, hash;
	
	if (index == 0) {
		index = &_index;
	}

	capacity = obj->length;
	hash = StringHash(name);
	*index = ObjectProbeSeq(hash, capacity, 0);
	
	for (i = 0; i < capacity; i ++) {
		if (obj->props[*index].name &&
			StringHash(obj->props[*index].name) == hash &&
			StringEqual(obj->props[*index].name, name))
		{
			return gtrue;
		}
		
		*index = ObjectProbeSeq(hash, capacity, i);
	}
	
	return gfalse;
}

/*
	Give the minimum needed capacity for a table with a specific usage and a current capacity
	curCapacity that can be achieved with the growth factor.
*/
guint ObjectNeededCapacity(guint usage, guint curCapacity)
{
	guint expandCapacity, shrinkCapacity, maxUsage, minUsage;
	
	expandCapacity = curCapacity * OBJECT_GROWTH_FACTOR_N / OBJECT_GROWTH_FACTOR_D;
	shrinkCapacity = curCapacity * OBJECT_GROWTH_FACTOR_D / OBJECT_GROWTH_FACTOR_N;
	
	if (expandCapacity == curCapacity) expandCapacity ++;
	
	maxUsage = curCapacity * OBJECT_MAX_USAGE_N / OBJECT_MAX_USAGE_D;
	minUsage = shrinkCapacity * OBJECT_MAX_USAGE_N / OBJECT_MAX_USAGE_D;
	
	if (usage > maxUsage) {
		return ObjectNeededCapacity(usage, expandCapacity);
	}
	else if (usage < minUsage) {
		return ObjectNeededCapacity(usage, shrinkCapacity);
	}
	else {
		return max(OBJECT_MIN_CAPACITY, curCapacity);
	}
}

/*
	Probe a free position for a hash to be placed in the table
*/
gbool ObjectFindFreePos(Object* obj, guint hash, guint* index)
{
	guint _index, i;
	
	if (index == 0) {
		index = &_index;
	}
	
	for (i = 0; i < obj->length; i ++) {
		*index = ObjectProbeSeq(hash, obj->length, i);
		
		if (obj->props[*index].name == 0) {
			return gtrue;
		}
	}
	
	return gfalse;
}

void ObjectDemo()
{
	Object* obj;
	
	obj = ObjectNew();
	
	ObjectSetValue(obj, StringFromCstr("null"), (Base*)IntNew(0));
	ObjectPrintInfo(obj);

	ObjectSetValue(obj, StringFromCstr("eins"), (Base*)IntNew(1));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("zwei"), (Base*)IntNew(2));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("drei"), (Base*)IntNew(3));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("vier"), (Base*)IntNew(4));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("fuenf"), (Base*)IntNew(5));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("sechs"), (Base*)IntNew(6));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("sieben"), (Base*)IntNew(7));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("acht"), (Base*)IntNew(8));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("neun"), (Base*)IntNew(9));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("zehn"), (Base*)IntNew(10));
	ObjectPrintInfo(obj);

	ObjectSetValue(obj, StringFromCstr("elf"), (Base*)IntNew(11));
	ObjectPrintInfo(obj);
	
	ObjectSetValue(obj, StringFromCstr("zwoelf"), (Base*)IntNew(12));
	ObjectPrintInfo(obj);
	
	printf("===================\n--- Abruf\n");
	
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("null")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("eins")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("zwei")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("drei")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("vier")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("fuenf")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("sechs")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("sieben")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("acht")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("neun")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("zehn")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("elf")))->value); printf(" ");
	printUlDec(((Int*)ObjectGetValue(obj, StringFromCstr("zwoelf")))->value); printf(" ");
	printNl();
}

void ObjectPrintInfo(Object* obj)
{
	int i;
	Array* keys;
	Array* vals;
	String* key;
	guint val;
	
	printf("--- Hashtable (%lu/%lu)\n", obj->usage, obj->length);
	for (i=0; i<obj->length; i++) {
		key = (String*)obj->props[i].name;
		val = (guint)obj->props[i].value;
		if (key) {
			printf("#%i : H = %lu ", i, StringHash(key));
			printf("K = "); StringPrint(key);
			printf(" V = %lu", ((Int*)val)->value);
		}
		else {
			printf("#%i", i);
		}
		printf("\n");
	}
	
	keys = ObjectGetKeys(obj);
	
	printf ("\n--- Key-Array\n");
	for (i=0; i<keys->usage; i++) {
		StringPrint((String*)keys->elms[i]); printf(" ");
	}
	
	vals = ObjectGetValues(obj);
	
	printf("\n--- Value-Array\n");
	for (i=0; i<vals->usage; i++) {
		printf("%lu ", ((Int*)vals->elms[i])->value);
	}
	
	printNl();
}

/* public */

Object* ObjectNew()
{
	Object* res;
	
	res = newobj(Object);
	ObjectInit(res);
	
	return res;
}

void ObjectInit(Object* obj)
{
	guint i;
	
	BaseInit(obj, objectType);
	obj->length = OBJECT_MIN_CAPACITY;
	obj->usage = 0;
	obj->props = newvec(Property, obj->length);
	
	for (i = 0; i < obj->length; i ++) {
		_initProp(&obj->props[i]);
	}
}

void ObjectSetValue(Object* obj, String* name, Base* value)
{
	guint hash, index, neededCapacity;
	String* oldName;
	Base* oldValue;
	
	hash = StringHash(name);
	
	if (ObjectLookup(obj, name, &index) == gfalse) {
		neededCapacity = ObjectNeededCapacity(obj->usage + 1, obj->length);
		
		if (neededCapacity != obj->length) {
			_resize(obj, neededCapacity);
		}
		
		ObjectFindFreePos(obj, hash, &index);
		obj->usage ++;
	}
	
	oldName = obj->props[index].name;
	oldValue = obj->props[index].value;
	_setProp(&obj->props[index], name, value);
	incRefCount(name);
	incRefCount(value);
	decRefCount(oldName);
	decRefCount(oldValue);
}

Base* ObjectGetValue(Object* obj, String* name)
{
	guint index;
	
	if (ObjectLookup(obj, name, &index)) {
		return obj->props[index].value;
	}

	return 0;
}

Array* ObjectGetKeys(Object* obj)
{
	Array* res;
	guint i;
	
	res = ArrayNew();
	
	for (i = 0; i < obj->length; i ++) {
		if (obj->props[i].name)
			ArrayAppend(res, (Base*)obj->props[i].name);
	}
	
	return res;
}

Array* ObjectGetValues(Object* obj)
{
	Array* res;
	guint i;
	
	res = ArrayNew ();
	
	for (i = 0; i < obj->length; i ++) {
		if (obj->props[i].name)
			ArrayAppend(res, (Base*)obj->props[i].value);
	}
	
	return res;
}
