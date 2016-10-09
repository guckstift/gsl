#pragma once

#include "types.h"

void* gmalloc (guint size);
void gfree (void* ptr);
void* grealloc (void* ptr, guint size);

#define GNEW(T) ((T*)gmalloc (sizeof (T)))
#define GNEWC(T,C) ((T*)gmalloc ((C) * sizeof (T)))
