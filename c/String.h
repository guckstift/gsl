#ifndef String_H
#define String_H

#include "basetypes.h"

typedef struct String {
	VarBase_HEAD
	guint hash;
	gchar chars[1];
} String;

extern Base StringType[1];

#define INVALID_HASH MAX_UINT

void StringInit(String* str, guint length);
String* StringNew(guint length);
String* StringFromCstr(char* cstr);
String* StringConcat (String* first, String* second);
String* StringAppend (String* first, String* second);
guint StringUpdateHash (String* src);
gbool StringEqual (String* first, String* second);
void StringPrint (String* src);

#define StringHash(ptr) \
	(!(ptr) ? INVALID_HASH : (ptr)->hash == INVALID_HASH ? StringUpdateHash(ptr) : (ptr)->hash)

#endif
