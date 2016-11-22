#ifndef memory_H
#define memory_H

#include "basetypes.h"

void* gmalloc(guint size);
void gfree(void* ptr);
void* grealloc(void* ptr, guint size);

#define newobj(type) \
	((type*)gmalloc(sizeof(type)))
#define varobjsize(type, elmtype, count) \
	(sizeof(type) + sizeof(elmtype) * ((count) - 1))
#define newvarobj(type, elmtype, count) \
	((type*)gmalloc(varobjsize(type, elmtype, (count))))
#define resizevarobj(ptr, type, elmtype, count) \
	((ptr) = (type*)grealloc((ptr), varobjsize(type, elmtype, (count))))
#define newvec(type, count) \
	((type*)gmalloc(sizeof(type) * (count)))
#define resizevec(ptr, type, count) \
	((ptr) = (type*)grealloc((ptr), sizeof(type) * (count)))

void gmcopy(void* dest, void* src, guint size);

#endif
