"""Exact finite coverage/endpoint falsifier for the native moment/sqrt graft.

Own mathematical model of the documented unsigned128 guards and rounding
formula. Shared self-authored model supplies exact rows and rational oracle.
No Lean execution, timing result, independent holdout or champion claim.
"""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
from math import isqrt
import hashlib
import json
import sys
import time

sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
FRONTIER=HERE.parent.parent/"research/board-frontier"
sys.path.insert(0,str(FRONTIER))
import norm_frontier as nf

def native_denominator(words):
    n=len(words)
    parts=list(map(nf.fields,words))
    base=min((e for _,m,e in parts if m),default=255)
    spans=[max(e-base,0) for _,m,e in parts if m]
    if n>=256 or any(s>36 for s in spans):
        return None,"moment_span_or_length",{}
    first=sum(s*(m<<max(e-base,0)) for s,m,e in parts)
    squares=sum(m*m<<(2*max(e-base,0)) for _,m,e in parts)
    total=n*squares
    if abs(first)>=1<<64 or total>=1<<128 or first*first>total:
        return None,"native_variance_guard",{"first_bits":abs(first).bit_length(),"q_times_n_bits":total.bit_length()}
    variance=total-first*first
    _,eps_m,eps_e=nf.fields(nf.EPS)
    common=min(2*base,eps_e+149)//2*2
    variance_shift=2*base-common
    eps_shift=eps_e+149-common
    eps_scaled=n*n*eps_m
    if variance.bit_length()+variance_shift>=128 or eps_scaled.bit_length()+eps_shift>=128:
        return None,"aligned_bitlength_guard",{}
    numerator=(variance<<variance_shift)+(eps_scaled<<eps_shift)
    if numerator>=1<<128:
        return None,"aligned_add_guard",{}
    divisor=n*n
    shift=(48-(numerator.bit_length()-1)+(divisor.bit_length()-1))//2
    if shift>=0 or -shift>=64:
        return None,"sqrt_scale_guard",{"scale":shift}
    k=-shift
    q,r=divmod(numerator>>(2*k),divisor)
    if q>=1<<62:
        return None,"sqrt_quotient_guard",{}
    two_bits=(numerator>>(2*k-2))&3
    low_zero=numerator%(1<<(2*k-2))==0
    root=isqrt(q)
    if q==root*root and r==0 and two_bits==0 and low_zero:
        accuracy=0
    elif q<root*root+root or (q==root*root+root and 4*r+two_bits<divisor):
        accuracy=1
    elif q==root*root+root and 4*r+two_bits==divisor and low_zero:
        accuracy=2
    else:
        accuracy=3
    exponent=(common-298)//2-shift+int(root>=1<<24)+150
    if not (1<<23<=root<1<<25 and 1<=exponent<=253):
        return None,"sqrt_pack_guard",{"root_bits":root.bit_length(),"biased_exponent":exponent}
    rounded=nf.quotient_even(4*root+accuracy,4 if root<1<<24 else 8)
    result=((exponent+1)<<23) if rounded==1<<24 else (exponent<<23)|(rounded-(1<<23))
    return result,"native_fast",{"base":base,"span":max(spans,default=0),"numerator_bits":numerator.bit_length(),"scale":shift}

def expected(words):
    n=len(words);keys=list(map(nf.key,words));first=sum(keys);squares=sum(k*k for k in keys)
    return nf.sqrt_ratio(n*squares-first*first+n*n*nf.key(nf.EPS)*(1<<149),n*n<<298)

def main():
    start=time.monotonic();counts=Counter();cells=[];stream=hashlib.sha256();misses=[]
    seed=27051001
    for profile in["typical","boundary"]:
        i,h,h2=nf.dimensions(seed,profile)
        for kind in["normal","wide","sparse"]:
            for rows in[1,8]:
                x=nf.gen(kind,rows*i,seed+999)
                x=nf.linear(x,rows,i,h,nf.weights(kind,seed,1,i,h*i),nf.bias(seed,2,h),True)
                x=nf.norm(x,rows,h,nf.scale(seed+3,h))
                x=nf.linear(x,rows,h,h2,nf.weights(kind,seed,4,h,h2*h),nf.bias(seed,5,h2),True)
                cell_counts=Counter()
                for row in range(rows):
                    words=x[row*h2:(row+1)*h2]
                    actual,state,meta=native_denominator(words)
                    oracle=expected(words)
                    if actual is not None:
                        assert actual==oracle,(profile,kind,rows,row,actual,oracle,meta)
                    else:
                        misses.append({"profile":profile,"kind":kind,"rows":rows,"row":row,"state":state,"meta":meta})
                    cell_counts[state]+=1
                    stream.update(json.dumps([profile,kind,rows,row,state,actual,oracle,meta],separators=(",",":")).encode()+b"\n")
                counts.update(cell_counts)
                cells.append({"profile":profile,"kind":kind,"rows":rows,"shape":[i,h,h2,10],"counts":dict(cell_counts)})
    directed=[]
    fixtures={"zeros":[0]*32,"mixed_zero_signs":[0,0x80000000]*16,"equal_ones":[0x3f800000]*32,
              "canceling_ones":[0x3f800000,0xbf800000]*16,"subnormal":[1,0x80000001]*16,
              "large_finite":[0x7f7fffff,0xff7fffff]*16,"length_guard":[0x3f800000]*256,
              "wide_span":[0x00800000,0x7f7fffff]*16}
    for name,words in fixtures.items():
        actual,state,meta=native_denominator(words);oracle=expected(words)
        if actual is not None:
            assert actual==oracle,(name,actual,oracle,meta)
        directed.append({"name":name,"state":state,"actual":actual,"oracle":oracle,"meta":meta})
    report={"at_utc":datetime.now(timezone.utc).isoformat(),
            "scope":"FINITE_NATIVE_GUARD_AND_SQRT_FORMULA_ONLY_NOT_LEAN_OR_NATIVE_SPEED",
            "seed":seed,"seen_exploration":True,"cells":cells,"row_counts":dict(counts),"guard_misses":misses,
            "directed":directed,"result_stream_sha256":stream.hexdigest(),
            "oracle_source_sha256":hashlib.sha256((FRONTIER/"norm_frontier.py").read_bytes()).hexdigest(),
            "recipe_sha256":hashlib.sha256((HERE/"graft_native_stats_v1.py").read_bytes()).hexdigest(),
            "candidate_sha256":"beca1b56d24ed64ed124fbeae50cb8be267fe3361336eab52b24f0c49720b0ed",
            "model_wall_seconds":time.monotonic()-start,"complete_call_speed":"UNKNOWN"}
    (HERE/"native-stats-model.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"cells":len(cells),"rows":dict(counts),"directed":directed,"seconds":report["model_wall_seconds"]},indent=2))

if __name__=="__main__":
    main()
