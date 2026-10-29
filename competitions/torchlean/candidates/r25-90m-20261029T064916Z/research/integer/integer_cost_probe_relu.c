/* R25 original algorithm cost discriminator, NOT Lean-generated code.
 * Build only on a public Linux runner, never the user's local machine:
 *   python3 prepare_cost_probe.py
 *   cc -O3 -march=native -std=gnu11 integer_cost_probe_relu.c -o integer_cost_probe_relu
 *   ./integer_cost_probe_relu 128 11
 * Record compiler/CPU/flags and source/header SHA with stdout; preserve assembly.
 * Cases: public typical seed42 normal/sparse MLP first layer 608 -> 80.
 * Both boundaries include output allocation, 80 complete once-rounded biased
 * dots, finite-word ReLU and release. 'full' additionally prepares and releases aligned arrays.
 * Validation/hash stays outside timing. The three algorithms share all setup
 * and terminal code. Wide/special handling is NOT timed or implemented here.
 */
#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "integer_cost_fixture.h"

typedef unsigned __int128 u128;
typedef __int128 i128;
typedef struct {
  uint64_t *x, *w;
  i128 bias[OUTPUT_N];
  int exponent[OUTPUT_N];
} Prepared;
static uint64_t fallback_count;
static volatile uint32_t sink;

static unsigned exp32(uint32_t w) { return (w >> 23) & 255u; }
static unsigned idx32(uint32_t w) { unsigned e=exp32(w); return e ? e-1 : 0; }
static uint64_t mant32(uint32_t w) { return (w & 0x7fffffu) | (exp32(w) ? 0x800000u : 0); }

static int align_vector(const uint32_t *raw, unsigned n, uint64_t *out,
                        unsigned *low, unsigned *span) {
  unsigned lo=254,hi=0,active=0;
  for (unsigned i=0;i<n;i++) {
    if (exp32(raw[i])==255) return 0;
    if (mant32(raw[i])) {
      unsigned e=idx32(raw[i]); if(e<lo)lo=e;if(e>hi)hi=e;active=1;
    }
  }
  if(!active)lo=hi=0;
  *low=lo;*span=hi-lo;
  if(*span>15)return 0;
  for(unsigned i=0;i<n;i++) {
    uint64_t m=mant32(raw[i]);
    uint64_t v=m ? m << (idx32(raw[i])-lo) : 0;
    out[i]=(raw[i]>>31) ? 0-v : v;
  }
  return 1;
}

static void release_prepared(Prepared *p) { free(p->x);free(p->w);p->x=p->w=NULL; }

static int prepare(unsigned c,Prepared *p) {
  p->x=malloc(INPUT_N*sizeof(uint64_t));p->w=malloc(INPUT_N*OUTPUT_N*sizeof(uint64_t));
  if(!p->x||!p->w){release_prepared(p);return 0;}
  unsigned lx,sx;
  if(!align_vector(inputs[c],INPUT_N,p->x,&lx,&sx)){release_prepared(p);return 0;}
  for(unsigned j=0;j<OUTPUT_N;j++) {
    unsigned ly,sy;
    if(!align_vector(weights[c]+j*INPUT_N,INPUT_N,p->w+j*INPUT_N,&ly,&sy)
       || 48+sx+sy>59) { release_prepared(p);return 0; }
    unsigned base=lx+ly;uint32_t bw=biases[c][j];
    int shift=(int)idx32(bw)+149-(int)base;
    if(exp32(bw)==255 || shift<0 || shift>102){release_prepared(p);return 0;}
    u128 bm=(u128)mant32(bw)<<shift;
    if(bm>=((u128)1<<126)){release_prepared(p);return 0;}
    p->bias[j]=(bw>>31) ? -(i128)bm : (i128)bm;
    p->exponent[j]=(int)base-298;
  }
  return 1;
}

static i128 signed128(u128 u) { return (u>>127) ? -((i128)(~u))-1 : (i128)u; }
static i128 signed64(uint64_t u) { return (u>>63) ? -(i128)(0-u) : (i128)u; }

__attribute__((noinline)) static i128 carry2(const uint64_t *a,const uint64_t *b,unsigned n) {
  uint64_t al=0,ah=0,bl=0,bh=0;
  for(unsigned i=0;i<n;i++) {
    uint64_t q=a[i]*b[i],lo=al+q;
    uint64_t hi=ah-(q>>63)+(lo<al);
    al=bl;ah=bh;bl=lo;bh=hi;
  }
  uint64_t lo=al+bl,hi=ah+bh+(lo<al);
  return signed128(((u128)hi<<64)|lo);
}

__attribute__((noinline)) static i128 block16(const uint64_t *a,const uint64_t *b,unsigned n) {
  u128 total=0;
  for(unsigned start=0;start<n;start+=16) {
    unsigned end=start+16<n ? start+16 : n;
    uint64_t s0=0,s1=0;unsigned i=start;
    for(;i+1<end;i+=2){s0+=a[i]*b[i];s1+=a[i+1]*b[i+1];}
    if(i<end)s0+=a[i]*b[i];
    total+=(u128)signed64(s0+s1);
  }
  return signed128(total);
}

__attribute__((noinline)) static i128 checked_buckets(const uint64_t *a,const uint64_t *b,unsigned n) {
  uint64_t pos=0,neg=0;
  for(unsigned i=0;i<n;i++) {
    uint64_t q=a[i]*b[i];
    if(q>>63) {
      uint64_t next=neg+(0-q);
      if(next<neg){fallback_count++;return carry2(a,b,n);}neg=next;
    } else {
      uint64_t next=pos+q;
      if(next<pos){fallback_count++;return carry2(a,b,n);}pos=next;
    }
  }
  return (i128)pos-(i128)neg;
}

static uint32_t round32(i128 value,int exponent) {
  if(!value)return 0;
  uint32_t sign=value<0 ? 0x80000000u : 0;
  u128 m=value<0 ? (u128)(-value) : (u128)value;
  uint64_t hi=(uint64_t)(m>>64),lo=(uint64_t)m;
  int log=hi ? 127-__builtin_clzll(hi) : 63-__builtin_clzll(lo);
  int shift=log-23;
  if(-149-exponent>shift)shift=-149-exponent;
  int unit=exponent+shift;u128 q;
  if(shift>=128)q=0;
  else if(shift>0) {
    q=m>>shift;u128 rem=m&(((u128)1<<shift)-1),half=(u128)1<<(shift-1);
    if(rem>half || (rem==half && (q&1)))q++;
  } else q=m<<(-shift);
  if(!q)return sign;
  if(q==((u128)1<<24)){q>>=1;unit++;}
  if(unit==-149 && q<((u128)1<<23))return sign|(uint32_t)q;
  int field=unit+150;
  if(field>=255)return sign|0x7f800000u;
  if(field<=0 || q<((u128)1<<23) || q>=((u128)1<<24))abort();
  return sign|((uint32_t)field<<23)|((uint32_t)q-0x800000u);
}

typedef i128 (*Algo)(const uint64_t *,const uint64_t *,unsigned);
static Algo algorithms[3]={carry2,block16,checked_buckets};
static const char *names[3]={"two_chain128","block16","checked_buckets"};

__attribute__((noinline)) static int execute(unsigned c,unsigned alg,int full,
                                            const Prepared *cached,int check) {
  Prepared owned;const Prepared *p=cached;
  if(full){if(!prepare(c,&owned))return 0;p=&owned;}
  uint32_t *out=malloc(OUTPUT_N*sizeof(uint32_t));if(!out)abort();
  for(unsigned j=0;j<OUTPUT_N;j++) {
    uint32_t word=round32(algorithms[alg](p->x,p->w+j*INPUT_N,INPUT_N)+p->bias[j],p->exponent[j]);
    out[j]=(word>>31) ? 0 : word; /* Contract act true on this guarded finite fixture. */
  }
  int ok=1;
  if(check)for(unsigned j=0;j<OUTPUT_N;j++) {
    uint32_t expected=(expecteds[c][j]>>31) ? 0 : expecteds[c][j];
    if(out[j]!=expected) {
      fprintf(stderr,"mismatch case=%u alg=%u output=%u got=%08x expected=%08x\n",
              c,alg,j,out[j],expected);ok=0;
    }
  }
  __asm__ __volatile__("" : : "r"(out) : "memory");
  sink^=out[OUTPUT_N-1];free(out);if(full)release_prepared(&owned);return ok;
}

static uint64_t now_ns(void) { struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return (uint64_t)t.tv_sec*1000000000ull+t.tv_nsec; }

static int boundaries(void) {
  struct { i128 value;int e;uint32_t word; } rs[]={
    {1,0,0x3f800000u},{-1,0,0xbf800000u},{1,-149,1u},{1,-150,0u},
    {3,-150,2u},{16777217,-24,0x3f800000u},{16777219,-24,0x3f800002u}};
  for(unsigned k=0;k<sizeof(rs)/sizeof(rs[0]);k++)if(round32(rs[k].value,rs[k].e)!=rs[k].word)return 0;
  uint64_t a[65],b[65];
  for(unsigned i=0;i<65;i++){a[i]=(i&1)?0-123456789ull:123456789ull;b[i]=7654321ull;}
  for(unsigned n=0;n<=65;n++) {
    i128 reference=0;for(unsigned i=0;i<n;i++)reference+=signed64(a[i]*b[i]);
    if(carry2(a,b,n)!=reference||block16(a,b,n)!=reference||checked_buckets(a,b,n)!=reference)return 0;
  }
  /* Force a positive bucket overflow despite a small final signed result.
   * Every term still satisfies the same strict 59-bit block16 bound. */
  i128 reference=0;
  for(unsigned i=0;i<65;i++) {
    a[i]=0xffffffull;b[i]=0xffffffull<<11;
    if(i>=33)b[i]=0-b[i];
    reference+=signed64(a[i]*b[i]);
  }
  uint64_t before=fallback_count;
  if(carry2(a,b,65)!=reference||block16(a,b,65)!=reference
     ||checked_buckets(a,b,65)!=reference||fallback_count!=before+1)return 0;
  return 1;
}

int main(int argc,char **argv) {
  unsigned reps=argc>1?(unsigned)strtoul(argv[1],NULL,10):128;
  unsigned rounds=argc>2?(unsigned)strtoul(argv[2],NULL,10):11;
  if(!reps||reps>4096||!rounds||rounds>31||!boundaries())return 2;
  printf("case,boundary,round,order,algorithm,reps,total_ns,ns_per_call,fallbacks\n");
  for(unsigned c=0;c<DATA_CASES;c++) {
    Prepared cached;if(!prepare(c,&cached))return 3;
    for(int full=0;full<=1;full++) {
      for(unsigned alg=0;alg<3;alg++)if(!execute(c,alg,full,&cached,1))return 4;
      for(unsigned round=0;round<rounds;round++)for(unsigned order=0;order<3;order++) {
        unsigned alg=(round+order+c)%3;fallback_count=0;
        uint64_t t0=now_ns();
        for(unsigned rep=0;rep<reps;rep++)if(!execute(c,alg,full,&cached,0))return 5;
        uint64_t elapsed=now_ns()-t0;
        printf("%s,%s,%u,%u,%s,%u,%"PRIu64",%.3f,%"PRIu64"\n",
          case_names[c],full?"with_prepare":"prepared",round,order,names[alg],reps,
          elapsed,(double)elapsed/reps,fallback_count);
      }
    }
    release_prepared(&cached);
  }
  return 0;
}
