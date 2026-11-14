"""Finite discriminator for dynamic 128-bit norm-moment overflow checks.

Includes a concrete counterexample to simply widening the old span guard.
No Lean acceptance or native speed is claimed.
"""
from __future__ import annotations
from datetime import datetime,timezone
import hashlib,json,random
from pathlib import Path
from norm_frontier import fields,gen
from mixer_frontier import dims

U=(1<<64)-1


def scan(words):
    lo=min((fields(w)[2]for w in words if fields(w)[1]),default=254)
    ph=pl=nh=nl=qh=ql=0;ok=len(words)<256;trace=[]
    for w in words:
        sign,m,i=fields(w);s=max(0,i-lo)
        if m and s>40:
            return {"accepted":False,"reason":"factor_width","at":len(trace),"low":lo}
        t=(m<<s)&U;q=m*m
        lower=(q<<(2*s))&U if 2*s<64 else 0
        upper=(q>>(64-2*s)) if 2*s<64 else ((q<<(2*s-64))&U)
        newl=(ql+lower)&U;carry=int(newl<ql)
        h1=(qh+carry)&U;h2=(h1+upper)&U
        ok=ok and h1>=qh and h2>=h1
        qh,ql=h2,newl
        if sign<0:
            new=(nl+t)&U;nh=(nh+int(new<nl))&U;nl=new
        else:
            new=(pl+t)&U;ph=(ph+int(new<pl))&U;pl=new
        trace.append({"q_hi":qh,"q_lo":ql,"ok":ok})
    factors=[s*(m<<max(0,i-lo))for s,m,i in map(fields,words)]
    exactq=sum(t*t for t in factors);exacts=sum(factors)
    sq=(qh<<64)+ql;ss=(ph<<64)+pl-(nh<<64)-nl
    if ok:
        assert exactq==sq and exacts==ss
    else:
        assert exactq>=1<<128 or len(words)>=256
    return {"accepted":ok,"reason":"accepted"if ok else"sum_overflow_or_length","low":lo,
            "sum_squares_bits":exactq.bit_length(),"sum_abs_bits":abs(exacts).bit_length(),
            "raw_square_mod_matches":sq==exactq% (1<<128)}


def main():
    started=datetime.now(timezone.utc).isoformat();rng=random.Random(0x270612)
    real=[]
    for seed in[27061001,27161004,27261007]:
        for profile in["typical","scale","boundary"]:
            t,c=dims(seed,profile)
            for kind in["normal","wide","sparse"]:
                x=gen(kind,t*c,seed+999)
                for r in range(t):
                    words=x[r*c:(r+1)*c];res=scan(words)
                    res.update(seed=seed,profile=profile,kind=kind,row=r,n=c)
                    real.append(res)
    random_cases=[]
    for n in[1,2,3,8,16,31,63,128,255,256]:
        for maxspan in[0,16,24,32,36,37,38,39,40,41]:
            for _ in range(20):
                base=rng.randrange(1,210)
                words=[((rng.randrange(2)<<31)|((base+rng.randrange(maxspan+1))<<23)|rng.getrandbits(23))for _ in range(n)]
                words[0]=(base<<23)|1
                res=scan(words);res.update(n=n,maxspan=maxspan);random_cases.append(res)
    # With span39 and 255 values, actual sum can exceed 128 bits. The old
    # exact proof's span36/n<256 bound cannot merely be changed to span40.
    witness=[1]+[((40<<23)|0x7fffff)]*254
    bad=scan(witness)
    assert not bad["accepted"] and bad["sum_squares_bits"]>128
    out={"status":"FINITE_DYNAMIC_GUARD_CHECK_ONLY","start_utc":started,"end_utc":datetime.now(timezone.utc).isoformat(),
        "source_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"real_mixer_first_norm_rows":real,
        "random_case_count":len(random_cases),"random_accepted":sum(x["accepted"]for x in random_cases),
        "counterexample":{"words_hex":["00000001"]+["147fffff"]*254,"result":bad},
        "limitations":["not Lean compiled","not full12 theorem","not cost measurement","n>=256 remains fallback"]}
    p=Path(__file__).with_name("norm-dynamic-result.json");p.write_text(json.dumps(out,indent=2),encoding="utf-8")
    print(json.dumps({"real_rows":len(real),"real_accepted":sum(x["accepted"]for x in real),"random_cases":len(random_cases),"counterexample_bits":bad["sum_squares_bits"]}))


if __name__=="__main__":main()
