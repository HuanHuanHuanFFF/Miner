"""Finite-check the complete packed-linear arithmetic, including exact bias.

Mirrors the owned Lean runtime structurally, while the oracle uses a single
fixed 2^-298 integer sum. Neither is a Lean correctness proof.
"""
from __future__ import annotations
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import random

from norm_frontier import fields, key, round_ratio, MASK


def oracle(X,W,b,rows,k,n,relu):
    out=[]
    for r in range(rows):
        for j in range(n):
            terms=[key(X[r*k+i])*key(W[j*k+i]) for i in range(k)]
            total=sum(terms)+(key(b[j])<<149)
            if total:
                word=round_ratio(total,1,-298)
            else:
                all_zero=all(t==0 for t in terms) and key(b[j])==0
                all_negative=bool(b[j]>>31) and all(bool((X[r*k+i]^W[j*k+i])>>31) for i in range(k))
                word=0x80000000 if all_zero and all_negative else 0
            out.append(0 if relu and word>>31 else word)
    return out


def complete(X,W,b,rows,k,n,relu,tile):
    if not rows or not n:return []
    if not k:return oracle(X,W,b,rows,k,n,relu)
    ax=min((fields(w)[2] for w in X if fields(w)[1]),default=254)
    aw=min((fields(w)[2] for w in W if fields(w)[1]),default=254)
    hiX=max((fields(w)[2] for w in X if fields(w)[1]),default=0)
    hiW=max((fields(w)[2] for w in W if fields(w)[1]),default=0)
    width=50+max(0,hiX-ax)+max(0,hiW-aw)+k.bit_length()-1
    half=1<<(width-1);mask=(1<<width)-1
    A=[s*(m<<max(0,i-ax)) for s,m,i in map(fields,X)]
    V=[s*(m<<max(0,i-aw)) for s,m,i in map(fields,W)]
    out=[0]*(rows*n)
    for start in range(0,n,tile):
        count=min(tile,n-start)
        P=[]
        for i in range(k):
            p=0
            for j in reversed(range(count)):
                p=(p<<width)+V[(start+j)*k+i]
            P.append(p)
        offset=sum(half<<(width*j) for j in range(count))
        for row in range(rows):
            packed=sum(A[row*k+i]*P[i] for i in range(k))+offset
            assert packed>=0
            for col in range(count):
                total=(packed&mask)-half
                packed>>=width
                j=start+col
                sb,mb,ib=fields(b[j]);bi=ib+149;lo=min(ax+aw,bi)
                joined=(total<<(ax+aw-lo))+(sb*mb<<(bi-lo))
                word=round_ratio(joined,1,lo-298) if joined else oracle(X,W,b,rows,k,n,False)[row*n+j]
                out[row*n+j]=0 if relu and word>>31 else word
            assert packed==0
    return out


def main():
    start=datetime.now(timezone.utc).isoformat();rng=random.Random(0x2706001)
    finite_edges=[0,0x80000000,1,0x80000001,0x007fffff,0x807fffff,0x00800000,0x80800000,
                  0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x3f000000,0x33800000]
    cases=[]
    for rows,k,n in [(0,3,4),(2,3,0),(1,0,4),(1,1,1),(2,2,3),(3,5,7),(8,17,19)]:
        for mode in ["edge","random","zeros","cancel"]:
            def word():
                if mode in ["edge","zeros","cancel"]:
                    return rng.choice(finite_edges if mode!="zeros" else [0,0x80000000])
                w=rng.getrandbits(32)
                return w if ((w>>23)&255)<255 else w^0x00800000
            X=[word() for _ in range(rows*k)];W=[word()for _ in range(n*k)];b=[word()for _ in range(n)]
            if mode=="cancel" and k>=2:
                X=[0x3f800000]*(rows*k)
                W=[(0xbf800000 if i%2 else 0x3f800000) if i+1<k or k%2==0 else 0 for j in range(n) for i in range(k)]
                b=[0x80000000]*n
            for relu in [False,True]:
                expected=oracle(X,W,b,rows,k,n,relu)
                for tile in [1,4,16,32]:
                    got=complete(X,W,b,rows,k,n,relu,tile)
                    assert got==expected,(rows,k,n,mode,relu,tile)
                    cases.append({"shape":[rows,k,n],"mode":mode,"relu":relu,"tile":tile,
                                  "outputs":len(got),"sha256":hashlib.sha256(repr(got).encode()).hexdigest()})
    result={"status":"FINITE_CALLER_FORMULA_CHECK_ONLY","start_utc":start,"end_utc":datetime.now(timezone.utc).isoformat(),
            "source_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"cases":cases,
            "case_count":len(cases),"output_words_checked":sum(c["outputs"]for c in cases),
            "coverage":["normal/subnormal/max-finite","both zero signs","exact bias once","cancellation","overflow","empty rows/columns","k=0 fallback","row-major output","ReLU"],
            "limitations":["not compiled Lean","finite inputs only; nonfinite/malformed fallback is source reviewed only","not original12 gate","not native timing"]}
    out=Path(__file__).with_name("packed-caller-result.json");out.write_text(json.dumps(result,indent=2),encoding="utf-8")
    print(json.dumps({k:result[k]for k in ["case_count","output_words_checked","status"]}))


if __name__=="__main__":main()
