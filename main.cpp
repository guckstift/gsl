#include <stdio.h>
#include "gtable.h"
#include "print.h"

void printTableInfo (gtable* table)
{
	printf ("Abruf\n");
	
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
	
	printf ("Hashtable (%lu/%lu)\n", table->usage, table->capacity);
	for (int i=0; i<table->capacity; i++) {
		printf("#%i : H = %lu ", i, table->entries[i].hash);
		
		gstring* key = (gstring*)table->entries[i].name;
		guint val = (guint)table->entries[i].value;
		if (key) {
			printf("K = "); gstringPrint (key);
			printf(" V = %lu", val);
		}
		printf("\n");
	}
	
	garray* keys = gtableGetKeys (table);
	
	printf ("Key-Array\n");
	for (int i=0; i<keys->usage; i++) {
		gstringPrint ((gstring*)keys->items[i]); printNl();
	}
	
	garray* vals = gtableGetValues (table);
	
	printf ("Value-Array\n");
	for (int i=0; i<vals->usage; i++) {
		printf("%lu\n", (guint)vals->items[i]);
	}
}

int main (int argc, char** argv)
{
	/*
	return 0;
	
	int cap = 0;
	for (int i=0; i<256; i++) {
		cap = _gtableNeededCapacity (i, 6);
		printUlDec(i); printf(" "); printUlDec (cap); printNl ();
	}
	return 0;
	*/
	
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
	
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("zehn"), (void*)10);
	printTableInfo (table);

	gtableSetValue (table, gstringFromCstr ("elf"), (void*)11);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("zwoelf"), (void*)12);
	printTableInfo (table);

	
	return 0;
}
