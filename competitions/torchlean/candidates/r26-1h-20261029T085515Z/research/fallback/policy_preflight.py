from pathlib import Path
import ast, datetime, hashlib, json, re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
P = HERE.parents[2] / 'r25-90m-20261029T064916Z' / 'development' / 'contract-port' / 'policy-source'
d = {}
exec(compile((P/'duplicates.py').read_text(encoding='utf-8'), 'pinned_duplicates', 'exec'), d)
t = ast.parse((P/'sandbox.py').read_text(encoding='utf-8'))
names={'_MAX_BYTES','OPTIONS','ATTRIBUTES','BANNED','GLOBAL'}
funcs={'intake','policy','global_declarations','options'}
sel=[n for n in t.body if (isinstance(n,ast.Assign) and
     any(isinstance(x,ast.Name) and x.id in names for x in n.targets)) or
     (isinstance(n,ast.FunctionDef) and n.name in funcs)]
ns={'Path':Path,'Verdict':object,'re':re,'normalized':d['normalized']}
exec(compile(ast.Module(body=sel,type_ignores=[]),'pinned_policy','exec'),ns)
rows=[]
for name in ('WordBlockRuntime.lean','WordBlockCarrier-v1.lean','WordBlockCarrier.lean',
             'WordBlockExtended.lean','WordBlockComplete.lean','WideBandRuntime.lean',
             'WordBlockStaticV2.lean','WordBlockTwoChains.lean'):
    p=HERE/name
    rows.append({'file':name,'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),
                 'bytes':p.stat().st_size,'intake':ns['intake'](p,None),
                 'policy':ns['policy'](p,None)})
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest()
                         for p in (P/'duplicates.py',P/'sandbox.py')},
        'scope':'Pinned original intake/policy AST only; no Lean compile, replay or timing.',
        'results':rows}
(HERE/'policy-preflight.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
