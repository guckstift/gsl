#include <stdio.h>
#include "gtable.h"
#include "print.h"

int main (int argc, char** argv)
{
	gtable* table;
	gstring* stringVarName;
	gstring* stringVarValue;
	gstring* stringRes;
	gstring* intVarName;
	gint intRes;
	
	table = gtableNew ();
	
	stringVarName = gstringFromCstr ("stringVar");
	stringVarValue = gstringFromCstr ("value");
	gtableSetValue (table, stringVarName, stringVarValue);
	stringRes = (gstring*)gtableGetValue (table, stringVarName);
	
	gstringPrint (stringRes); printNl ();
	
	intVarName = gstringFromCstr ("intVar");
	gtableSetValue (table, intVarName, (void*)+666);
	intRes = (gint)gtableGetValue (table, intVarName);
	
	printSlDec (intRes); printNl ();
	
	return 0;
}
