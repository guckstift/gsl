#pragma once

#include "types.h"

struct gstring {
	guint length;
	gchar chars[0];
};

gstring* gstringNew (guint length);
gstring* gstringFromCstr (const char* cstr);
gstring* gstringConcat (gstring* first, gstring* second);
guint gstringHash (gstring* src);
gbool gstringEqual (gstring* first, gstring* second);
