"""Exposed-input counts for mathematically constant normal-product edges."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import ast
import json
import random

base=Path(__file__).resolve().parent
root=base.parents[4]
start,budget,max_pairs=monotonic(),3.0,12000

def functions(path,names,constants):
    tree=ast.parse(path.read_bytes())
    nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in names
           or isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id in constants for t in n.targets)]
    env={}
    exec(compile(ast.Module(body=nodes,type_ignores=[]),str(path),'exec'),env)
    return env

gen=root/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
partner=root/'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity.py'
assert sha256(gen.read_bytes()).hexdigest()=='28eb38c9388f595960ea039e18b5783984cb2a0b0cdb182011449a0cd146e7a1'
g=functions(gen,{'word','ctz','element'},{'M32','M64'})
s=functions(partner,{'partner'},{'M32'})
run=root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357'
idx=json.loads((run/'original-artifact-hashes.json').read_bytes())
plan_path=run/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
plan=json.loads(plan_path.read_bytes())
rng=random.Random(202610250026)
rows,count=[],0
for c in plan['cases']:
    if c['kernel']!='mul' or not c['timed']:
        continue
    length=c['work']; size=min(length,256)
    positions=list(range(length)) if length<=size else [0,length-1]+rng.sample(range(1,length-1),size-2)
    counts=dict(non_normal_input=0,zero_sum_le102=0,low_sum103_127=0,
                existing_sum128_380=0,hinge_sum381=0,inf_sum_ge382=0)
    fixed=g['element'](c,0,1,31)
    for i in positions:
        count+=1
        assert count<=max_pairs and monotonic()-start<budget
        a=g['element'](c,i,0,31)
        b=s['partner'](c,i,a,g['element'],g['word'],fixed)
        ea,eb=(a>>23)&255,(b>>23)&255
        if not(1<=ea<=254 and 1<=eb<=254):
            key='non_normal_input'
        elif ea+eb<=102: key='zero_sum_le102'
        elif ea+eb<=127: key='low_sum103_127'
        elif ea+eb<=380: key='existing_sum128_380'
        elif ea+eb==381: key='hinge_sum381'
        else: key='inf_sum_ge382'
        counts[key]+=1
    rows.append(dict(case=c['name'],work=length,samples=size,counts=counts))
weight=sum(r['work'] for r in rows)
fractions={k:sum(r['work']*r['counts'][k]/r['samples'] for r in rows)/weight for k in rows[0]['counts']}
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
            state='INPUT_COUNTS_ONLY_NO_CANDIDATE',script_sha256=sha256(Path(__file__).read_bytes()).hexdigest(),
            plan_sha256=sha256(plan_path.read_bytes()).hexdigest(),run=40124283357,
            generator_sha256=sha256(gen.read_bytes()).hexdigest(),partner_sha256=sha256(partner.read_bytes()).hexdigest(),
            pairs=count,budget_seconds=budget,max_pairs=max_pairs,elapsed_seconds=monotonic()-start,
            work_weighted_input_fractions=fractions,cases=rows,
            mathematical_route='Normal inputs only: S<=102 produces signed zero; S>=382 produces signed infinity. Excludes non-normal inputs, does not change BMM native loop.',
            scope='Already exposed discovery inputs; no cost share, measured gain, all-input proof or new CI. Hinge103/381 deliberately excluded.')
Path(__file__).with_suffix('.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in record.items() if k!='cases'},indent=2))
