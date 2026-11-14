"""Exact paired-product identity and bounded-factor coverage, no native claim.

Independent mechanism from output packing: share row/column products, then
replace each two MACs by one product of sums. Only coverage is discriminated.
"""
from __future__ import annotations
from datetime import datetime,timezone
import hashlib,json,random
from pathlib import Path
import mixer_frontier as mf
import norm_frontier as nf


def paired(a,w):
    k=len(a);pairs=k//2
    row=sum(a[2*i]*a[2*i+1]for i in range(pairs))
    out=[]
    for b in w:
        col=sum(b[2*i]*b[2*i+1]for i in range(pairs))
        cross=sum((a[2*i]+b[2*i+1])*(a[2*i+1]+b[2*i])for i in range(pairs))
        out.append(cross-row-col+(a[-1]*b[-1] if k%2 else 0))
    return out


def norm_factors(words):
    lo=min((nf.fields(w)[2]for w in words if nf.fields(w)[1]),default=254)
    a=[s*(m<<max(0,i-lo))for s,m,i in map(nf.fields,words)]
    return a,max((abs(v)for v in a),default=0)


def coverage(x,w,rows,k,n):
    A=[norm_factors(x[r*k:(r+1)*k])for r in range(rows)]
    B=[norm_factors(w[j*k:(j+1)*k])for j in range(n)]
    eligible=sum(a[1]+b[1]<1<<32 for a in A for b in B)
    # Native proof must use signed-magnitude multiplication: abs(sum)<2^32
    # bounds each full unsigned64 product, not signed63 decoding.
    return {"shape":[rows,k,n],"eligible_outputs":eligible,"outputs":rows*n,
        "input_max_bits":[v[1].bit_length()for v in A],"weight_max_bits":[v[1].bit_length()for v in B],
        "original_product_count":rows*k*n,
        "all_eligible_product_count":(k//2)*(rows*n+rows+n)+(k%2)*rows*n,
        "actual_cost":"UNKNOWN; coverage/counts do not bound wall time"}


def main():
    started=datetime.now(timezone.utc).isoformat();rng=random.Random(0x270640)
    checks=0
    for k in[0,1,2,3,7,16,31,128]:
        for bits in[1,24,31,32,63,277]:
            for _ in range(12):
                a=[rng.randrange(-(1<<bits),1<<bits)for _ in range(k)]
                w=[[rng.randrange(-(1<<bits),1<<bits)for _ in range(k)]for _ in range(5)]
                assert paired(a,w)==[sum(x*y for x,y in zip(a,b))for b in w]
                checks+=1
    cells=[]
    for seed in[27061001,27161004,27261007]:
        for profile in["typical","scale","boundary"]:
            T,C=mf.dims(seed,profile)
            for kind in["normal","wide","sparse"]:
                x=nf.gen(kind,T*C,seed+999);saved=x
                x=nf.norm(x,T,C,nf.scale(seed+1,C),nf.bias(seed,2,C))
                x=mf.add(mf.gemm(nf.weights(kind,seed,3,T,T*T),x,T,T,C),saved);saved=x
                x=nf.norm(x,T,C,nf.scale(seed+4,C),nf.bias(seed,5,C))
                w=nf.weights(kind,seed,6,C,2*C*C);a=coverage(x,w,T,C,2*C)
                x=nf.linear(x,T,C,2*C,w,nf.bias(seed,7,2*C),True)
                w=nf.weights(kind,seed,8,2*C,2*C*C);b=coverage(x,w,T,2*C,C)
                cells.append({"seed":seed,"profile":profile,"kind":kind,"linear1":a,"linear2":b})
    total={}
    for stage in["linear1","linear2"]:
        total[stage]={k:sum(c[stage][k]for c in cells)for k in["eligible_outputs","outputs","original_product_count","all_eligible_product_count"]}
    out={"status":"FINITE_IDENTITY_AND_FACTOR_COVERAGE_ONLY","start_utc":started,"end_utc":datetime.now(timezone.utc).isoformat(),
         "source_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"identity_cases":checks,"cells":cells,"totals":total,
         "limits":["not Lean","not runtime cost","correction/preparation/native signed128 accumulation still needed","no current champion claim"]}
    dest=Path(__file__).with_name("winograd-discriminator-result.json");dest.write_text(json.dumps(out,indent=2),encoding="utf-8")
    print(json.dumps({"identity_cases":checks,"totals":total}))


if __name__=="__main__":main()
