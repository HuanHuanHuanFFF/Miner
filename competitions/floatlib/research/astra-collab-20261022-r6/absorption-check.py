from pathlib import Path
from datetime import datetime,timezone
import ast,json,hashlib,random
HERE=Path(__file__).resolve().parent
old=HERE.parent/'astra-collab-20261022/web/R2-W02/original-extracted/FloatLib_R2-W02/diagnostics/diagnose_layout.py'
tree=ast.parse(old.read_text())
selected=ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ['unpack','rne_int','round_dyadic','add']],type_ignores=[])
ns={};exec(compile(selected,str(old),'exec'),ns)
oracle=ns['add']
def criterion(a,b):
    ea,eb=(a>>23)&255,(b>>23)&255
    if not(0<ea<255 and 0<eb<255):return False
    hi,lo=(a,b) if ea>=eb else (b,a)
    gap=abs(ea-eb)
    return gap>=26 or (gap>=25 and ((hi&0x7fffff)!=0 or ((hi^lo)>>31)==0))
trace=hashlib.sha256(); witnesses=[]; count=0;accepted=0;overflow_outside_guard=[]
fractions=(0,1,2,0x3fffff,0x400000,0x7ffffe,0x7fffff)
def check(a,b):
    global count,accepted
    ea,eb=(a>>23)&255,(b>>23)&255
    try:
        expected=oracle(a,b)
    except OverflowError:
        assert not criterion(a,b)
        overflow_outside_guard.append({'a':hex(a),'b':hex(b)})
        return
    hi=a if ea>=eb else b
    ok=criterion(a,b)
    if ok:assert expected==hi,(hex(a),hex(b),hex(expected));accepted+=1
    if abs(ea-eb)>=25 and expected!=hi and len(witnesses)<12:
        witnesses.append({'a':hex(a),'b':hex(b),'actual':hex(expected),'large':hex(hi),'gap':abs(ea-eb)})
    trace.update(a.to_bytes(4,'little')+b.to_bytes(4,'little')+expected.to_bytes(4,'little'));count+=1
for ehi in range(28,255):
    for gap in (24,25,26,27):
        for fhi in fractions:
            for flo in fractions:
                for signs in range(4):
                    check(((signs&1)<<31)|(ehi<<23)|fhi,((signs>>1)<<31)|((ehi-gap)<<23)|flo)
r=random.Random(2026102207)
for _ in range(30000):
    ehi=r.randrange(27,255);elo=r.randrange(1,ehi-24)
    check((r.randrange(2)<<31)|(ehi<<23)|r.getrandbits(23),(r.randrange(2)<<31)|(elo<<23)|r.getrandbits(23))
out={'status':'PASS_FINITE_EXACT_INTEGER_ORACLE','completed_at_utc':datetime.now(timezone.utc).isoformat(),'cases':count,'accepted_by_refined_criterion':accepted,'trace_sha256':trace.hexdigest(),'oracle_sha256':hashlib.sha256(old.read_bytes()).hexdigest(),'all_gap25_absorption':'FALSE_COUNTEREXAMPLES','gap25_counterexamples':witnesses,'overflow_outside_guard':overflow_outside_guard,'sufficient_criterion_under_test':'Both inputs finite normal; gap>=26, or gap>=25 and(larger fraction nonzero or same sign). Result is original larger word.','scope':'Finite oracle checks support boundary investigation, not an all-input proof, Lean gate or performance claim.','initial_probe_failure':'Initial finite-only oracle raised OverflowError on gap24 maximum-finite same-sign samples. Revision explicitly records them as outside the proposed sufficient guard and oracle domain; no claimed validation of their output.'}
(HERE/'absorption-check.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
