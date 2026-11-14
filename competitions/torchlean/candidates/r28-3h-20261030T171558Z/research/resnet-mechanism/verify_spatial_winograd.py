#!/usr/bin/env python3
"""Finite exact integer/64-bit checks only; no model/native/gate claim."""
import hashlib,json,random
from pathlib import Path
P=Path(__file__).resolve().parent
MASK=(1<<64)-1
BT=((1,0,-1,0),(0,1,1,0),(0,-1,1,0),(0,1,0,-1))
G=((2,0,0),(1,1,1),(1,-1,1),(0,0,2))
AT=((1,1,1,0),(0,1,-1,-1))
def mm(a,b): return [[sum(x*y for x,y in zip(row,col)) for col in zip(*b)] for row in a]
def tr(a): return list(map(list,zip(*a)))
def transform(a,t): return mm(mm(t,a),tr(t))
def s64(x): return ((x+(1<<63))&MASK)-(1<<63)
def pair(x,w): return ((x% (1<<25))*w,(x//(1<<25))*w)
def word_block(vs,us):
    lo=hi=0
    for v,u in zip(vs,us):
        l,h=pair(v,u)
        lo=(lo+l)&MASK;hi=(hi+h)&MASK
    return s64(lo)+(1<<25)*s64(hi)
def tile(ds,ws):
    vs=[transform(d,BT) for d in ds]
    us=[transform(w,G) for w in ws]
    m=[[sum(v[i][j]*u[i][j] for v,u in zip(vs,us)) for j in range(4)] for i in range(4)]
    mw=[[sum(word_block([v[i][j] for v in vs[k:k+8]],[u[i][j] for u in us[k:k+8]]) for k in range(0,len(ds),8)) for j in range(4)] for i in range(4)]
    assert mw==m
    out=transform(m,AT)
    direct=[[sum(d[y+r][x+c]*w[r][c] for d,w in zip(ds,ws) for r in range(3) for c in range(3)) for x in range(2)] for y in range(2)]
    assert out==[[4*a for a in row] for row in direct]
    assert all(v%4==0 for row in out for v in row)
    return max(abs(pair(v[i][j],u[i][j])[0]) for v,u in zip(vs,us) for i in range(4) for j in range(4)),max(abs(pair(v[i][j],u[i][j])[1]) for v,u in zip(vs,us) for i in range(4) for j in range(4))
def main():
    rng=random.Random(280011)
    cases=0; maxlo=maxhi=0
    for nc in (1,3,4,5,6,7,8,9,14,16,28):
      for f in (0,1,3,6):
       g=31-f
       for mode in ('random','positive','negative','sparse','alternating'):
        ds=[];ws=[]
        for ch in range(nc):
         def value(bits,pos):
          a=(1<<bits)-1 if mode in ('positive','negative','alternating') else rng.randrange(1<<bits)
          if mode=='negative' or mode=='alternating' and pos%2: a=-a
          if mode=='random' and rng.randrange(2): a=-a
          if mode=='sparse' and rng.randrange(2): a=0
          return a
         ds.append([[value(24+g,i*4+j+ch) for j in range(4)] for i in range(4)])
         ws.append([[value(24+f,i*3+j+ch) for j in range(3)] for i in range(3)])
        lo,hi=tile(ds,ws);maxlo=max(maxlo,lo);maxhi=max(maxhi,hi);cases+=1
    # Full-channel reuse of signed64 partials fails inside source11's old K<256 bound.
    # Use representable mantissa/exponent values, and one low-exponent weight per kernel.
    mant=(1<<24)-1;X=mant<<25;Wh=mant<<6;Wl=mant
    d=[[X]*4 for _ in range(4)];w=[[Wh]*3 for _ in range(3)];w[0][0]=Wl
    v=transform(d,BT)[1][1];u=transform(w,G)[1][1]
    nc=28; exact=nc*v*u;wrong=word_block([v]*nc,[u]*nc)
    overflow_u=u
    assert wrong!=exact
    assert sum(pair(v,u)[1] for _ in range(nc)) >= 1<<63
    # Arbitrary UInt64 input pairs: zero skipping preserves modular four-accumulator state.
    zero=(1<<57);nzero=0
    for i in range(10000):
      x=zero if i%2==0 else rng.getrandbits(64)
      w=rng.getrandbits(64);u=rng.getrandbits(64);a=[rng.getrandbits(64) for _ in range(4)]
      low=x&((1<<25)-1);high=((x>>25)-(1<<32))&MASK
      out=[(a[0]+low*(w-(1<<31)))&MASK,(a[1]+high*(w-(1<<31)))&MASK,(a[2]+low*(u-(1<<31)))&MASK,(a[3]+high*(u-(1<<31)))&MASK]
      skipped=a if x==zero else out
      assert skipped==out;nzero+=1
    out={'state':'FINITE_MODEL_PASS','seed':280011,'spatial_tiles':cases,'output_identities':cases*4,'split25_eight_channel_word_blocks':'PASS for all checked transformed coordinates','max_abs_single_low':str(maxlo),'max_abs_single_high':str(maxhi),'zero_pair_mod64_cases':nzero,'counterexample':{'scope':'naive unblocked signed64 reuse; not base11 bug','cin':nc,'k':nc*9,'g':25,'f':6,'X':str(X),'W_high':Wh,'W_low':Wl,'V':str(v),'U':overflow_u,'high_sum':str(nc*pair(v,overflow_u)[1]),'signed64_bound':str(1<<63),'expected':str(exact),'naive_result':str(wrong)},'not_claimed':['Lean compilation','all-input proof','source11 actual hit coverage','native speedup','whole-model acceptance'],'corrected_receipt':'v0 INVALID only for printed U/high_sum: random loop reused name u; assertions and exact/naive results were already computed before reuse','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (P/'finite-model-receipt.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(out,indent=2))
if __name__=='__main__':main()
