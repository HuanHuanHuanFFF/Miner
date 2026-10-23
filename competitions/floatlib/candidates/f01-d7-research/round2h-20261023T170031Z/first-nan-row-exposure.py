"""Counts on already-executed inputs only; no runtime or performance prediction."""
from pathlib import Path
import ast, datetime, hashlib, json

root=Path(__file__).resolve().parents[5]
out=Path(__file__).resolve().parent
generator=root/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
tree=ast.parse(generator.read_bytes())
nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('word','ctz','element')]
ns={'M64':(1<<64)-1,'M32':(1<<32)-1}
exec(compile(ast.Module(body=nodes,type_ignores=[]),str(generator),'exec'),ns)
runs=[]
for rid in (39944891642,39946600549,39992610090):
    run=root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(rid)
    index=json.loads((run/'original-artifact-hashes.json').read_bytes())
    plan=run/index['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
    data=json.loads(plan.read_bytes()); rows=[]
    for c in data['cases']:
        if c['kernel']!='bmm' or not c['timed']:continue
        batch,m,n,p=(c[k] for k in ('batch','m','n','p'))
        hits=0
        if n:
            for r in range(batch*m):
                bits=ns['element'](c,r*n,0,n)
                hits+=int(bits & 0x7fffffff > 0x7f800000)
        rows.append({'case':c['name'],'shape':[batch,m,n,p],'route':'DIRECT' if n<=4 or p<=2 else 'PACKED',
                     'rows':batch*m,'first_A_nan_rows':hits,'affected_outputs':hits*p,
                     'full_mac_work':batch*m*n*p,'native_suffix_MACs_avoidable':hits*p*max(0,n-1)})
    runs.append({'run':rid,'seed':data.get('seed'),'drawn_plan_sha256':hashlib.sha256(plan.read_bytes()).hexdigest(),
                 'totals':{k:sum(c[k] for c in rows) for k in ('rows','first_A_nan_rows','affected_outputs','full_mac_work','native_suffix_MACs_avoidable')},'cases':rows})
result={'as_of_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'INFERRED_SOURCE_GENERATOR_COUNTS',
        'generator_transcription_sha256':hashlib.sha256(generator.read_bytes()).hexdigest(),
        'scope':'Already exposed executed plans only. Counts exclude map/pack/output, branch and exact replay costs; not a speedup estimate. replayEarly must still receive original per-column B to preserve signaling NaN priority.',
        'runs':runs}
(out/'first-nan-row-exposure.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps([{k:v for k,v in r.items() if k!='cases'} for r in runs]))
