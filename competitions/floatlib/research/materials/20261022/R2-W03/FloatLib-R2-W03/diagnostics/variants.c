/* Independent C surrogates. No reassociation, no FMA, no data preconversion. */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
extern float runtime_of_bits(uint32_t);
/* This boxed approximation models two dependent loads, NOT complete Lean RC. */
typedef struct { uintptr_t header; float value; } Box;
static float flat[512];
static Box values[512];
static Box *boxed[512];
void init_tables(void) {
  for (unsigned i=0;i<512;i++) {
    unsigned e=i&255u;
    uint32_t b=(i&256u)<<23;
    if (e>=24 && e<=254) b|=(e-23u)<<23;
    flat[i]=runtime_of_bits(b);
    values[i].header=0; values[i].value=flat[i]; boxed[i]=&values[i];
  }
}
float call_conv(uint32_t u) { return runtime_of_bits(u); }
float zero_conv(uint32_t u) { return u==0 ? 0.0f : runtime_of_bits(u); }
float flat_conv(uint32_t u) {
  if (u==0) return 0.0f;
  uint32_t e=(u>>23)&255u;
  if (e<24 || e>254) return runtime_of_bits(u);
  uint32_t m=(u&0x7fffffu)|0x800000u;
  return (float)m*flat[u>>23];
}
float boxed_conv(uint32_t u) {
  if (u==0) return 0.0f;
  uint32_t e=(u>>23)&255u;
  if (e<24 || e>254) return runtime_of_bits(u);
  uint32_t m=(u&0x7fffffu)|0x800000u;
  return (float)m*boxed[u>>23]->value;
}
float dense_conv(uint32_t u) {
  if (u==0) return 0.0f;
  uint32_t e=(u>>23)&255u;
  if (e<124 || e>130) return runtime_of_bits(u);
  uint32_t m=(u&0x7fffffu)|0x800000u;
  uint32_t n=m<<(e-124);
  float y=(float)n*0x1p-26f;
  return (u>>31) ? -y : y;
}
float dense_signed_conv(uint32_t u) {
  if (u==0) return 0.0f;
  uint32_t e=(u>>23)&255u;
  if (e<124 || e>130) return runtime_of_bits(u);
  uint32_t m=(u&0x7fffffu)|0x800000u;
  uint32_t n=m<<(e-124);
  uint32_t mask=0u-(u>>31);
  int32_t sn=(int32_t)((n^mask)-mask);
  return (float)sn*0x1p-26f;
}
float wide64_conv(uint32_t u) {
  if (u==0) return 0.0f;
  uint32_t e=(u>>23)&255u;
  if (e<102 || e>151) return runtime_of_bits(u);
  uint64_t m=(u&0x7fffffu)|0x800000u;
  uint32_t r=e<=133 ? e-102 : e-134;
  float scale=e<=133 ? 0x1p-48f : 0x1p-16f;
  uint64_t n=m<<r;
  float y=(float)n*scale;
  return (u>>31) ? -y : y;
}
float wide64_signed_conv(uint32_t u) {
  if (u==0) return 0.0f;
  uint32_t e=(u>>23)&255u;
  if (e<102 || e>151) return runtime_of_bits(u);
  uint64_t m=(u&0x7fffffu)|0x800000u;
  uint32_t r=e<=133 ? e-102 : e-134;
  float scale=e<=133 ? 0x1p-48f : 0x1p-16f;
  uint64_t n=m<<r;
  uint64_t mask=0ull-(u>>31);
  int64_t sn=(int64_t)((n^mask)-mask);
  return (float)sn*scale;
}
#define SUM(NAME) float sum_##NAME(const uint32_t *a, size_t n) { float s=0.0f; for(size_t i=0;i<n;i++) { float x=NAME##_conv(a[i]); s=s+x; } return s; }
SUM(call) SUM(zero) SUM(flat) SUM(boxed) SUM(dense) SUM(dense_signed) SUM(wide64) SUM(wide64_signed)
