"""Old complete Mixer calls: native MD2 input double/single-zero coverage.

Explicitly distinct from the held shared-weight-B zero family. Uses only
previously seen R27 seeds and exact reference formula, never CI3/4 inputs.
"""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import hashlib,importlib.util,json,struct,sys,time,random
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
R27=ROUND.parent/"r27-5h-20261029T194443Z/research/board-frontier"
MASK=(1<<64)-1
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def step(h,l,p):
    low=(l+p)&MASK
    return (h-(p>>63)+(low<l))&MASK,low
def main():
    began=time.monotonic();f=load(R27/"norm_frontier.py","r28_inputzero_formula");sys.modules["norm_frontier"]=f
    m=load(R27/"mixer_frontier.py","r28_inputzero_mixer");yc=load(HERE/"mixer36_block_census.py","r28_inputzero_metadata").yc
    expected={(r["seed"],r["profile"],r["kind"]):r["output_sha256"]for r in json.loads((R27/"mixer-frontier-result.json").read_text())["cells"]}
    total=Counter();per_stage={};records=[];cells=[];context={}
    def observe(stage,x,w,b,rows,k,out):
        assert time.monotonic()-began<20,"20s lightweight model cap"
        count=Counter(calls=1,logical_MACs=rows*k*out)
        count["input_words"]+=len(x);count["input_zeros"]+=sum((v&0x7fffffff)==0 for v in x)
        if rows>=2:
            first=next((i for i,v in enumerate(x[:rows*k])if(v&0x7fffffff)==0),None)
            count["probe_words"]+=(first+1 if first is not None else rows*k)
            count["calls_select_zero_loop"]+=first is not None
            xm=[yc(x[i*k:(i+1)*k])for i in range(rows)];wm=[yc(w[j*k:(j+1)*k])for j in range(out)]
            for i in range(0,rows-1,2):
                for j,z in enumerate(wm):
                    admitted=True
                    for a in[xm[i],xm[i+1]]:
                        mb=f.fields(b[j])[1];ib=f.fields(b[j])[2]+126
                        lo=min(a[0]+z[0],ib)if mb else a[0]+z[0];hi=max(a[1]+z[1],ib)if mb else a[1]+z[1]
                        admitted &= a[2]and z[2]and((b[j]>>23)&255)!=255 and 0<=hi-lo<=15
                    if not admitted:continue
                    count["native_pair_terms"]+=k;count["native_base_products"]+=2*k
                    for t in range(k):
                        a=(x[i*k+t]&0x7fffffff)==0;bb=(x[(i+1)*k+t]&0x7fffffff)==0
                        count["both_zero_terms"]+=a and bb
                        count["only_row1_zero_terms"]+=a and not bb
                        count["only_row2_zero_terms"]+=bb and not a
                        count["neither_zero_terms"]+=not a and not bb
                        count["double_only_deleted_products"]+=2*(a and bb)
                        count["single_and_double_deleted_products"]+=a+bb
        total.update(count);per_stage.setdefault(stage,Counter()).update(count)
        records.append({**context,"stage":stage,"shape":[rows,k,out],"counts":dict(count)})
    for seed in[27061001,27161004]:
        for profile in["typical","scale","boundary"]:
            T,C=m.dims(seed,profile)
            for kind in["normal","wide","sparse"]:
                context.clear();context.update(seed=seed,profile=profile,kind=kind);mark=len(records)
                x=f.gen(kind,T*C,seed+999);saved=x
                x=f.norm(x,T,C,f.scale(seed+1,C),f.bias(seed,2,C));a=f.weights(kind,seed,3,T,T*T)
                x=m.add(m.gemm(a,x,T,T,C),saved);saved=x
                x=f.norm(x,T,C,f.scale(seed+4,C),f.bias(seed,5,C))
                w=f.weights(kind,seed,6,C,2*C*C);b=f.bias(seed,7,2*C);observe("linear1",x,w,b,T,C,2*C)
                x=f.linear(x,T,C,2*C,w,b,True)
                w=f.weights(kind,seed,8,2*C,2*C*C);b=f.bias(seed,9,C);observe("linear2_after_ReLU",x,w,b,T,2*C,C)
                x=m.add(f.linear(x,T,2*C,C,w,b,False),saved)
                w=f.weights(kind,seed,10,T*C,10*T*C);b=f.bias(seed,11,10);observe("classifier_not_MD2",x,w,b,1,T*C,10)
                x=f.linear(x,1,T*C,10,w,b,False)
                digest=hashlib.sha256(b"".join(struct.pack("<I",v)for v in x)).hexdigest();assert digest==expected[(seed,profile,kind)]
                cells.append({**context,"output_sha256":digest,"oldseen_hash_match":True,"stages":records[mark:]})
    rng=random.Random(0x283601);identity=0
    for i in range(16000):
        h1,l1,h2,l2,a,bb,w,d1,d2=[rng.getrandbits(64)for _ in range(9)]
        if i%4==0:a=bb=0
        elif i%4==1:a=0
        elif i%4==2:bb=0
        p1=(a*w<< (d1&63))&MASK;p2=(bb*w<<(d2&63))&MASK
        reference=step(h1,l1,p1)+step(h2,l2,p2)
        candidate=((h1,l1)if a==0 else step(h1,l1,p1))+((h2,l2)if bb==0 else step(h2,l2,p2))
        assert reference==candidate;identity+=1
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-began,"state":"OLD_SEEN_FULLFORMULA_AND_FINITE_WORD_MODEL_NOT_NATIVE_OR_LEAN","cells":cells,"totals":dict(total),"stage_totals":{k:dict(v)for k,v in per_stage.items()},"arbitrary_uint64_step_identities":identity,
         "mechanism":"Only prepared source36 MD2; singlezero skips one product/shift/carry, doublezero skips both and sharedWread. Per-call rawzero probe keeps dense nozero calls on original loop. No added cache/transpose/offset correction.",
         "bounds":"Counts only original bothrows-eligible nativebranch; classifier rows1 excluded. Probe input scans and branchprediction/register cost remain in wholemodel.","freeze":"Only oldseen seeds27061001/27161004; noCI3/4 input generation/confirmation access","comparison":"Bweightzero family is distinct but gains cannot be summed; no native speed/currentchampion probability inferred."}
    (HERE/"MIXER-INPUT-ZERO-CENSUS.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"cells":len(cells),"wall_seconds":out["wall_seconds"],"totals":out["totals"],"stages":out["stage_totals"]}))
if __name__=="__main__":main()
