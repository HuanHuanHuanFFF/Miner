#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fenv.h>
#include <float.h>
#if defined(__x86_64__) || defined(__i386__)
#include <xmmintrin.h>
#endif
void init_tables(void);
#define DECL(N) float N##_conv(uint32_t); float sum_##N(const uint32_t*,size_t);
DECL(call) DECL(zero) DECL(flat) DECL(boxed) DECL(dense) DECL(dense_signed) DECL(wide64) DECL(wide64_signed)
typedef float (*convfn)(uint32_t); typedef float (*sumfn)(const uint32_t*,size_t);
const char *names[]={"call","zero","flat","boxed","dense","dense_signed","wide64","wide64_signed"};
convfn cv[]={call_conv,zero_conv,flat_conv,boxed_conv,dense_conv,dense_signed_conv,wide64_conv,wide64_signed_conv};
sumfn sf[]={sum_call,sum_zero,sum_flat,sum_boxed,sum_dense,sum_dense_signed,sum_wide64,sum_wide64_signed};
static uint32_t bits(float x){uint32_t u;memcpy(&u,&x,4);return u;}
static uint64_t random_state;
static uint32_t next(void){random_state^=random_state>>12;random_state^=random_state<<25;random_state^=random_state>>27;return (uint32_t)((random_state*2685821657736338717ull)>>32);}
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec*1e-9;}
static int cmp(const void *a,const void *b){double x=*(const double*)a,y=*(const double*)b;return (x>y)-(x<y);}
static volatile uint32_t sink;
int main(int argc, char **argv){
 printf("FLOAT_ENV bytes=%zu radix=%d mant=%d min_exp=%d max_exp=%d eval_method=%d rounding=%d\n",sizeof(float),FLT_RADIX,FLT_MANT_DIG,FLT_MIN_EXP,FLT_MAX_EXP,FLT_EVAL_METHOD,fegetround());
 if (sizeof(float)!=4 || FLT_RADIX!=2 || FLT_MANT_DIG!=24 || FLT_MIN_EXP!=-125 || FLT_MAX_EXP!=128 || FLT_EVAL_METHOD!=0 || fegetround()!=FE_TONEAREST){fputs("invalid host float contract\n",stderr);return 2;}
#if defined(__x86_64__) || defined(__i386__)
 unsigned mxcsr=_mm_getcsr();
 printf("MXCSR 0x%08x FTZ=%u DAZ=%u\n",mxcsr,(mxcsr>>15)&1u,(mxcsr>>6)&1u);
 if (mxcsr&((1u<<15)|(1u<<6))){fputs("FTZ/DAZ enabled; refuse comparison without changing environment\n",stderr);return 2;}
#else
 fputs("Non-x86 FTZ/DAZ check NOT_RUN; no host results certified\n",stderr);return 2;
#endif
 struct timespec seed_time; clock_gettime(CLOCK_REALTIME,&seed_time);
 random_state=argc>1?strtoull(argv[1],0,0):(((uint64_t)seed_time.tv_sec<<32)^(uint64_t)seed_time.tv_nsec);
 if(random_state==0)random_state=1;
 printf("SYNTHETIC_SEED 0x%016llx (only test data; candidate independent)\n",(unsigned long long)random_state);
 uint32_t first[1000];
 for(unsigned i=0;i<1000;i++)first[i]=(next()&0x807fffffu)|((124u+next()%7u)<<23);
 double t0=now();sink=bits(sum_call(first,1000));double first_call_ns=(now()-t0)*1e9;
 t0=now();init_tables();double init_ns=(now()-t0)*1e9;
 sink=bits(sum_boxed(first,1000)); double setup_first_sum_ns=(now()-t0)*1e9;
 printf("FIRST_SAMPLE baseline_1000_ns=%.0f table_static_init_ns=%.0f init_plus_boxed_1000_ns=%.0f\n",first_call_ns,init_ns,setup_first_sum_ns);
 uint32_t special[]={0,0x80000000,1,0x80000001,0x007fffff,0x807fffff,0x00800000,0x80800000,0x0bffffff,0x0c000000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc00001,0x7f800001,0xffc12345,0xff800001};
 unsigned long long checks=0;
 for(unsigned v=0;v<8;v++){
  for(unsigned j=0;j<sizeof(special)/sizeof(*special);j++){uint32_t u=special[j];if(bits(cv[v](u))!=bits(call_conv(u))){printf("FAIL special %s %08x\n",names[v],u);return 1;}checks++;}
 }
 for(unsigned e=0;e<256;e++) for(unsigned k=0;k<2048;k++){
  uint32_t u=(next()&0x807fffffu)|(e<<23);
  uint32_t expected=bits(call_conv(u));
  for(unsigned v=0;v<8;v++){if(bits(cv[v](u))!=expected){printf("FAIL random %s %08x\n",names[v],u);return 1;} checks++;}
 }
 printf("CONVERSION_CHECKS %llu PASS (native canonical-NaN semantics only)\n",checks);
 const char *domains[]={"dense","relu","wide","raw"};
 uint32_t a[1000];
 for(unsigned d=0;d<4;d++){
  for(unsigned i=0;i<1000;i++){
   uint32_t r=next(); unsigned e=(d==0||d==1)?124u+next()%7u:102u+next()%50u;
   a[i]=d==3?r:((r&0x807fffffu)|(e<<23));
   if(d==1)a[i]=(r&1u)?0:(a[i]&0x7fffffffu);
  }
  uint32_t expected=bits(sum_call(a,1000));
  for(unsigned v=0;v<8;v++)if(bits(sf[v](a,1000))!=expected){printf("FAIL sum %s %s\n",domains[d],names[v]);return 1;}
  printf("DOMAIN %s SUM %08x\n",domains[d],expected);
  enum{REPS=11,LOOPS=4000}; double times[8][REPS];
  for(unsigned rep=0;rep<REPS;rep++)for(unsigned vi=0;vi<8;vi++){
   unsigned v=(vi+rep)%8; double start=now();
   for(unsigned j=0;j<LOOPS;j++) sink=bits(sf[v](a,1000));
   times[v][rep]=(now()-start)*1e9/(LOOPS*1000.0);
  }
  for(unsigned v=0;v<8;v++){qsort(times[v],REPS,sizeof(double),cmp);printf("TIME %s %s ns_per_item min=%.4f median=%.4f max=%.4f\n",domains[d],names[v],times[v][0],times[v][REPS/2],times[v][REPS-1]);}
 }
 /* Resolve the concrete repeated-single-vector branch/cache risk with 64
    different raw-bit vectors. No input conversion buffer is constructed. */
 enum{POOL=64,WIDTH=1000,PREPS=5,PLOOPS=128};
 const unsigned pvariants[]={0,1,3,5,6};
 unsigned pool_checks=0;
 for(unsigned d=0;d<3;d++){
  double prepare_start=now();
  uint32_t *pool=malloc(POOL*WIDTH*sizeof(uint32_t));
  if(!pool){fputs("pool allocation failed\n",stderr);return 2;}
  for(unsigned i=0;i<POOL*WIDTH;i++){
   uint32_t r=next(); unsigned e=(d==0||d==1)?124u+next()%7u:102u+next()%50u;
   pool[i]=(r&0x807fffffu)|(e<<23);
   if(d==1)pool[i]=(r&1u)?0:(pool[i]&0x7fffffffu);
  }
  printf("POOL_INPUT_SETUP %s count=%u bytes=%zu ns=%.0f\n",domains[d],POOL,POOL*WIDTH*sizeof(uint32_t),(now()-prepare_start)*1e9);
  uint32_t expected_checksum=0;
  for(unsigned j=0;j<POOL;j++){
   uint32_t expected=bits(sum_call(pool+j*WIDTH,WIDTH));
   expected_checksum^=expected+j*0x9e3779b9u;
   for(unsigned vi=0;vi<5;vi++){
    unsigned v=pvariants[vi];
    if(bits(sf[v](pool+j*WIDTH,WIDTH))!=expected){printf("FAIL pool %s %s vec=%u\n",domains[d],names[v],j);free(pool);return 1;}
    pool_checks++;
   }
  }
  printf("POOL_CHECKSUM %s %08x\n",domains[d],expected_checksum);
  double times[5][PREPS];
  for(unsigned rep=0;rep<PREPS;rep++)for(unsigned order=0;order<5;order++){
   unsigned vi=(order+rep)%5,v=pvariants[vi];double start=now();
   for(unsigned k=0;k<PLOOPS;k++){
    uint32_t checksum=0;
    for(unsigned j=0;j<POOL;j++)checksum^=bits(sf[v](pool+j*WIDTH,WIDTH))+j*0x9e3779b9u;
    sink=checksum;
   }
   times[vi][rep]=(now()-start)*1e9/(PLOOPS*(double)POOL*WIDTH);
  }
  for(unsigned vi=0;vi<5;vi++){
   qsort(times[vi],PREPS,sizeof(double),cmp);
   printf("POOL_TIME %s %s ns_per_item min=%.4f median=%.4f max=%.4f\n",domains[d],names[pvariants[vi]],times[vi][0],times[vi][PREPS/2],times[vi][PREPS-1]);
  }
  free(pool);
 }
 printf("POOL_VALIDATIONS %u PASS\n",pool_checks);
 printf("SINK %08x\n",sink);
 return 0;
}
