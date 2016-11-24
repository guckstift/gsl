#include <stdlib.h>
#include <string.h>
#include "memory.h"

void* gmalloc(guint size)
{
	return calloc(size, 1);
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

gbool gmequal(void* first, void* second, guint size)
{
	return memcmp(first, second, size) == 0;
}
