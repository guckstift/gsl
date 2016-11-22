#include <string.h>
#include <stdio.h>
#include "String.h"
#include "memory.h"

Base StringType[1];

static guint _cstrlen(char* cstr)
{
	return strlen(cstr);
}

void StringInit(String* str, guint length)
{
	str->refcount = 0;
	str->type = StringType;
	str->length = length;
	str->hash = INVALID_HASH;
}

String* StringNew(guint length)
{
	String* res;
	
	res = newvarobj(String, gchar, length);
	StringInit(res, length);
	
	return res;
}

String* StringFromCstr(char* cstr)
{
	guint i;
	String* res;

	i = _cstrlen(cstr);
	res = StringNew(i);
	gmcopy(res->chars, cstr, res->length);

	return res;
}

String* StringConcat (String* first, String* second)
{
	guint i;
	String* res;

	res = StringNew (first->length + second->length);
	gmcopy(res->chars, first->chars, first->length);
	gmcopy(&res->chars[first->length], second->chars, second->length);

	return res;
}

String* StringAppend (String* first, String* second)
{
	resizevarobj(first, String, gchar, first->length + second->length);
	gmcopy(&first->chars[first->length], second->chars, second->length);
	first->length = first->length + second->length;
	
	return first;
}

guint StringUpdateHash (String* src)
{
	guint i;

	for (src->hash = 0, i = 0; i < src->length; i ++)
		src->hash += src->chars[i] * (i + 1);
	
	if (src->hash == INVALID_HASH)
		src->hash = INVALID_HASH - 1;

	return src->hash;
}

gbool StringEqual (String* first, String* second)
{
	guint i;

	if (first->length != second->length)
		return gfalse;
	
	i = 0;
	
	if (sizeof(guint64) == 8) {
		for (; i + 7 < first->length; i += 8) {
			if (*(guint64*)&first->chars[i] != *(guint64*)&second->chars[i])
				return gfalse;
		}
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

void StringPrint (String* src)
{
	fwrite (src->chars, sizeof (gchar), src->length, stdout);
}
