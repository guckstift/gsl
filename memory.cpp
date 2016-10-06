#include <stdlib.h>
#include "memory.h"

void* gmalloc (guint size)
{
	return malloc (size);
}

void gfree (void* ptr)
{
	free (ptr);
}

void* grealloc (void* ptr, guint size)
{
	return realloc (ptr, size);
}
