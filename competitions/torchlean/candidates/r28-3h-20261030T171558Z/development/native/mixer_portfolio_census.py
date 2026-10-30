"""Old-seen full Mixer formula replay of precise prepare/singleton dispatch.

Preparation counts and native-dot eligibility only; no timing or new proof.
"""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import hashlib,importlib.util,json,struct,sys,time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
R27=ROUND.parent/"r27-5h-20261029T194443Z/research/board-frontier"
MASK64=(1<<64)-1
def load(path,name):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def main():
    started=time.monotonic();f=load(R27/"norm_frontier.py","r28_portfolio_model_norm");sys.modules["norm_frontier"]=f
    m=load(R27/"mixer_frontier.py","r28_portfolio_model_mixer");yc=load(HERE/"mixer36_block_census.py","r28_portfolio_model_metadata").yc
    expected={(r["seed"],r["profile"],r["kind"]):r["output_sha256"] for r in json.loads((R27/"mixer-frontier-result.json").read_text())["cells"]}
    stages=[];totals=Counter();cells=[]
    def observe(stage,x,w,b,rows,k,out):
        assert time.monotonic()-started<20,"20 second lightweight model cap"
        xm=[yc(x[i*k:(i+1)*k]) for i in range(rows)];wm=[yc(w[j*k:(j+1)*k]) for j in range(out)]
        count=Counter(calls=1,logical_MACs=rows*k*out)
        native=[]
        for i,a in enumerate(xm):
            for j,z in enumerate(wm):
                mb=f.fields(b[j])[1];ib=f.fields(b[j])[2]+126
                lo=min(a[0]+z[0],ib) if mb else a[0]+z[0]
                hi=max(a[1]+z[1],ib) if mb else a[1]+z[1]
                hit=a[2] and z[2] and ((b[j]>>23)&255)!=255 and 0<=hi-lo<=15
                native.append(hit)
        any_input=any(((hi-lo)&MASK64)<=15 for lo,hi,finite in xm)
        singleton=rows==1 and 64<=k
        pair_base=2<=rows and 0<k and k<1048576
        unfiltered=(pair_base or singleton) and 0<k and k<1048576
        exact_probe=any(native) if rows==1 else True
        admitted=unfiltered and any_input and exact_probe
        prep=(rows+out)*k
        count["pairlinear_control_prepared_words"]+=prep if pair_base else 0
        count["unfiltered_singleton_prepared_words"]+=prep if unfiltered else 0
        count["portfolio_prepared_words"]+=prep if admitted else 0
        count["avoided_vs_unfiltered_singleton_words"]+=prep if unfiltered and not admitted else 0
        count["new_singleton_fast_calls"]+=int(singleton and admitted)
        count["new_singleton_rejected_calls"]+=int(singleton and not admitted)
        count["metadata_eligible_dots"]+=sum(native)
        count["metadata_eligible_MACs"]+=sum(native)*k
        totals.update(count)
        stages.append({"stage":stage,"shape":[rows,k,out],"input_any_narrow":any_input,"precise_singleton_probe":exact_probe,"portfolio_admitted":admitted,"counts":dict(count)})
    seed=27061001
    for profile in ["typical","scale","boundary"]:
        T,C=m.dims(seed,profile)
        for kind in ["normal","wide","sparse"]:
            mark=len(stages);x=f.gen(kind,T*C,seed+999);saved=x
            x=f.norm(x,T,C,f.scale(seed+1,C),f.bias(seed,2,C));a=f.weights(kind,seed,3,T,T*T)
            wp=[x[t*C+j] for j in range(C) for t in range(T)]
            observe("token_gemm_as_pairlinear",a,wp,[0]*C,T,T,C)
            x=m.add(m.gemm(a,x,T,T,C),saved);saved=x
            x=f.norm(x,T,C,f.scale(seed+4,C),f.bias(seed,5,C))
            w=f.weights(kind,seed,6,C,2*C*C);b=f.bias(seed,7,2*C);observe("linear1",x,w,b,T,C,2*C)
            x=f.linear(x,T,C,2*C,w,b,True)
            w=f.weights(kind,seed,8,2*C,2*C*C);b=f.bias(seed,9,C);observe("linear2",x,w,b,T,2*C,C)
            x=m.add(f.linear(x,T,2*C,C,w,b,False),saved)
            w=f.weights(kind,seed,10,T*C,10*T*C);b=f.bias(seed,11,10);observe("classifier",x,w,b,1,T*C,10)
            x=f.linear(x,1,T*C,10,w,b,False)
            digest=hashlib.sha256(b"".join(struct.pack("<I",v) for v in x)).hexdigest();assert digest==expected[(seed,profile,kind)]
            cells.append({"seed":seed,"profile":profile,"kind":kind,"T":T,"C":C,"old_seen_output_hash":digest,"stages":stages[mark:]})
    candidate=json.loads((HERE/"mixer36-portfolio-receipt.json").read_text())
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-started,"state":"OLD_SEEN_MODEL_ONLY_NO_NATIVE_OR_LEAN","candidate_sha256":candidate["candidate_sha256"],"totals":dict(totals),"cells":cells,
         "boundary":"All9referenceformula hashes match oldseen record. Newprogram output not executed. Norm26 changes exact algorithm availability but reference mathematical output remains same. Wordprep/eligibleMAC counts are not elapsedcost.",
         "decision":"Use precise native-dot singleton probe to avoid cache build for cells with zero admitted classifier outputs; preserve original dispatch and newcandidate proof/gate boundary. All producer/fallback cost stays inside measurement."}
    (HERE/"MIXER-PORTFOLIO-CENSUS.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"cells":len(cells),"wall_seconds":out["wall_seconds"],"totals":out["totals"]}))
if __name__=="__main__":main()
