#include "gstring.h"
#include "memory.h"

gstring* gstringNew (guint length)
{
	gstring* res;
	
	res = (gstring*)gmalloc (sizeof (gstring) + length * sizeof (gchar));
	res->length = length;
	return res;
}

gstring* gstringFromCstr (const char* cstr)
{
	guint i;
	gstring* res;
	
	for (i = 0; cstr[i]; i ++);
	
	res = gstringNew (i);
	
	for (i = 0; i < res->length; i ++)
		res->chars[i] = cstr[i];
	
	return res;
}

gstring* gstringConcat (gstring* first, gstring* second)
{
	guint i;
	gstring* res;
	
	res = gstringNew (first->length + second->length);
	
	for (i = 0; i < first->length; i ++)
		res->chars[i] = first->chars[i];

	for (i = 0; i < second->length; i ++)
		res->chars[first->length + i] = second->chars[i];
	
	return res;
}
