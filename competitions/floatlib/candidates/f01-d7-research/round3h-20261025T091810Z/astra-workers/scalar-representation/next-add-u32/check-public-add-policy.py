"""Run original fixed gate intake/policy/options functions only, including comment scan."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
GATE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert hashlib.sha256(GATE.read_bytes()).hexdigest()=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(GATE.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,
 'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
 n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(GATE),'exec'),env)
p=HERE/'Kernel-add-native-high-draft1.lean';v=SimpleNamespace(slot='full')
result={k:env[k](p,v) for k in ['intake','policy']}
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'gate_sha256':hashlib.sha256(GATE.read_bytes()).hexdigest(),
 'source_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'source_bytes':p.stat().st_size,
 'original_functions':list(result),'comment_text_included':True,'result':result,
 'state':'PASS_ORIGINAL_TEXT_POLICY_ONLY' if all(x is None for x in result.values()) else 'FAIL',
 'Lean_full_gate':'NOT_RUN'}
(HERE/'public-add-draft1-policy.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2));assert out['state'].startswith('PASS')
