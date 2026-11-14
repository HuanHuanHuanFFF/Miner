#!/usr/bin/env python3
"""Finite model of exactly the runtime's window order, sentinel, word operations."""
import hashlib,json,random
from pathlib import Path
P=Path(__file__).resolve().parent
MASK=(1<<64)-1;OLD=1<<57;PAYLOAD=1<<55;MASK56=(1<<56)-1
def acc(a,x,w,u):
    lo=x&((1<<25)-1);hi=((x>>25)-(1<<32))&MASK
    return [(a[0]+lo*(w-(1<<31)))&MASK,(a[1]+hi*(w-(1<<31)))&MASK,(a[2]+lo*(u-(1<<31)))&MASK,(a[3]+hi*(u-(1<<31)))&MASK]
def patch(data,ci,h,w,y,x):
    return [data[(c*h+yy)*w+xx] if 0<=yy<h and 0<=xx<w else 0 for c in range(ci) for dy in range(3) for dx in range(3) for yy,xx in [(y+dy-1,x+dx-1)]]
def packed(data,ci,h,w):
    padded=[(data[(c*h+y-1)*w+x-1] if 1<=y<=h and 1<=x<=w else 0)+OLD for c in range(ci) for y in range(h+2) for x in range(w+2)]
    out=[]
    for y in range(h):
     for x in range(w):
      for c in range(ci):
       row=(c*(h+2)+y)*(w+2)+x
       for dy in range(3):
        for dx in range(3):
         v=padded[row+dy*(w+2)+dx]
         if v!=OLD:
          q=((c*9+dy*3+dx)<<56)|(v-3*PAYLOAD)
          assert 0<q<1<<63
          out.append(q)
      out.append(0)
    return out
def main():
    rng=random.Random(2800112);cases=outputs=entries=0
    for ci in [1,3,7,14]:
     for h,w in [(1,1),(1,4),(3,2),(5,5)]:
      for co in [1,2,5,8]:
       for mode in ['zero','random','boundary','sparse']:
        def value():
          if mode=='zero':return 0
          if mode=='boundary':return rng.choice([-(1<<55)+1,-1,0,1,(1<<55)-1])
          if mode=='sparse' and rng.randrange(4):return 0
          return rng.randrange(-(1<<55)+1,1<<55)
        data=[value() for _ in range(ci*h*w)]
        ww=[rng.randrange(-(1<<30)+1,1<<30)+(1<<31) for _ in range(co*ci*9)]
        cache=packed(data,ci,h,w);entries+=len(cache);k=ci*9
        assert cache.count(0)==h*w
        for o in range(0,co,2):
          expected=[]
          for y in range(h):
           for x in range(w):
            a=[0]*4
            for t,v in enumerate(patch(data,ci,h,w,y,x)):
              a=acc(a,v+OLD,ww[o*k+t],ww[(o+1)*k+t] if o+1<co else 1<<31)
            expected.append(a)
          actual=[];a=[0]*4
          for q in cache:
            if q==0:actual.append(a);a=[0]*4
            else:
              t=q>>56;v=(q&MASK56)+3*PAYLOAD
              assert t<k
              a=acc(a,v,ww[o*k+t],ww[(o+1)*k+t] if o+1<co else 1<<31)
          assert actual==expected
          outputs+=len(actual)*(2 if o+1<co else 1)
        cases+=1
    bad_low=(0<<56)+(-(1<<55)+(1<<55))
    bad_high=(0<<56)+((1<<55)+(1<<55))
    assert bad_low==0 and bad_high>>56==1
    r={'state':'FINITE_PACKED_SUPPORT_MODEL_PASS','seed':2800112,'shape_mode_cases':cases,'output_accumulator_states':outputs,'packed_entries_including_sentinels':entries,'tested_cin':[1,3,7,14],'tested_cout':[1,2,5,8],'tested_spatial_shapes':[[1,1],[1,4],[3,2],[5,5]],'matched':'all four modulo64 accumulator states for every paired/unpaired output; existing finalizer/sign replay unchanged by proposed integration','strict_bound_counterexamples':{'X_equals_minus_2pow55':'index0 encodes sentinel0','X_equals_plus_2pow55':'payload carries into index1'},'source_rule':'admitted source11 X is strictly inside these endpoints; prototype adds K<128','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'not_claimed':['Lean proof','runtime compilation','candidate all12 gate','native speedup']}
    (P/'packed-support-model-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');print(json.dumps(r,indent=2))
if __name__=='__main__':main()
