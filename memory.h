#pragma once

#include "types.h"

void* gmalloc (guint size);
void gfree (void* ptr);
void* grealloc (void* ptr, guint size);

#define gnew(T,C) ((T*)gmalloc ((C) * sizeof (T)))
#define gresize(P,T,C) ((P) = (T*)grealloc ((P), (C) * sizeof (T)))
