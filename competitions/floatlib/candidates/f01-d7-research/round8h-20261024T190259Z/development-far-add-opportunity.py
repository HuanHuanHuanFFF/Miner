"""Bounded opportunity check on exposed inputs, before any far-add runtime work."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import random
import struct
import time

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
def extract(path,names,constants=()):
    tree=ast.parse(path.read_bytes())
    nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in names or
           isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id in constants for t in n.targets)]
    env={}
    exec(compile(ast.Module(body=nodes,type_ignores=[]),str(path),'exec'),env)
    return env
generator=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
assert hashlib.sha256(generator.read_bytes()).hexdigest()=='28eb38c9388f595960ea039e18b5783984cb2a0b0cdb182011449a0cd146e7a1'
g=extract(generator,{'word','ctz','element'},{'M32','M64'})
partner=extract(ROOT/'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity.py',{'partner'},{'M32'})['partner']
base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357'
index=json.loads((base/'original-artifact-hashes.json').read_bytes())
plan_path=base/index['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
plan=json.loads(plan_path.read_bytes())
value=lambda word:struct.unpack('<f',struct.pack('<I',word))[0]
bits=lambda val:struct.unpack('<I',struct.pack('<f',val))[0]
rng=random.Random(202610242300)
rows=[];trace=hashlib.sha256();started=time.perf_counter()
for case in plan['cases']:
    if case['kernel']!='add' or not case['timed']:continue
    n=min(case['work'],256)
    positions=list(range(case['work'])) if n==case['work'] else [0,case['work']-1]+rng.sample(range(1,case['work']-1),n-2)
    fixed=g['element'](case,0,1,31)
    counts=dict(normal_far26=0,normal_narrow7=0,normal_mid8to25=0,normal_cancel_gap01=0,input_not_normal=0)
    for pos in positions:
        a=g['element'](case,pos,0,31)
        b=partner(case,pos,a,g['element'],g['word'],fixed)
        ea,eb=(a>>23)&255,(b>>23)&255
        if not (1<=ea<=254 and 1<=eb<=254):
            counts['input_not_normal']+=1;continue
        gap=abs(ea-eb)
        same=((a^b)>>31)==0
        if gap>=26:
            high=a if ea>=eb else b
            assert high==bits(value(a)+value(b)),(hex(a),hex(b),gap)
            counts['normal_far26']+=1
            trace.update(struct.pack('<III',a,b,high))
        elif gap<=7 and (same or gap>=2):counts['normal_narrow7']+=1
        elif gap<=1:counts['normal_cancel_gap01']+=1
        else:counts['normal_mid8to25']+=1
    rows.append(dict(case=case['name'],work=case['work'],samples=n,counts=counts))
    assert time.perf_counter()-started<5
work=sum(r['work'] for r in rows)
fractions={key:sum(r['work']*r['counts'][key]/r['samples'] for r in rows)/work for key in rows[0]['counts']}
a,b=0x3f800000,0x80000000|(102<<23)|0x7fffff
counterexample=dict(gap25=dict(a=hex(a),b=hex(b),incorrect_high=hex(a),actual=hex(bits(value(a)+value(b)))))
assert counterexample['gap25']['actual']!=hex(a)
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='EXPOSED_FINITE_DOMAIN_OPPORTUNITY_ONLY',run=40124283357,
            samples=sum(r['samples'] for r in rows),work_weighted_input_fractions=fractions,counterexample=counterexample,
            source_plan_sha256=hashlib.sha256(plan_path.read_bytes()).hexdigest(),script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
            trace_sha256=trace.hexdigest(),wall_seconds=time.perf_counter()-started,cases=rows,
            scope='Same exposed scalar input positions as narrow-domain screen; far branch only normal exponent gaps>=26. No new candidate, clean holdout, Lean proof, timing share or speedup result. A gap25 opposite-sign power-of-two counterexample is retained.')
destination=OUT/'development-far-add-opportunity.json'
assert not destination.exists()
destination.write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({k:v for k,v in record.items() if k!='cases'}))
