#include <string.h>
#include <stdio.h>
#include "gtable.h"
#include "memory.h"
#include "math.h"

/* private */

static void _initEntry (gentry* entry)
{
	entry->hash = 0;
	entry->name = 0;
	entry->value = 0;
}

static void _copyEntry (gentry* dest, gentry* src)
{
	dest->hash = src->hash;
	dest->name = src->name;
	dest->value = src->value;
}

static void _setEntry (gentry* entry, guint hash, gstring* name, void* value)
{
	entry->hash = hash;
	entry->name = name;
	entry->value = value;
}

/*
	Reposition a table entry located at oldIndex to its appropriate position in the table
*/
static void _reposition (gtable* table, guint oldIndex)
{
	guint newIndex;
	
	newIndex = _gtableCorrectPos (table, oldIndex);
	
	if (newIndex != oldIndex) {
		_copyEntry (&table->entries[newIndex], &table->entries[oldIndex]);
		_initEntry (&table->entries[oldIndex]);
	}
}

/*
	Resize the table to newCapacity and reposition each entry
*/
static guint _resize (gtable* table, guint newCapacity)
{
	guint i, oldCapacity;
	
	oldCapacity     = table->capacity;
	table->capacity = newCapacity;
	
	if (newCapacity > oldCapacity) {
		gresize (table->entries, gentry, table->capacity);
	
		for (i = 0; i < oldCapacity; i ++) {
			if (table->entries[i].name) {
				_reposition (table, i);
			}
		}
	}
	else if (newCapacity < oldCapacity) {
		table->capacity = newCapacity;
	
		for (i = 0; i < oldCapacity; i ++) {
			if (table->entries[i].name) {
				_reposition (table, i);
			}
		}
		
		gresize (table->entries, gentry, table->capacity);
	}
}

/* internal */

/*
	Give the nth probe position for a specific hash value in a table with a specific capacity
*/
guint _gtableProbeSeq (guint hash, guint capacity, guint n)
{
	return (hash + (n + n * n) / 2) % capacity;
}

/*
	Give the appropriate position for an entry located at oldIndex
*/
guint _gtableCorrectPos (gtable* table, guint oldIndex)
{
	guint hash, capacity, newIndex, i;
	
	hash = table->entries[oldIndex].hash;
	capacity = table->capacity;
	newIndex = _gtableProbeSeq (hash, capacity, 0);
	
	for (i = 0; i < capacity && newIndex != oldIndex && table->entries[newIndex].name; i ++) {
		newIndex = _gtableProbeSeq (hash, capacity, i);
	}
	
	return newIndex;
}

/*
	Lookup an entry in the table with its hash precalculated
*/
gbool _gtableLookupHash (gtable* table, gstring* name, guint hash, guint* index)
{
	guint _index, capacity, i;
	
	if (index == 0) {
		index = &_index;
	}
	
	capacity = table->capacity;
	*index = _gtableProbeSeq (hash, capacity, 0);
	
	for (i = 0; i < capacity; i ++) {
		if (table->entries[*index].name == 0) {
			return false;
		}
		else if (gstringEqual (name, table->entries[*index].name)) {
			return true;
		}
		
		*index = _gtableProbeSeq (hash, capacity, i);
	}
	
	return false;
}

/*
	Lookup an entry in the table
*/
gbool _gtableLookup (gtable* table, gstring* name, guint* index)
{
	return _gtableLookupHash (table, name, gstringHash (name), index);
}

/*
	Give the minimum needed capacity for a table with a specific usage and a current capacity
	curCapacity that can be achieved with the growth factor.
*/
guint _gtableNeededCapacity (guint usage, guint curCapacity)
{
	guint expandCapacity, shrinkCapacity, maxUsage, minUsage;
	
	expandCapacity = curCapacity * GTABLE_GROWTH_FACTOR_N / GTABLE_GROWTH_FACTOR_D;
	shrinkCapacity = curCapacity * GTABLE_GROWTH_FACTOR_D / GTABLE_GROWTH_FACTOR_N;
	
	if (expandCapacity == curCapacity) expandCapacity ++;
	
	maxUsage = curCapacity * GTABLE_MAX_USAGE_N / GTABLE_MAX_USAGE_D;
	minUsage = shrinkCapacity * GTABLE_MAX_USAGE_N / GTABLE_MAX_USAGE_D;
	
	if (usage > maxUsage) {
		return _gtableNeededCapacity (usage, expandCapacity);
	}
	else if (usage < minUsage) {
		return _gtableNeededCapacity (usage, shrinkCapacity);
	}
	else {
		return MAX (GTABLE_MIN_CAPACITY, curCapacity);
	}
}

/*
	Probe a free position for a hash to be placed in the table
*/
gbool _gtableFindFreePos (gtable* table, guint hash, guint* index)
{
	guint _index, i;
	
	if (index == 0) {
		index = &_index;
	}
	
	for (i = 0; i < table->capacity; i ++) {
		*index = _gtableProbeSeq (hash, table->capacity, i);
		
		if (table->entries[*index].name == 0) {
			return true;
		}
	}
	
	return false;
}

/* public */

gtable* gtableNew ()
{
	gtable* res;
	guint i;
	
	res = gnew (gtable, 1);
	res->capacity = GTABLE_MIN_CAPACITY;
	res->usage = 0;
	res->entries = gnew (gentry, res->capacity);
	
	for (i = 0; i < res->capacity; i ++) {
		_initEntry (&res->entries[i]);
	}
	
	return res;
}

void gtableSetValue (gtable* table, gstring* name, void* value)
{
	guint hash, index, neededCapacity;
	
	hash = gstringHash (name);
	
	if (_gtableLookupHash (table, name, hash, &index) == false) {
		neededCapacity = _gtableNeededCapacity (table->usage + 1, table->capacity);
		
		if (neededCapacity != table->capacity) {
			_resize (table, neededCapacity);
		}
		
		_gtableFindFreePos (table, hash, &index);
		table->usage ++;
	}
	
	_setEntry (&table->entries[index], hash, name, value);
}

void* gtableGetValue (gtable* table, gstring* name)
{
	guint hash, index;
	
	hash = gstringHash (name);
	
	if (_gtableLookupHash (table, name, hash, &index)) {
		return table->entries[index].value;
	}

	return 0;
}

garray* gtableGetKeys (gtable* table)
{
	garray* res;
	guint i;
	
	res = garrayNew ();
	
	for (i = 0; i < table->capacity; i ++) {
		if (table->entries[i].name)
			garrayAppend (res, table->entries[i].name);
	}
	
	return res;
}

garray* gtableGetValues (gtable* table)
{
	garray* res;
	guint i;
	
	res = garrayNew ();
	
	for (i = 0; i < table->capacity; i ++) {
		if (table->entries[i].name)
			garrayAppend (res, table->entries[i].value);
	}
	
	return res;
}
