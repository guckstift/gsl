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

/*
	Reposition a table entry located at oldIndex to its appropriate position in the table
*/
static void _reposition (gtable* table, guint oldIndex)
{
	guint newIndex;
	
	newIndex = gtableCorrectPos (table, oldIndex);
	
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

/* internals */

/*
	Give the nth probe position for a specific hash value in a table with a specific capacity
*/
guint gtableProbeSeq (guint hash, guint capacity, guint n)
{
	return (hash + (n + n * n) / 2) % capacity;
}

/*
	Give the appropriate position for an entry located at oldIndex
*/
guint gtableCorrectPos (gtable* table, guint oldIndex)
{
	guint hash, capacity, newIndex, i;
	
	hash     = table->entries[oldIndex].hash;
	capacity = table->capacity;
	newIndex = gtableProbeSeq (hash, capacity, 0);
	
	for (i = 0; i < capacity && newIndex != oldIndex && table->entries[newIndex].name; i ++) {
		newIndex = gtableProbeSeq (hash, capacity, i);
	}
	
	return newIndex;
}

/*
	Lookup an entry in the table with its hash precalculated
*/
gbool gtableLookupHash (gtable* table, gstring* name, guint hash, guint* index)
{
	guint _index, capacity, i;
	
	if (index == 0) {
		index = &_index;
	}
	
	capacity = table->capacity;
	*index = gtableProbeSeq (hash, capacity, 0);
	
	for (i = 0; i < capacity; i ++) {
		if (table->entries[*index].hash == hash && gstringEqual (name, table->entries[*index].name)) {
			return gtrue;
		}
		
		*index = gtableProbeSeq (hash, capacity, i);
	}
	
	return gfalse;
}

/*
	Lookup an entry in the table
*/
gbool gtableLookup (gtable* table, gstring* name, guint* index)
{
	return gtableLookupHash (table, name, gstringHash (name), index);
}

/*
	Give the minimum needed capacity for a table with a specific usage and a current capacity
	curCapacity that can be achieved with the growth factor.
*/
guint gtableNeededCapacity (guint usage, guint curCapacity)
{
	guint expandCapacity, shrinkCapacity, maxUsage, minUsage;
	
	expandCapacity = curCapacity * GTABLE_GROWTH_FACTOR_N / GTABLE_GROWTH_FACTOR_D;
	shrinkCapacity = curCapacity * GTABLE_GROWTH_FACTOR_D / GTABLE_GROWTH_FACTOR_N;
	
	if (expandCapacity == curCapacity) expandCapacity ++;
	
	maxUsage = curCapacity * GTABLE_MAX_USAGE_N / GTABLE_MAX_USAGE_D;
	minUsage = shrinkCapacity * GTABLE_MAX_USAGE_N / GTABLE_MAX_USAGE_D;
	
	if (usage > maxUsage) {
		return gtableNeededCapacity (usage, expandCapacity);
	}
	else if (usage < minUsage) {
		return gtableNeededCapacity (usage, shrinkCapacity);
	}
	else {
		return MAX (GTABLE_MIN_CAPACITY, curCapacity);
	}
}

/*
	Probe a free position for a hash to be placed in the table
*/
gbool gtableFindFreePos (gtable* table, guint hash, guint* index)
{
	guint _index, i;
	
	if (index == 0) {
		index = &_index;
	}
	
	for (i = 0; i < table->capacity; i ++) {
		*index = gtableProbeSeq (hash, table->capacity, i);
		
		if (table->entries[*index].name == 0) {
			return gtrue;
		}
	}
	
	return gfalse;
}

void gtableDemo ()
{
	gtable* table;
	
	table = gtableNew ();
	
	gtableSetValue (table, gstringFromCstr ("null"), (void*)0);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("eins"), (void*)1);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("zwei"), (void*)2);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("drei"), (void*)3);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("vier"), (void*)4);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("fuenf"), (void*)5);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("sechs"), (void*)6);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("sieben"), (void*)7);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("acht"), (void*)8);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("neun"), (void*)9);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("zehn"), (void*)10);
	gtablePrintInfo (table);

	gtableSetValue (table, gstringFromCstr ("elf"), (void*)11);
	gtablePrintInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("zwoelf"), (void*)12);
	gtablePrintInfo (table);
}

void gtablePrintInfo (gtable* table)
{
	printf ("===================\n--- Abruf\n");
	
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("null"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("eins"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("zwei"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("drei"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("vier"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("fuenf"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("sechs"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("sieben"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("acht"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("neun"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("zehn"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("elf"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("zwoelf"))); printf(" ");
	printNl ();
	
	printf ("--- Hashtable (%lu/%lu)\n", table->usage, table->capacity);
	for (int i=0; i<table->capacity; i++) {
		printf("#%i : H = %lu ", i, table->entries[i].hash);
		
		gstring* key = (gstring*)table->entries[i].name;
		guint val = (guint)table->entries[i].value;
		if (key) {
			printf("K = "); gstringPrint (key);
			printf(" V = %lu", val);
		}
		printf("\n");
	}
	
	garray* keys = gtableGetKeys (table);
	
	printf ("\n--- Key-Array\n");
	for (int i=0; i<keys->usage; i++) {
		gstringPrint ((gstring*)keys->items[i]); printf(" ");
	}
	
	garray* vals = gtableGetValues (table);
	
	printf ("\n--- Value-Array\n");
	for (int i=0; i<vals->usage; i++) {
		printf("%lu ", (guint)vals->items[i]);
	}
	
	printNl ();
}

/* public */

gtable* gtableNew ()
{
	gtable* res;
	
	res = gnew (gtable, 1);
	gtableInit (res);
	
	return res;
}

void gtableInit (gtable* table)
{
	guint i;
	
	table->capacity = GTABLE_MIN_CAPACITY;
	table->usage    = 0;
	table->entries  = gnew (gentry, table->capacity);
	
	for (i = 0; i < table->capacity; i ++) {
		_initEntry (&table->entries[i]);
	}
}

void gtableSetValue (gtable* table, gstring* name, void* value)
{
	guint hash, index, neededCapacity;
	
	hash = gstringHash (name);
	
	if (gtableLookupHash (table, name, hash, &index) == gfalse) {
		neededCapacity = gtableNeededCapacity (table->usage + 1, table->capacity);
		
		if (neededCapacity != table->capacity) {
			_resize (table, neededCapacity);
		}
		
		gtableFindFreePos (table, hash, &index);
		table->usage ++;
	}
	
	_setEntry (&table->entries[index], hash, name, value);
}

void* gtableGetValue (gtable* table, gstring* name)
{
	guint hash, index;
	
	hash = gstringHash (name);
	
	if (gtableLookupHash (table, name, hash, &index)) {
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
