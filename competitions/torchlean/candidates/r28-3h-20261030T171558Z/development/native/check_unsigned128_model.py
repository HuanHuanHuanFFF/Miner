"""Finite disproof check for unsigned128 affine correction carry/borrow helpers."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random,time
HERE=Path(__file__).resolve().parent;M=(1<<64)-1;M128=(1<<128)-1
def add(h,l,a,b):
    low=(l+b)&M
    return (h+a+(low<l))&M,low
def sub(h,l,a,b):return (h-a-(l<b))&M,(l-b)&M
def pair(h,l):return (h<<64)+l
def main():
    started=time.monotonic();rng=random.Random(0x2836128);edges=[0,1,2,(1<<63)-1,1<<63,M-1,M]
    missing_borrow=missing_carry=0
    for t in range(40000):
        h,l,a,b=[rng.getrandbits(64) for _ in range(4)]
        if t<49:l,b=edges[t//7],edges[t%7]
        assert pair(*add(h,l,a,b))==(pair(h,l)+pair(a,b))&M128
        assert pair(*sub(h,l,a,b))==(pair(h,l)-pair(a,b))&M128
        missing_borrow+=pair((h-a)&M,(l-b)&M)!=((pair(h,l)-pair(a,b))&M128)
        missing_carry+=pair((h+a)&M,(l+b)&M)!=((pair(h,l)+pair(a,b))&M128)
    for s in range(64):
        for v in edges+[rng.getrandbits(64) for _ in range(50)]:
            low=(v<<s)&M;high=0 if s==0 else v>>(64-s)
            assert pair(high,low)==v<<s
    files=[HERE/"Unsigned128Arithmetic.lean",HERE/"Shift64Pair.lean.inc"]
    counterexamples=[
        {"case":"missingunsignedcarry","h":"0000000000000000","l":"ffffffffffffffff","a":"0000000000000000","b":"0000000000000001","expected":"00000000000000010000000000000000","withoutcarry":"00000000000000000000000000000000"},
        {"case":"missingunsignedborrow","h":"0000000000000000","l":"0000000000000000","a":"0000000000000000","b":"0000000000000001","expected":"ffffffffffffffffffffffffffffffff","withoutborrow":"0000000000000000ffffffffffffffff"},
        {"case":"missingzeroshiiftbranch","value":"0000000000000001","shift":0,"expected":"00000000000000000000000000000001","usingmasked64minusshift":"00000000000000010000000000000001"}
    ]
    assert pair(*add(0,M,0,1))==1<<64
    assert pair(*sub(0,0,0,1))==M128
    assert pair(1>>((64-0)&63),1)==(1<<64)+1
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-started,"state":"FINITE_WORD_FALSIFICATION_NO_LEAN_OR_NATIVE","cases":40000,
         "missing_borrow_counterexamples":missing_borrow,"missing_carry_counterexamples":missing_carry,"shifts_including_zero_and63":3648,
         "helpers":[{"path":p.name,"sha256":hashlib.sha256(p.read_bytes()).hexdigest(),"bytes":p.stat().st_size}for p in files],
         "directed_raw_counterexamples":counterexamples,
         "use":"Potential complementary interface for crosssourceC centered64 terminal affinecorrection; no duplicateconfidence for alreadyexisting unsigned128_step or affineidentity",
         "boundary":"Uncompiledproofdrafts only. Exact index/cacheproducer/correctionorder/globalbound/oldYLbias/sentinel/newall12 remainOPEN. NoextraCIrequest."}
    (HERE/"UNSIGNED128-HELPERS-MODEL.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["cases","missing_borrow_counterexamples","missing_carry_counterexamples","wall_seconds"]}))
if __name__=="__main__":main()
