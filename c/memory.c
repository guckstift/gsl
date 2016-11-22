#include <stdlib.h>
#include <string.h>
#include "memory.h"

void* gmalloc(guint size)
{
	return malloc(size);
}

void gfree(void* ptr)
{
	free(ptr);
}

void* grealloc(void* ptr, guint size)
{
	return realloc(ptr, size);
}

void gmcopy(void* dest, void* src, guint size)
{
	memcpy(dest, src, size);
}
