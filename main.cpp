#include <stdio.h>
#include "types.h"
#include "gstring.h"
#include "gtable.h"
#include "math.h"

gstring a;

int main (int argc, char** argv)
{
	gstring b;
	gstring *hello;
	
	/*
	printf("%lu\n", sizeof (a));
	printf("%lu\n", sizeof (b));
	printf("%lu\n", sizeof (gstring));
	printf("%i\n", a.chars[0]);
	printf("%i\n", b.chars[0]);
	*/
	
	hello = gstringFromCstr ("0");
	printf("Hash: %lu\n", gstringHash (hello));
	hello = gstringFromCstr ("z");
	printf("Hash: %lu\n", gstringHash (hello));
	hello = gstringFromCstr ("zz");
	printf("Hash: %lu\n", gstringHash (hello));
	hello = gstringFromCstr ("zzz");
	printf("Hash: %lu\n", gstringHash (hello));
	
	//printf("%lu\n", hello->length);
	//printf("%c\n", hello->chars[11]);
	
	return 0;
}
