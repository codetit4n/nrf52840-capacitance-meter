#pragma once

#include <stddef.h>
#include <stdint.h>

void init_uarte0(void);
void uarte_write(const char* text, size_t len);
