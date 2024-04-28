#pragma once
#include "stdint.hpp"

void __far* memcpy(void __far* dst, const void __far* src, uint16_t num);
void __far* memset(void __far* ptr, int value, uint16_t num);
int memcmp(const void __far* ptr1, const void __far* ptr2, uint16_t num);