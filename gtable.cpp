#include <string.h>
#include <stdio.h>
#include "gtable.h"
#include "memory.h"
#include "math.h"
#include "print.h"

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

static void _reposition (gtable* table, guint oldIndex)
{
	guint newIndex;
	
	newIndex = _gtableCorrectPos (table, oldIndex);
	
	if (newIndex != oldIndex) {
		_copyEntry (&table->entries[newIndex], &table->entries[oldIndex]);
		_initEntry (&table->entries[oldIndex]);
	}
}

static guint _expand (gtable* table, guint mag)
{
	guint oldCapacity, newCapacity, i;
	
	oldCapacity = table->capacity;
	table->capacity = oldCapacity << mag;
	gresize (table->entries, gentry, table->capacity);
	
	for (i = 0; i < oldCapacity; i ++) {
		if (table->entries[i].name) {
			_reposition (table, i);
		}
	}
}

static guint _shrink (gtable* table, guint mag)
{
	guint oldCapacity, newCapacity, i;
	
	oldCapacity = table->capacity;
	newCapacity = table->capacity >> mag;
	newCapacity = newCapacity < 4 ? 4 : newCapacity;
	table->capacity = newCapacity;
	
	for (i = newCapacity; i < oldCapacity; i ++) {
		if (table->entries[i].name) {
			_reposition (table, i);
		}
	}
	
	gresize (table->entries, gentry, newCapacity);
}

/* internal */

guint _gtableProbeSeq (guint hash, guint capacity, guint pos)
{
	return (hash + (pos + pos * pos) / 2) % capacity;
}

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

gbool _gtableLookup (gtable* table, gstring* name, guint* index)
{
	return _gtableLookupHash (table, name, gstringHash (name), index);
}

guint _gtableNeededCapacity (guint usage)
{
	guint capacity;
	
	capacity = nextPowerOf2 (usage);
	
	if (usage >= capacity * 3 / 4) {
		capacity <<= 1;
	}
	
	if (capacity < 4) {
		capacity = 4;
	}
	
	return capacity;
}

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
	res->capacity = 4;
	res->usage = 0;
	res->entries = gnew (gentry, res->capacity);
	
	for (i = 0; i < res->capacity; i ++) {
		_initEntry (&res->entries[i]);
	}
	
	return res;
}

void gtableSetValue (gtable* table, gstring* name, void* value)
{
	guint hash, index;
	
	hash = gstringHash (name);
	
	if (_gtableLookupHash (table, name, hash, &index) == false) {
		if (_gtableNeededCapacity (table->usage + 1) > table->capacity) {
			_expand (table, 1);
		}
		
		_gtableFindFreePos (table, hash, &index);
		table->usage ++;
	}
	
	_setEntry (&table->entries[index], hash, name, value);
	
	printf("index: ");printUlDec(index); printNl();
	printf("usage: ");printUlDec(table->usage); printNl();
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
