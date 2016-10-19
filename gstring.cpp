#include <stdio.h>
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

guint gstringHash (gstring* src)
{
	guint res, i;

	for (res = 0, i = 0; i < src->length; i ++)
		res += src->chars[i] * (i + 1);

	return res;
}

gbool gstringEqual (gstring* first, gstring* second)
{
	guint i;

	if (first->length != second->length)
		return gfalse;
	
	for (i = 0; i + 7 < first->length; i += 8) {
		if (*(guint*)&first->chars[i] != *(guint*)&second->chars[i])
			return gfalse;
	}

	for (; i + 3 < first->length; i += 4) {
		if (*(guint32*)&first->chars[i] != *(guint32*)&second->chars[i])
			return gfalse;
	}

	for (; i + 1 < first->length; i += 2) {
		if (*(guint16*)&first->chars[i] != *(guint16*)&second->chars[i])
			return gfalse;
	}

	for (; i < first->length; i ++) {
		if (first->chars[i] != second->chars[i])
			return gfalse;
	}

	return gtrue;
}

void gstringPrint (gstring* src)
{
	fwrite (src->chars, sizeof (gchar), src->length, stdout);
}
