#!/usr/bin/env python3
"""Original, bounded source recipe: keep source #11 portfolio, skip zero 3x3 terms.

The fetched base and generated whole sources stay local under ignored directories.
No compilation, benchmarking, network access, or Git mutation occurs here.
"""
import argparse
import hashlib
import json
from pathlib import Path

BASE_SHA = "ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3"
HERE = Path(__file__).resolve().parent
BASE = HERE.parents[1] / "competition-state" / "source-private" / "official-11.lean"

HELPER = """@[inline] def R28zeroPair (x w u:UInt64) (a:UInt64 × UInt64 × UInt64 × UInt64):UInt64 × UInt64 × UInt64 × UInt64 :=
 if x == 0x200000000000000 then a
 else (a.1+Y9 x w,a.2.1+cq1 x w,a.2.2.1+Y9 x u,a.2.2.2+cq1 x u)
lemma R28zeroPair_eq (x w u:UInt64) (a:UInt64 × UInt64 × UInt64 × UInt64):
 R28zeroPair x w u a=(a.1+Y9 x w,a.2.1+cq1 x w,a.2.2.1+Y9 x u,a.2.2.2+cq1 x u):=by
 by_cases h:x=0x200000000000000
 . subst x;simp [R28zeroPair,Y9,cq1]
 . simp [R28zeroPair,h]
"""

def apply(source: str) -> str:
    marker = "def Yt3g (s:ConvShape)"
    assert source.count(marker) == 1
    source = source.replace(marker, HELPER + marker)
    begin = source.index(marker)
    end = source.index("\ndef Yt3f", begin)
    body = source[begin:end]
    call = "  Yt3g s relu inp wts b k o P T W hw wp nc n f0 n0 h0 l0 C0 v0 f1 n1 h1 l1 C1 v1 j0 j20 hn hB hW hW2 hT hS acc acc2 p (c+1)"
    assert body.count(call) == 1
    lets = "  let z0:=R28zeroPair x0 w0 u0 (a0,a1,b0,b1)\n"
    lets += "".join(f"  let z{i}:=R28zeroPair x{i} w{i} u{i} z{i-1}\n" for i in range(1,9))
    body = body.replace(call, lets + call)
    terms=[]
    for acc,fn,wt in [("a0","Y9","w"),("a1","cq1","w"),("b0","Y9","u"),("b1","cq1","u")]:
        terms.append("("+acc+"".join(f"+{fn} x{i} {wt}{i}" for i in range(9))+")")
    old=" ".join(terms)
    assert body.count(old)==1
    body=body.replace(old,"z8.1 z8.2.1 z8.2.2.1 z8.2.2.2")
    source=source[:begin]+body+source[end:]
    old="   rw[Yt3g,dif_pos hc];dsimp only\n"
    assert source.count(old)==1
    source=source.replace(old,old+"   simp only [R28zeroPair_eq]\n")
    return source

def transform(raw: bytes, submission: int, variant: str) -> bytes:
    """Existing R28 runner adapter interface; reconstruction only."""
    assert submission == 11 and variant in ("zero-pair11", "r28-resnet-zero-pair11")
    assert hashlib.sha256(raw).hexdigest() == BASE_SHA
    result = apply(raw.decode("utf-8")).encode("utf-8")
    assert len(result) <= 256000
    return result

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--base",type=Path,default=BASE)
    ap.add_argument("--output",type=Path,default=HERE/"private"/"zero-pair11.lean")
    args=ap.parse_args()
    data=args.base.read_bytes()
    assert hashlib.sha256(data).hexdigest()==BASE_SHA,"wrong source base"
    result=apply(data.decode("utf-8")).encode("utf-8")
    assert len(result)<=256000,len(result)
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_bytes(result)
    receipt={"variant":"r28-resnet-zero-pair11", "base_sha256":BASE_SHA,
        "result_sha256":hashlib.sha256(result).hexdigest(),"bytes":len(result),
        "recipe_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "changes":"One new inline accumulator helper; replace only paired 3x3 accumulation and add its equality rewrite in existing proof.",
        "preserved":"All base entry points, guard domains, preparation, bias finalizer, fallback portfolio and all12 theorem statement.",
        "proof_state":"UNCOMPILED_SOURCE_PROOF; not full-gate acceptance",
        "performance_state":"UNKNOWN; potential tuple allocation, branch cost and compiler erasure require native discriminator"}
    (HERE/"zero-pair11-receipt.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(receipt,indent=2))

if __name__=="__main__": main()
