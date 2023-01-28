#include "../include/Utils.h"

uint32_t bit_size(uint32_t size) {
    size--;
    uint32_t i=0;
    for (; size > 0; size >>= 1, i++) {}
    return i;
}