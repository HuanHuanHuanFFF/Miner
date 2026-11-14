"""Pinned-formula Mixer census: exact arithmetic, no native timing claim."""
from __future__ import annotations
from collections import Counter
from datetime import datetime,timezone
import hashlib,json,struct
from pathlib import Path
from norm_frontier import gen,weights,bias,scale,key,fields,round_ratio,linear,norm,lcg


def dims(seed,profile):
    r=lcg(8,seed^0x5BD1E995);draw=lambda i,s:r[i]%s
    T=9+2*draw(6,5) if profile=="boundary" else (20+2*draw(6,7) if profile=="scale" else 8+draw(6,9))
    C=15+2*draw(7,10) if profile=="boundary" else (12+draw(7,9) if profile=="scale" else 16+4*draw(7,9))
    return T,C


def gemm(A,B,m,k,n):
    a=list(map(key,A));b=list(map(key,B))
    return [round_ratio(sum(a[i*k+t]*b[t*n+j] for t in range(k)),1,-298) for i in range(m)for j in range(n)]


def add(a,b):return[round_ratio(key(x)+key(y),1,-149)for x,y in zip(a,b)]


def norm_stats(x,rows,n):
    out=[]
    for r in range(rows):
        row=x[r*n:(r+1)*n]
        lo=min((fields(w)[2]for w in row if fields(w)[1]),default=255)
        hi=max((fields(w)[2]for w in row if fields(w)[1]),default=0)
        z=[s*(m<<max(0,i-lo))for s,m,i in map(fields,row)]
        out.append({"span":max(0,hi-lo),"n":n,"sum_abs_bits":abs(sum(z)).bit_length(),
                    "sum_squares_bits":sum(t*t for t in z).bit_length(),
                    "old_stats_guard":n<256 and max(0,hi-lo)<=36})
    return out


def linear_stats(x,w,rows,k,n):
    mx=[fields(t)for t in x];mw=[fields(t)for t in w]
    loX=min((i for s,m,i in mx if m),default=254);hiX=max((i for s,m,i in mx if m),default=0)
    loW=min((i for s,m,i in mw if m),default=254);hiW=max((i for s,m,i in mw if m),default=0)
    width=50+max(0,hiX-loX)+max(0,hiW-loW)+k.bit_length()-1
    return {"shape":[rows,k,n],"macs":rows*k*n,"zero_x":sum(m==0 for s,m,i in mx),
            "x_words":len(mx),"zero_w":sum(m==0 for s,m,i in mw),"w_words":len(mw),
            "packed_digit_bits":width,"packed_factor_bytes_lower_bound":(k*n*width+7)//8,
            "x_span":max(0,hiX-loX),"w_span":max(0,hiW-loW)}


def main():
    started=datetime.now(timezone.utc).isoformat();results=[]
    for seed in[27061001,27161004,27261007]:
        for profile in["typical","scale","boundary"]:
            T,C=dims(seed,profile)
            for kind in["normal","wide","sparse"]:
                x=gen(kind,T*C,seed+999); saved=x
                statistics={"norm1":norm_stats(x,T,C)}
                x=norm(x,T,C,scale(seed+1,C),bias(seed,2,C))
                a=weights(kind,seed,3,T,T*T)
                statistics["gemm"]={"shape":[T,T,C],"macs":T*T*C,"transposed_linear_branch":T>=20}
                x=add(gemm(a,x,T,T,C),saved);saved=x
                statistics["norm2"]=norm_stats(x,T,C)
                x=norm(x,T,C,scale(seed+4,C),bias(seed,5,C))
                w=weights(kind,seed,6,C,2*C*C)
                statistics["linear1"]=linear_stats(x,w,T,C,2*C)
                x=linear(x,T,C,2*C,w,bias(seed,7,2*C),True)
                w=weights(kind,seed,8,2*C,2*C*C)
                statistics["linear2"]=linear_stats(x,w,T,2*C,C)
                x=add(linear(x,T,2*C,C,w,bias(seed,9,C),False),saved)
                w=weights(kind,seed,10,T*C,10*T*C)
                statistics["classifier"]=linear_stats(x,w,1,T*C,10)
                x=linear(x,1,T*C,10,w,bias(seed,11,10),False)
                results.append({"seed":seed,"profile":profile,"kind":kind,"tokens":T,"channels":C,
                    "statistics":statistics,"output_sha256":hashlib.sha256(b''.join(struct.pack('<I',w)for w in x)).hexdigest()})
    out={"status":"EXACT_FINITE_FORMULA_CENSUS_NOT_LEAN","start_utc":started,"end_utc":datetime.now(timezone.utc).isoformat(),
         "source_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"cells":results,
         "limits":["one sample per cell; official batches repeat model per sample","no native cost","no current-source direct run","not original all12 gate"]}
    p=Path(__file__).with_name("mixer-frontier-result.json");p.write_text(json.dumps(out,indent=2),encoding="utf-8")
    rows=[r for c in results for stage in["norm1","norm2"] for r in c["statistics"][stage]]
    print(json.dumps({"cells":len(results),"norm_rows":len(rows),"old_guard_failed_rows":sum(not r['old_stats_guard']for r in rows),
        "q_bits":dict(Counter(r['sum_squares_bits'] for r in rows)),"failed_spans":dict(Counter(r['span']for r in rows if not r['old_stats_guard']))}))


if __name__=="__main__":main()
