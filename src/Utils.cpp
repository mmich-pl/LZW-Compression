#include "../include/Utils.h"

int bit_size(int size) {
    size--;
    int i;
    for (i = 0; size > 0; size >>= 1, i++) {}
    return i;
}