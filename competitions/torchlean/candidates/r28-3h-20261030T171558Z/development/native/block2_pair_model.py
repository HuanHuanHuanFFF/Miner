"""Finite exact-word replay of the new MD2 block2 branch on old Mixer cells."""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import hashlib,importlib.util,json,struct,sys,time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
R27=ROUND.parent/"r27-5h-20261029T194443Z/research/board-frontier"
MASK=(1<<64)-1;C=1<<62
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def step(h,l,p):
    low=(l+p)&MASK
    return (h-(p>>63)+(low<l))&MASK,low
def signed(p):return p if p<1<<63 else p-(1<<64)
def main():
    began=time.monotonic();f=load(R27/"norm_frontier.py","r28_block2_wordmodel");sys.modules["norm_frontier"]=f
    m=load(R27/"mixer_frontier.py","r28_block2_mixermodel")
    yc=load(HERE/"mixer36_block_census.py","r28_block2_metadata").yc
    expected={(r["seed"],r["profile"],r["kind"]):r["output_sha256"] for r in json.loads((R27/"mixer-frontier-result.json").read_text())["cells"]}
    total=Counter();stages=[];cells=[]
    def encode(w,base):
        sign,mant,index=f.fields(w);v=(mant<<((index-base)&63))&MASK
        return (C+sign*v)&MASK
    def observe(stage,x,w,b,rows,k,out):
        assert time.monotonic()-began<20,"20 second lightweight model cap"
        count=Counter(dots=rows*out,logical_MACs=rows*k*out)
        xs=[x[i*k:(i+1)*k] for i in range(rows)];ws=[w[j*k:(j+1)*k] for j in range(out)]
        xm=list(map(yc,xs));wm=list(map(yc,ws))
        xp=[[encode(v,a[0]) for v in row] for row,a in zip(xs,xm)]
        wp=[[encode(v,a[0]) for v in row] for row,a in zip(ws,wm)]
        for i in range(0,rows-1,2):
            for j in range(out):
                z=wm[j];mb=f.fields(b[j])[1];ib=f.fields(b[j])[2]+126
                lows=[];spans=[]
                for a in [xm[i],xm[i+1]]:
                    lo=min(a[0]+z[0],ib) if mb else a[0]+z[0]
                    hi=max(a[1]+z[1],ib) if mb else a[1]+z[1]
                    lows.append(lo);spans.append(hi-lo)
                if not (xm[i][2] and xm[i+1][2] and z[2] and ((b[j]>>23)&255)!=255 and all(0<=s<=14 for s in spans)):continue
                count["block2_eligible_pair_dots"]+=1;count["block2_eligible_logical_MACs"]+=2*k
                for r,lo in zip([i,i+1],lows):
                    d=xm[r][0]+z[0]-lo;assert 0<=d<=14
                    products=[(((a-C)&MASK)*((v-C)&MASK)<<d)&MASK for a,v in zip(xp[r],wp[j])]
                    for t,p in enumerate(products):
                        sa,ma,ia=f.fields(xs[r][t]);sb,mv,iv=f.fields(ws[j][t])
                        exact=sa*sb*(ma*mv<<max(0,ia+iv-lo))
                        assert signed(p)==exact and -(1<<62)<=exact<(1<<62)
                    scalar=blocked=(0,0)
                    for p in products:scalar=step(*scalar,p)
                    for t in range(0,k,2):
                        block=products[t:t+2]
                        assert -(1<<63)<=sum(map(signed,block))<(1<<63)
                        blocked=step(*blocked,sum(block)&MASK)
                        count["block2_signed_merges"]+=1
                    assert scalar==blocked
                    count["exact_pair_accumulators_matched"]+=1
        total.update(count);stages.append({"stage":stage,"shape":[rows,k,out],"counts":dict(count)})
    seed=27061001
    for profile in ["typical","scale","boundary"]:
        T,W=m.dims(seed,profile)
        for kind in ["normal","wide","sparse"]:
            mark=len(stages);x=f.gen(kind,T*W,seed+999);saved=x
            x=f.norm(x,T,W,f.scale(seed+1,W),f.bias(seed,2,W));a=f.weights(kind,seed,3,T,T*T)
            x=m.add(m.gemm(a,x,T,T,W),saved);saved=x
            x=f.norm(x,T,W,f.scale(seed+4,W),f.bias(seed,5,W))
            w=f.weights(kind,seed,6,W,2*W*W);b=f.bias(seed,7,2*W);observe("linear1",x,w,b,T,W,2*W)
            x=f.linear(x,T,W,2*W,w,b,True)
            w=f.weights(kind,seed,8,2*W,2*W*W);b=f.bias(seed,9,W);observe("linear2",x,w,b,T,2*W,W)
            x=m.add(f.linear(x,T,2*W,W,w,b,False),saved)
            x=f.linear(x,1,T*W,10,f.weights(kind,seed,10,T*W,10*T*W),f.bias(seed,11,10),False)
            digest=hashlib.sha256(b"".join(struct.pack("<I",v) for v in x)).hexdigest();assert digest==expected[(seed,profile,kind)]
            cells.append({"seed":seed,"profile":profile,"kind":kind,"T":T,"C":W,"output_sha256":digest,"old_seen_hash_matched":True,"stages":stages[mark:]})
    prototype=json.loads((HERE/"mixer36-block2-cost-receipt.json").read_text())
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-began,"state":"OLD_SEEN_FINITE_WORD_ACCUMULATOR_MODEL_ONLY", "prototype_sha256":prototype["candidate_sha256"],
         "totals":dict(total),"cells":cells,"scope":"New branch only exact source36 paired linears; original classifier/GEMM/norm/add unchanged; loop pair128 accumulator matched before identical original bias/round/fallback",
         "boundary":"Not Lean, all12, generated-native, output parity of new executable, current champion or runtime cost. Root no extraCI request; use only if a high-upside cost discriminator fits priority."}
    (HERE/"BLOCK2-PAIR-MODEL.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({"wall_seconds":out["wall_seconds"],"cells":len(cells),"totals":out["totals"]}))
if __name__=="__main__":main()
