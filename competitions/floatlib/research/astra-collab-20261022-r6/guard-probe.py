from pathlib import Path
from datetime import datetime, timezone
import random,json,hashlib
HERE=Path(__file__).resolve().parent
def normal(u): return (((u&0x7fffffff)-0x0c000000)&0xffffffff)<0x73800000
def fast(u):
    a=u&0x7fffffff
    return ((a-1)&0xffffffff)>=0x0bffffff and a<0x7f800000
r=random.Random(2026102206)
words=set(r.getrandbits(32) for _ in range(100000))
for e in range(256):
    for sign in (0,0x80000000):
        for f in (0,1,2,3,0x3fffff,0x400000,0x7ffffd,0x7ffffe,0x7fffff):
            words.add(sign|(e<<23)|f)
for u in words:
    assert normal(u)==(24<=((u>>23)&255)<=254)
    assert not fast(u) or ((u>>23)&255)!=255
    assert not normal(u) or fast(u)
out={'status':'PASS_FINITE_GUARD_DIAGNOSTIC_ONLY','count':len(words),'seed':2026102206,'scope':'Interval equivalence and finite implication on specified words. No floating arithmetic or Lean acceptance claim.','trace_sha256':hashlib.sha256(b''.join(x.to_bytes(4,'little') for x in sorted(words))).hexdigest(),'official_bench_sha256':hashlib.sha256((HERE/'upstream/Bench.lean').read_bytes()).hexdigest(),'analytic_timed_exponent_ranges':{'add:near-one':[124,130],'add:wide-gap':[96,127],'add:cancel':[127,127]},'timed_add_guard_coverage':'ALL_BY_GENERATOR_EXPONENT_RANGE','completed_at_utc':datetime.now(timezone.utc).isoformat()}
(HERE/'guard-probe.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
