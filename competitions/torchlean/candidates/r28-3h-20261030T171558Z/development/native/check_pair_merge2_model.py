"""Falsify the conditional signed block merge identity before loop proofs."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random,time
HERE=Path(__file__).resolve().parent
MASK=(1<<64)-1
def signed(x):return x if x<1<<63 else x-(1<<64)
def step(h,l,p):
    z=(l+p)&MASK
    return (h-(p>>63)+(z<l))&MASK,z
def main():
    start=time.monotonic();rng=random.Random(0x2836);accepted=rejected=0;negative=0
    fixtures=[0,1,2,(1<<63)-1,1<<63,(1<<63)+1,MASK-1,MASK]
    for i in range(30000):
        h,l=rng.getrandbits(64),rng.getrandbits(64)
        p,q=(fixtures[(i//len(fixtures))%len(fixtures)],fixtures[i%len(fixtures)]) if i<64 else (rng.getrandbits(64),rng.getrandbits(64))
        total=signed(p)+signed(q)
        merged=step(h,l,(p+q)&MASK);separate=step(*step(h,l,p),q)
        if -(1<<63)<=total<1<<63:
            accepted+=1;assert merged==separate
        else:
            rejected+=1;negative+=merged!=separate
    helper=HERE/"WordPairMerge2.lean.inc"
    p,q=(1<<63)-1,1
    expected=step(*step(0,0,p),q);unconditional=step(0,0,(p+q)&MASK)
    assert expected!=unconditional
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-start,"seed":0x2836,"cases":30000,
         "guard_accepted":accepted,"guard_rejected":rejected,"counterexamples_without_guard":negative,
         "helper_sha256":hashlib.sha256(helper.read_bytes()).hexdigest(),"helper_bytes":helper.stat().st_size,
         "directed_missing_guard_counterexample":{"h":"0000000000000000","l":"0000000000000000","p":f"{p:016x}","q":f"{q:016x}","signedsum":1<<63,"expected_step_by_step":[f"{v:016x}"for v in expected],"wrong_unconditional_merge":[f"{v:016x}"for v in unconditional]},
         "status":"FINITE_FALSIFICATION_NO_LEAN_NO_NATIVE","finding":"Signed-mass guard is necessary: unguarded merged128 and scalar updates can differ by2^64 in high/low representation. Guarded cases all matched in this sample.",
         "integration":"Proposed helper after exactpublic36Z128. Need standalone Lean elaboration and original loop/metadata proof; no full candidate or speed evidence.",
         "cost":"MIXER36-BLOCK-CENSUS.json buys source36 workload coverage only. Do not request extraCI before a cost-meaningful integrated native route is selected."}
    (HERE/"PAIR-MERGE2-MODEL.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["cases","guard_accepted","guard_rejected","counterexamples_without_guard","wall_seconds"]}))
if __name__=="__main__":main()
