"""Finite layout/initial-source/cache model for a proposed same-head tag; no candidate."""
from pathlib import Path
import json
import random

OUT=Path(__file__).resolve().parents[1]/'evidence/round26/route-a'
MASK24=(1<<24)-1
MASK64=(1<<64)-1

def key(k):
    h=(k*0x9e3779b97f4a7c15)&MASK64
    return h>>49,(h>>41)&255

def ahead(head,k):
    slot,tag=key(k);stored=head[slot];pos=stored&MASK24;oldtag=stored>>24
    miss=stored!=0 and oldtag!=tag
    return slot|(tag<<15)|(oldtag<<23),pos|(int(miss)<<24)

def main():
    rng=random.Random(261414);cases=0;misses=0;prefix_equal=0;zero_reads=0;cache_checks=0
    boundary=[]
    for p in [0,1,32767,32768,MASK24-1,MASK24]:
        for tag in range(256):
            h=p|(tag<<24);assert h<1<<32 and h&MASK24==p and h>>24==tag
            slot=32767;want=255;packed=slot|(want<<15)|(tag<<23)
            assert packed<1<<31 and packed&32767==slot and (packed>>15)&255==want and (packed>>23)&255==tag
            c=p|(1<<24);assert c<1<<25 and c&MASK24==p and c>>24==1;cases+=1
    for km in [0xffffffff,0xffffff00]:
        original=[0]*32768;head=[0]*32768;prev0=[0]*32768;prev1=[0]*32768
        keys=[rng.getrandbits(32)&km for _ in range(100000)]
        for p,k in enumerate(keys):
            packed,c=ahead(head,k);slot=packed&32767;tag=(packed>>15)&255;old=head[slot]
            assert c&MASK24==original[slot]
            assert (c&MASK24)|(((packed>>23)&255)<<24)==old
            source=original[slot]
            if old==0:assert c>>24==0;zero_reads+=1
            if keys[source]==k:assert c>>24==0;prefix_equal+=1
            if c>>24:assert keys[source]!=k;misses+=1
            # Full packed-head equality is the cache identity; no tuple extra field.
            for replacement in [old,((p+1)&MASK24)|(rng.randrange(256)<<24)]:
                fixed=replacement==((c&MASK24)|(((packed>>23)&255)<<24))
                assert fixed==(replacement==old);cache_checks+=1
            prev0[p%32768]=original[slot];original[slot]=p
            prev1[p%32768]=head[slot]&MASK24;head[slot]=p|(tag<<24)
            assert prev0[p%32768]==prev1[p%32768]and head[slot]&MASK24==original[slot]
            cases+=1
    for n in [(1<<24)-1,1<<24,(1<<24)+1]:boundary.append({'n':n,'use_original_kernel':n>=1<<24})
    result={'status':'VERIFIED_FINITE_TAG_LAYOUT_SOURCE0_AND_CACHE_MODEL_NOT_NATIVE_OR_EQUIVALENCE_PROOF',
       'cases':cases,'cache_checks':cache_checks,'model_tag_misses':misses,'model_prefix_equal':prefix_equal,'model_zero_source_reads':zero_reads,
       'fallback_boundary_model':boundary,'limits':['Randomkeymodelcountsarenotcorpuscoverage orperformance.','No actualRustfallbackexecution,parsertrajectory,encoder,Leanorcurrentpoolresult.']}
    (OUT/'tagged-head-layout-model.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result,indent=2))

if __name__=='__main__':main()
