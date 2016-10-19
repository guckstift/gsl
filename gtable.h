#pragma once

#include "types.h"
#include "gstring.h"
#include "garray.h"

#define GTABLE_MIN_CAPACITY    4
#define GTABLE_MAX_USAGE_N     3
#define GTABLE_MAX_USAGE_D     4
#define GTABLE_GROWTH_FACTOR_N 2
#define GTABLE_GROWTH_FACTOR_D 1

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
garray* gtableGetKeys (gtable* table);
garray* gtableGetValues (gtable* table);
guint _gtableProbeSeq (guint hash, guint capacity, guint pos);
guint _gtableCorrectPos (gtable* table, guint oldIndex);
gbool _gtableLookupHash (gtable* table, gstring* name, guint hash, guint* index);
gbool _gtableLookup (gtable* table, gstring* name, guint* index);
guint _gtableNeededCapacity (guint capacity, guint usage);
gbool _gtableFindFreePos (gtable* table, guint hash, guint* index);
