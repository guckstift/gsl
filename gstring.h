#pragma once

#include "types.h"

struct gstring {
	guint length;
	gchar chars[0];
};

gstring* gstringNew (guint length);
gstring* gstringFromCstr (const char* cstr);
gstring* gstringConcat (gstring* first, gstring* second);
