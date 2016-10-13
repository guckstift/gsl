#include <stdio.h>
#include "gtable.h"
#include "print.h"

int main (int argc, char** argv)
{
	gtable* table;
	
	table = gtableNew ();
	gtableSetValue (table, gstringFromCstr ("null"), (void*)0);
	gtableSetValue (table, gstringFromCstr ("eins"), (void*)1);
	gtableSetValue (table, gstringFromCstr ("zwei"), (void*)2);
	gtableSetValue (table, gstringFromCstr ("drei"), (void*)3);
	gtableSetValue (table, gstringFromCstr ("vier"), (void*)4);
	gtableSetValue (table, gstringFromCstr ("fuenf"), (void*)5);
	gtableSetValue (table, gstringFromCstr ("sechs"), (void*)6);
	gtableSetValue (table, gstringFromCstr ("sieben"), (void*)7);
	gtableSetValue (table, gstringFromCstr ("acht"), (void*)8);
	gtableSetValue (table, gstringFromCstr ("neun"), (void*)9);
	
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("null"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("eins"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("zwei"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("drei"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("vier"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("fuenf"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("sechs"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("sieben"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("acht"))); printNl ();
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("neun"))); printNl ();
	
	return 0;
}
