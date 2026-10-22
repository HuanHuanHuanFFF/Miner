/* Public-semantics surrogate only; NOT Lean runtime, NOT official gate. */
#include <stdint.h>
#include <string.h>
#include <math.h>
float runtime_of_bits(uint32_t u) {
  float x; memcpy(&x,&u,4);
  if (isnan(x)) return NAN;
  return x;
}
