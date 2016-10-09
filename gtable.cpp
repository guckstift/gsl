#include "gtable.h"
#include "memory.h"
#include "math.h"

gtable* gtableNew ()
{
	gtable* res;
	guint i;
	
	res = GNEW (gtable);
	res->capacity = 4;
	res->usage = 0;
	res->entries = GNEWC (_gentry, res->capacity);
	
	for (i = 0; i < res->capacity; i ++) {
		res->entries[0].hash = 0;
		res->entries[0].name = 0;
		res->entries[0].value = 0;
	}
}

void gtable(gtable* table, guint neededSize)
{
	guint newCapacity;
	
	newCapacity = _adjustedSize (neededSize);
}

void gtableSetValue (gtable* table, gstring* name, void* value)
{
	guint hash, index, i;
	gbool found; 
	_gentry* entry;
	
	hash = gstringHash (name);
	
	for (i = 0, found = false; i < table->capacity && found == false; i ++) {
		index = probe (hash, table->capacity, i);
		entry = &table->entries[index];
		
		if (entry->hash == hash && gstringEqual (name, entry->name))
			found = true;
		
		if (table->entries[index].name == 0) {
			found = true;
		}
	}
	
	if (found) {
		table->entries[index].hash = hash;
		table->entries[index].name = name;
		table->entries[index].value = value;
	}
	else {
	}
}

void gtableSetValueHash (gtable* table, gstring* name, void* value, guint hash)
{
}

guint _probe (guint hash, guint mod, guint pos)
{
	return (hash + (pos + pos * pos	) / 2) % mod;
}

guint _adjustedSize (guint neededSize)
{
	guint capacity, threeFourth;
	
	capacity = nextPowerOf2 (neededSize);
	threeFourth = capacity * 3 / 4;
	
	if (neededSize >= threeFourth)
		capacity <<= 1;
	
	return capacity > 4 ? capacity : 4;
}

