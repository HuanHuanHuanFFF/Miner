"""Finite exposed-input and fence tests for normal large-gap absorption."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
from itertools import product
import ast
import importlib.util
import json
import random

base=Path(__file__).resolve().parent; root=base.parents[4]
start,budget,max_pairs=monotonic(),3.0,14000

def functions(path,names,constants):
    tree=ast.parse(path.read_bytes())
    nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in names
           or isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id in constants for t in n.targets)]
    env={}; exec(compile(ast.Module(body=nodes,type_ignores=[]),str(path),'exec'),env); return env

gen=root/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
partner=root/'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity.py'
oracle_path=gen.with_name('nonfinite-oracle.py')
spec=importlib.util.spec_from_file_location('r14_widegap_oracle',oracle_path)
oracle=importlib.util.module_from_spec(spec); spec.loader.exec_module(oracle)
g=functions(gen,{'word','ctz','element'},{'M32','M64'})
s=functions(partner,{'partner'},{'M32'})
run=root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357'
idx=json.loads((run/'original-artifact-hashes.json').read_bytes())
plan_path=run/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
plan=json.loads(plan_path.read_bytes()); rng=random.Random(202610250030)
rows,total,accepted=[],0,0
for c in plan['cases']:
    if c['kernel']!='add' or not c['timed']: continue
    length=c['work']; size=min(length,256)
    positions=list(range(length)) if length<=size else [0,length-1]+rng.sample(range(1,length-1),size-2)
    counts=dict(gap_ge26=0,extended_gap25=0)
    fixed=g['element'](c,0,1,31)
    for i in positions:
        total+=1; assert total<=max_pairs and monotonic()-start<budget
        a=g['element'](c,i,0,31); b=s['partner'](c,i,a,g['element'],g['word'],fixed)
        ea,eb=(a>>23)&255,(b>>23)&255
        if not(1<=ea<=254 and 1<=eb<=254): continue
        d=abs(ea-eb); hi,lo=(a,b) if ea>=eb else (b,a)
        broad=d>=26
        extended=d==25 and (((a^b)>>31)==0 or (hi&0x7fffff)!=0 or (lo&0x7fffff)==0)
        counts['gap_ge26']+=broad; counts['extended_gap25']+=extended
        if broad or extended:
            assert oracle.add(a,b)==hi
            accepted+=1
    rows.append(dict(case=c['name'],work=length,samples=size,counts=counts))
fences=0
for eh,d,fh,fl,sh,sl in product([27,127,254],[25,26,31,63,126],
                               [0,1,0x7ffffe,0x7fffff],[0,1,0x7fffff],[0,1],[0,1]):
    if eh-d<1: continue
    a=(sh<<31)|(eh<<23)|fh; b=(sl<<31)|((eh-d)<<23)|fl
    allowed=d>=26 or d==25 and (sh==sl or fh!=0 or fl==0)
    if allowed:
        assert oracle.add(a,b)==a and oracle.add(b,a)==a
        fences+=1
    assert total+fences<=max_pairs and monotonic()-start<budget
counterexamples=[]
for a,b,removed in [(0x3f800000,0xb3000001,'opposite gap25 at power-of-two high with non-minimal low'),
                    (0x3f800001,0x33800000,'gap24 same sign and odd high mantissa at tie')]:
    got=oracle.add(a,b); assert got!=a
    counterexamples.append(dict(a=hex(a),b=hex(b),return_high=hex(a),actual_integer_oracle=hex(got),removed=removed))
weight=sum(r['work'] for r in rows)
fractions={k:sum(r['work']*r['counts'][k]/r['samples'] for r in rows)/weight for k in rows[0]['counts']}
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
            state='FINITE_MATHEMATICAL_OPPORTUNITY_ONLY',script_sha256=sha256(Path(__file__).read_bytes()).hexdigest(),
            plan_sha256=sha256(plan_path.read_bytes()).hexdigest(),oracle_sha256=sha256(oracle_path.read_bytes()).hexdigest(),
            run=40124283357,pairs=total,accepted_samples=accepted,fence_tests=fences,
            budget_seconds=budget,max_pairs=max_pairs,elapsed_seconds=monotonic()-start,
            work_weighted_input_fractions=fractions,counterexamples=counterexamples,cases=rows,
            scope='Exposed input generator plus own exact integer oracle, not pinned Lean/native/performance. No runtime variant, replacement of D priority, or CI request.')
Path(__file__).with_suffix('.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in record.items() if k!='cases'},indent=2))
