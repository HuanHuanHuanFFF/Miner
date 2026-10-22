/* R2-W01 CPU surrogate only. NOT Lean, NOT the official benchmark, NOT a submission.
 * This measures one complete guarded odd-mantissa block implementation, including
 * failed-block replay, against an ordered native float loop on fresh synthetic data.
 * C float reference has no asserted FloatLib NaN payload equivalence.
 */
#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { N=1000, V=100, BLOCK=32 };
static volatile uint32_t sink;
static uint64_t state = UINT64_C(0x29098a849141d67b);
static uint32_t rng32(void) {
    state ^= state >> 12; state ^= state << 25; state ^= state >> 27;
    return (uint32_t)((state * UINT64_C(2685821657736338717)) >> 32);
}
static float from_bits(uint32_t w) { float f; memcpy(&f,&w,4); return f; }
static uint32_t to_bits(float f) { uint32_t w; memcpy(&w,&f,4); return w; }

__attribute__((noinline))
static uint32_t ordered(const uint32_t *a) {
    float s=0.0f;
    for(unsigned i=0;i<N;i++) s=s+from_bits(a[i]);
    return to_bits(s);
}

__attribute__((noinline))
static uint32_t ordered_skip_zero(const uint32_t *a) {
    float s=0.0f;
    for(unsigned i=0;i<N;i++) if((a[i]&0x7fffffffu)!=0) s=s+from_bits(a[i]);
    return to_bits(s);
}

static int delta_one(uint32_t w,unsigned es,uint32_t sign,uint32_t *dout) {
    uint32_t mag=w&0x7fffffffu;
    if(mag==0) { *dout=0;return 1; }
    unsigned e=mag>>23;
    unsigned d=es-e;
    if((w&0x80000000u)!=sign || e==0 || e==255 || !(w&1u) || d<2 || d>24)
        return 0;
    uint32_t m=0x800000u+(mag&0x7fffffu);
    *dout=(m+(1u<<(d-1)))>>d;
    return 1;
}

__attribute__((noinline))
static uint32_t guarded(const uint32_t *a) {
    float s=0.0f;
    unsigned i=0;
    while(i<N) {
        uint32_t sw=to_bits(s), mag=sw&0x7fffffffu, sign=sw&0x80000000u;
        unsigned es=mag>>23;
        unsigned b=N-i<BLOCK?N-i:BLOCK;
        if(es>=1 && es<=253) {
            uint32_t sum[4]={0,0,0,0};
            int good=1;
            for(unsigned j=0;j<b;j++) {
                uint32_t delta;
                if(!delta_one(a[i+j],es,sign,&delta)) {good=0;break;}
                sum[j&3]+=delta;
            }
            uint32_t d=sum[0]+sum[1]+sum[2]+sum[3];
            if(good && d<=0x800000u-(mag&0x7fffffu)) {
                s=from_bits(sign|(mag+d));i+=b;continue;
            }
        }
        for(unsigned j=0;j<b;j++) s=s+from_bits(a[i+j]);
        i+=b;
    }
    return to_bits(s);
}

/* A second probe removes the unpredictable per-element zero branch. All shifts
 * are masked before execution, even on rejected data. UInt32 wrap on rejected
 * candidates is defined C arithmetic; accepted candidates obey D<=2^27.
 */
__attribute__((noinline))
static uint32_t guarded_branchless(const uint32_t *a) {
    float s=0.0f;
    unsigned i=0;
    while(i<N) {
        uint32_t sw=to_bits(s),mag=sw&0x7fffffffu,sign=sw&0x80000000u;
        unsigned es=mag>>23,b=N-i<BLOCK?N-i:BLOCK;
        int eligible=es>=1 && es<=253;
        /* At most four cheap prechecks limit dense/wide rejected-block cost. */
        if(eligible) for(unsigned j=0;j<b && j<4;j++) {
            uint32_t unused;
            if(!delta_one(a[i+j],es,sign,&unused)){eligible=0;break;}
        }
        if(eligible) {
            uint32_t sums[4]={0,0,0,0},good=1;
            for(unsigned j=0;j<b;j++) {
                uint32_t w=a[i+j],v=w&0x7fffffffu,nz=(v!=0);
                uint32_t e=v>>23,d=es-e,sh=d&31u;
                uint32_t m=((v&0x7fffffu)|0x800000u)&(0u-nz);
                uint32_t delta=((m+(1u<<((d-1)&31u)))>>sh)&(0u-nz);
                uint32_t valid=(e!=0)&(e!=255)&(w&1u)&((w&0x80000000u)==sign)&(d>=2)&(d<=24);
                good &= valid | (1u-nz);
                sums[j&3]+=delta;
            }
            uint32_t d=sums[0]+sums[1]+sums[2]+sums[3];
            if(good && d<=0x800000u-(mag&0x7fffffu)) {
                s=from_bits(sign|(mag+d));i+=b;continue;
            }
        }
        for(unsigned j=0;j<b;j++) s=s+from_bits(a[i+j]);
        i+=b;
    }
    return to_bits(s);
}

/* Same proved integer increments, computed by independent fixed-anchor adds.
 * For es>=3, positive odd subnormals also cannot be halfway: effective E=1.
 * Only the integer reduction may reassociate; each float addition is independent.
 */
__attribute__((noinline))
static uint32_t guarded_anchor(const uint32_t *a) {
    float s=0.0f;
    unsigned i=0;
    while(i<N) {
        uint32_t sw=to_bits(s),mag=sw&0x7fffffffu,sign=sw&0x80000000u;
        unsigned es=mag>>23,b=N-i<BLOCK?N-i:BLOCK;
        int eligible=es>=3 && es<=253;
        uint32_t limit=((es-1u)<<23)-1u;
        if(eligible) for(unsigned j=0;j<b && j<4;j++) {
            uint32_t w=a[i+j],v=w&0x7fffffffu;
            if(v && ((w&0x80000000u)!=sign || !(v&1u) || v>limit))
                {eligible=0;break;}
        }
        if(eligible) {
            uint32_t ah=es<<23,d=0,good=1;
            float h=from_bits(ah);
            for(unsigned j=0;j<b;j++) {
                uint32_t w=a[i+j],v=w&0x7fffffffu,z=(v==0);
                good &= (z|((w&0x80000000u)==sign)) & (z|(v&1u)) & (v<=limit);
                uint32_t out=to_bits(h+from_bits(v));
                d+=out-ah;
            }
            if(good && d<=0x800000u-(mag&0x7fffffu)) {
                s=from_bits(sign|(mag+d));i+=b;continue;
            }
        }
        for(unsigned j=0;j<b;j++) s=s+from_bits(a[i+j]);
        i+=b;
    }
    return to_bits(s);
}

static double now_ns(void) {
    struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);
    return (double)t.tv_sec*1e9+(double)t.tv_nsec;
}
static double measure(uint32_t (*fn)(const uint32_t*),const uint32_t *data,unsigned reps) {
    uint32_t hash=0;double start=now_ns();
    for(unsigned r=0;r<reps;r++) for(unsigned v=0;v<V;v++)
        hash=(hash^fn(data+v*N))*16777619u;
    double elapsed=now_ns()-start;sink=hash;
    return elapsed/((double)reps*V*N);
}

int main(int argc,char **argv) {
    unsigned reps=argc>1?(unsigned)strtoul(argv[1],0,10):1000;
    uint32_t *data=malloc(sizeof(uint32_t)*N*V);
    if(!data)return 1;
    puts("class,round,native_ns_per_element,skip_zero_ns_per_element,guarded_ns_per_element,guarded_over_native,branchless_ns_per_element,branchless_over_native,anchor_ns_per_element,anchor_over_native");
    for(unsigned kind=0;kind<3;kind++) {
        for(unsigned i=0;i<N*V;i++) {
            uint32_t w=rng32();
            data[i]= kind==2? (w&0x807fffffu)|((102+(w>>23)%50)<<23):
                     kind==1? ((w&1u)?(w&0x7fffffu)|((124+(w>>23)%7)<<23):0u):
                              (w&0x807fffffu)|((124+(w>>23)%7)<<23);
        }
        for(unsigned v=0;v<V;v++) {
            uint32_t ref=ordered(data+v*N), got=guarded(data+v*N);
            if(ref!=got){fprintf(stderr,"mismatch kind=%u v=%u %08x %08x\n",kind,v,ref,got);return 2;}
            if(ref!=guarded_branchless(data+v*N)){fprintf(stderr,"branchless mismatch kind=%u v=%u\n",kind,v);return 3;}
            if(ref!=guarded_anchor(data+v*N)){fprintf(stderr,"anchor mismatch kind=%u v=%u\n",kind,v);return 4;}
        }
        (void)measure(guarded,data,10);(void)measure(ordered,data,10);
        for(unsigned trial=0;trial<5;trial++) {
            double a,b,c,d,e;
            if(trial&1){e=measure(guarded_anchor,data,reps);d=measure(guarded_branchless,data,reps);c=measure(guarded,data,reps);b=measure(ordered_skip_zero,data,reps);a=measure(ordered,data,reps);}
            else {a=measure(ordered,data,reps);b=measure(ordered_skip_zero,data,reps);c=measure(guarded,data,reps);d=measure(guarded_branchless,data,reps);e=measure(guarded_anchor,data,reps);}
            printf("%s,%u,%.9f,%.9f,%.9f,%.6f,%.9f,%.6f,%.9f,%.6f\n",kind==0?"dense":kind==1?"relu":"wide",trial,a,b,c,c/a,d,d/a,e,e/a);
        }
    }
    free(data);return 0;
}
