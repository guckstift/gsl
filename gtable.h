#pragma once

#include "types.h"
#include "gstring.h"

struct gtable {
	guint capacity;
	guint usage;
	gentry* entries;
};

struct gentry {
	guint hash;
	gstring* name;
};

gtable* gtableNew ();
