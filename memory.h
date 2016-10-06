#pragma once

#include "types.h"

void* gmalloc (guint size);
void gfree (void* ptr);
void* grealloc (void* ptr, guint size);
