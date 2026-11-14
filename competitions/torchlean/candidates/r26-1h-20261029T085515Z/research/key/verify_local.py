from pathlib import Path
import json,hashlib,re,ast
from datetime import datetime,timezone
H=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key')
P=Path('competitions/torchlean/candidates/r25-90m-20261029T064916Z/development/contract-port/policy-source')
expected={'sandbox.py':'13c4f7b71e678a27d024613e5198e0d75667de4e','duplicates.py':'3e8eb21d1a50cce44090e29a816e3b55c0ad3fd9'}
for n,sha in expected.items():
 b=(P/n).read_bytes();assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()==sha
D={};exec(compile((P/'duplicates.py').read_text(encoding='utf-8'),'pinned_duplicates','exec'),D)
t=ast.parse((P/'sandbox.py').read_text(encoding='utf-8'));names={'_MAX_BYTES','OPTIONS','ATTRIBUTES','BANNED','GLOBAL'};funcs={'intake','policy','global_declarations','options'}
sel=[n for n in t.body if (isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id in names for x in n.targets)) or (isinstance(n,ast.FunctionDef) and n.name in funcs)]
ns={'Path':Path,'Verdict':object,'re':re,'normalized':D['normalized']};exec(compile(ast.Module(body=sel,type_ignores=[]),'pinned_policy','exec'),ns)
rows=[]
for p in sorted(H.rglob('*.lean')):
 raw=p.read_bytes();src=raw.decode('utf-8-sig');rows.append(dict(path=p.relative_to(H).as_posix(),bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest(),intake=ns['intake'](p,None),policy=ns['policy'](p,None),imports=re.findall(r'^import\s+(.+)$',src,re.M),placeholder_count=len(re.findall(r'\b(sorry|admit|axiom)\b',src))))
result=dict(at_utc=datetime.now(timezone.utc).isoformat(),sources=expected,checks=rows,proof='NOT_RUN',axioms='NOT_RUN',native='NOT_RUN',local_Lean=False)
(H/'local-preflight.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8');print(json.dumps(result,indent=2))
p=H/'HANDOFF.md';t=p.read_text(encoding='utf-8-sig').replace('09:17 可选','可选').replace('7801/16270/24405B','7805/16274/24409B');p.write_text(t,encoding='utf-8',newline='\n')
