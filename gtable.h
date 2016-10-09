#pragma once

#include "types.h"
#include "gstring.h"

struct _gentry;

struct gtable {
	guint capacity;
	guint usage;
	_gentry* entries;
};

struct _gentry {
	guint hash;
	gstring* name;
	void* value;
};

gtable* gtableNew ();
void gtable(gtable* table, guint neededSize);
void gtableSetValue (gstring* name, void* value);
//void gtableSetValueHash (guint hash, void* value);
guint _probe (guint hash, guint mod, guint pos);
guint _adjustedSize (guint neededSize);

