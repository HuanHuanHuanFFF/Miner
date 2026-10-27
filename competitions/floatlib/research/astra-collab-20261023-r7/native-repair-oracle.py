from pathlib import Path
from datetime import datetime,timezone
import runpy,hashlib,json,random
HERE=Path(__file__).resolve().parent
o=runpy.run_path(str(HERE/'nonfinite-oracle.py'),run_name='source_oracle')
add,mul,nan,snan,native,dot=[o[x] for x in ['add','mul','nan','snan','native_model','dot']]
def replay(a,b):
    acc=0;steps=0
    for k,(x,y) in enumerate(zip(a,b)):
        steps+=1
        nxt=native(add,acc,native(mul,x,y))
        if not nan(nxt):acc=nxt;continue
        repaired=add(acc,mul(x,y))
        if nan(repaired) and not snan(repaired):return repaired,steps,1,0
        for x2,y2 in zip(a[k+1:],b[k+1:]):repaired=add(repaired,mul(x2,y2))
        return repaired,steps,1,len(a)-k-1
    return acc,steps,0,0
r=random.Random(2026102302);trace=hashlib.sha256();counts={'traces':0,'native_prefix_steps':0,'exact_repair_steps':0,'exact_cold_suffix_steps':0,'full_dot_steps':0}
pool=[0,0x80000000,1,0x80000001,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc00001,0xffc12345,0x7f854321,0xff800002]
for n in [0,1,2,3,8,32,128]:
    for _ in range(800):
        a=[r.choice(pool) if r.randrange(3)==0 else r.getrandbits(32) for _ in range(n)]
        b=[r.choice(pool) if r.randrange(3)==0 else r.getrandbits(32) for _ in range(n)]
        exact=dot(a,b);got,ns,rs,cs=replay(a,b);assert got==exact
        counts['traces']+=1;counts['native_prefix_steps']+=ns;counts['exact_repair_steps']+=rs;counts['exact_cold_suffix_steps']+=cs;counts['full_dot_steps']+=n
        trace.update(got.to_bytes(4,'little')+n.to_bytes(4,'little'))
out={'status':'PASS_FINITE_SOURCE_DERIVED_WORD_MODEL','completed_at_utc':datetime.now(timezone.utc).isoformat(),'seed':2026102302,'counts':counts,'trace_sha256':trace.hexdigest(),'oracle_source_sha256':hashlib.sha256((HERE/'nonfinite-oracle.py').read_bytes()).hexdigest(),'scope':'Prepared native-prefix/exact-event repair model only; not actual Float32/Lean runtime, not a timing or prevalence estimate. Cold suffix branch retained even though test count may be zero. First full native pass/preparation is not included in these operation counts.'}
(HERE/'native-repair-oracle.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
