"""Old-seen complete Mixer formula census for exact native64/block prospects.

This does not execute Lean or native code. Counts do not establish speed or a
new full-input theorem. Only previously retained R27 seeds are inspected.
"""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import hashlib,importlib.util,json,struct,sys,time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
R27=ROUND.parent/"r27-5h-20261029T194443Z/research/board-frontier"
def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def yc(words):
    lo,hi=511,0
    for w in words:
        a=w&0x7fffffff
        lo=min(lo,((a-1)&0xffffffff)>>23);hi=max(hi,a>>23)
    return max(0,lo-1),max(0,hi-1),hi!=255
def main():
    start=time.monotonic();f=load(R27/"norm_frontier.py","r28_block_formula")
    # Importing this owned module requires its sibling name; no code mutation.
    sys.modules["norm_frontier"]=f;m=load(R27/"mixer_frontier.py","r28_block_mixer")
    old=json.loads((R27/"mixer-frontier-result.json").read_text())["cells"]
    expected={(r["seed"],r["profile"],r["kind"]):r["output_sha256"] for r in old}
    rows=[]
    def observe(stage,x,w,b,n,k,out):
        assert time.monotonic()-start<20,"20 second local light-model cap"
        xs=[x[i*k:(i+1)*k] for i in range(n)];ws=[w[j*k:(j+1)*k] for j in range(out)]
        xm=list(map(yc,xs));wm=list(map(yc,ws));count=Counter();spans=Counter();blocks=Counter()
        for i,a in enumerate(xm):
            for j,z in enumerate(wm):
                count["dots"]+=1;count["logical_MACs"]+=k
                mb=f.fields(b[j])[1];ib=f.fields(b[j])[2]+126
                lo=min(a[0]+z[0],ib) if mb else a[0]+z[0]
                hi=max(a[1]+z[1],ib) if mb else a[1]+z[1]
                span=hi-lo
                if not (a[2] and z[2] and ((b[j]>>23)&255)!=255 and 0<=span<=15):continue
                count["native128_eligible_dots"]+=1;count["native128_eligible_MACs"]+=k;spans[span]+=1
                group=1<<min(4,15-span);blocks[group]+=1
                count["blocked_merge_upper_bound"]+=(k+group-1)//group
                if k<=1<<(15-span):count["whole64_eligible_dots"]+=1;count["whole64_eligible_MACs"]+=k
                # Exact finite formula confirms the proposed coarse guard is sound here.
                products=[]
                for u,v in zip(xs[i],ws[j]):
                    sa,ma,ia=f.fields(u);sb,mv,iv=f.fields(v)
                    products.append(sa*sb*(ma*mv<<max(0,ia+iv-lo)))
                for t in range(0,k,group):
                    mass=sum(abs(p) for p in products[t:t+group]);assert mass<1<<63
                if k<=1<<(15-span):assert sum(map(abs,products))<1<<63
        rows.append({"stage":stage,"shape":[n,k,out],"counts":dict(count),"native_bias_inclusive_span_histogram":dict(spans),"max_safe_group_up_to16_histogram":dict(blocks)})
    cells=[];seed=27061001
    for profile in ["typical","scale","boundary"]:
        T,C=m.dims(seed,profile)
        for kind in ["normal","wide","sparse"]:
            mark=len(rows);x=f.gen(kind,T*C,seed+999);saved=x
            x=f.norm(x,T,C,f.scale(seed+1,C),f.bias(seed,2,C));a=f.weights(kind,seed,3,T,T*T)
            # GEMM represented as row-major W columns for this census only.
            wx=[x[t*C+j] for j in range(C) for t in range(T)]
            observe("gemm",a,wx,[0]*C,T,T,C)
            x=m.add(m.gemm(a,x,T,T,C),saved);saved=x
            x=f.norm(x,T,C,f.scale(seed+4,C),f.bias(seed,5,C))
            w=f.weights(kind,seed,6,C,2*C*C);b=f.bias(seed,7,2*C);observe("linear1",x,w,b,T,C,2*C)
            x=f.linear(x,T,C,2*C,w,b,True)
            w=f.weights(kind,seed,8,2*C,2*C*C);b=f.bias(seed,9,C);observe("linear2",x,w,b,T,2*C,C)
            x=m.add(f.linear(x,T,2*C,C,w,b,False),saved)
            w=f.weights(kind,seed,10,T*C,10*T*C);b=f.bias(seed,11,10);observe("classifier",x,w,b,1,T*C,10)
            x=f.linear(x,1,T*C,10,w,b,False)
            digest=hashlib.sha256(b"".join(struct.pack("<I",v) for v in x)).hexdigest()
            assert digest==expected[(seed,profile,kind)]
            cells.append({"seed":seed,"profile":profile,"kind":kind,"T":T,"C":C,"stages":rows[mark:],"output_sha256":digest,"old_seen_hash_matched":True})
    total=Counter();stage_counts={}
    for row in rows:
        total.update(row["counts"]);stage_counts.setdefault(row["stage"],Counter()).update(row["counts"])
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-start,"status":"OLD_SEEN_FINITE_FORMULA_NATIVE_GUARD_CENSUS_NOT_SPEED_OR_LEAN",
         "seed":seed,"cells":cells,"totals":dict(total),"stage_totals":{k:dict(v) for k,v in stage_counts.items()},
         "source36_sha256":"595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b",
         "formula":"nativeMD product abs<2^(48+span); group<=2^(15-span) guarantees groupmass<2^63; whole64 only if k<=2^(15-span); final bias still existing YL exact192 path",
         "negative_history":"R27 block16 on public23 had a different prepared P/I interface and mixed whole-model outcomes; do not assume source36 scope/cost or proof transfers. This buys coverage evidence before any new implementation.",
         "boundaries":["Counts weighted by logicalMACs only, not walltime or production score","one oldseen sample percell, no fresh confirmation data","original all12/newsource gate/native64 implementation absent","time20s asserted only at each stage, not externalhardkill; actualwall reported"]}
    (HERE/"MIXER36-BLOCK-CENSUS.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"cells":len(cells),"wall_seconds":out["wall_seconds"],"totals":out["totals"],"stages":out["stage_totals"]}))
if __name__=="__main__":main()
