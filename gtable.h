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
guint _gtableProbeSeq (guint hash, guint capacity, guint pos);
guint _gtableCorrectPos (gtable* table, guint oldIndex);
gbool _gtableLookupHash (gtable* table, gstring* name, guint hash, guint* index);
gbool _gtableLookup (gtable* table, gstring* name, guint* index);
guint _gtableNeededCapacity (guint usage);
gbool _gtableFindFreePos (gtable* table, guint hash, guint* index);
