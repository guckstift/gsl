#pragma once

#include "types.h"
#include "gstring.h"

struct gentry {
	guint hash;
	gstring* name;
	void* value;
};

struct gtable {
	guint capacity;
	guint usage;
	gentry* entries;
};

gtable* gtableNew ();
void gtableSetValue (gtable* table, gstring* name, void* value);
void* gtableGetValue (gtable* table, gstring* name);
guint _probeSeq (guint hash, guint capacity, guint pos);
guint _correctPos (gtable* table, guint oldIndex);
gbool _lookupHash (gtable* table, gstring* name, guint hash, guint* index);
gbool _lookup (gtable* table, gstring* name, guint* index);
guint _neededCapacity (guint usage);
gbool _findFreePos (gtable* table, guint hash, guint* index);
