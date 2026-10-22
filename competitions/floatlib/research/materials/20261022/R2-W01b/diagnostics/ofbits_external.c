#include <stdint.h>
#include <string.h>
#include <math.h>

/* Separate translation unit; no link-time optimization.
   Mirrors v4.34.0 runtime object.cpp:1987-1993 on the recorded host. */
float external_of_bits(uint32_t u) {
    float x;
    memcpy(&x, &u, sizeof x);
    if (isnan(x)) {
        const uint32_t canonical = UINT32_C(0x7fc00000);
        memcpy(&x, &canonical, sizeof x);
    }
    return x;
}
