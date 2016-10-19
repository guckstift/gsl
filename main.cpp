#include <stdio.h>
#include "gtable.h"
#include "print.h"

void printTableInfo (gtable* table)
{
	printf ("===================\n--- Abruf\n");
	
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("null"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("eins"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("zwei"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("drei"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("vier"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("fuenf"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("sechs"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("sieben"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("acht"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("neun"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("zehn"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("elf"))); printf(" ");
	printUlDec((guint)gtableGetValue (table, gstringFromCstr ("zwoelf"))); printf(" ");
	printNl ();
	
	printf ("--- Hashtable (%lu/%lu)\n", table->usage, table->capacity);
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
	
	printf ("\n--- Key-Array\n");
	for (int i=0; i<keys->usage; i++) {
		gstringPrint ((gstring*)keys->items[i]); printf(" ");
	}
	
	garray* vals = gtableGetValues (table);
	
	printf ("\n--- Value-Array\n");
	for (int i=0; i<vals->usage; i++) {
		printf("%lu ", (guint)vals->items[i]);
	}
	
	printNl ();
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
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("eins"), (void*)1);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("zwei"), (void*)2);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("drei"), (void*)3);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("vier"), (void*)4);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("fuenf"), (void*)5);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("sechs"), (void*)6);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("sieben"), (void*)7);
	printTableInfo (table);
	
	gtableSetValue (table, gstringFromCstr ("acht"), (void*)8);
	printTableInfo (table);
	
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
