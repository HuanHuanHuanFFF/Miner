"""Run the exact pinned official intake/policy/options AST, without importing the gate."""
from pathlib import Path
from types import SimpleNamespace
import argparse, ast, hashlib, json, re

ROOT = next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE = Path(__file__).resolve().parent
source = ROOT/'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw'
raw = source.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree = ast.parse(raw)
names = {'OPTIONS','ATTRIBUTES','BANNED'}
nodes = [n for n in tree.body if isinstance(n,ast.Assign) and
    any(isinstance(t,ast.Name) and t.id in names for t in n.targets)]
nodes += [n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in {'intake','policy','options'}]
assert len(nodes) == 6
env = {'Path':Path,'Verdict':SimpleNamespace,'re':re,'_MAX_BYTES':256000,
       'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
exec(compile(ast.Module(body=nodes,type_ignores=[]),str(source),'exec'),env)
ap=argparse.ArgumentParser()
ap.add_argument('candidates',nargs='+')
ap.add_argument('--output',required=True)
args=ap.parse_args()
results=[]
for name in args.candidates:
    path=ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean'
    reason=env['intake'](path,SimpleNamespace(slot='full'))
    if reason is None: reason=env['policy'](path,SimpleNamespace(slot='full'))
    results.append({'candidate':name,'sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
                    'reason':reason,'policy_pass':reason is None})
record={'official_gate_sha256':hashlib.sha256(raw).hexdigest(),
    'exact_ast_nodes':[getattr(n,'name',n.targets[0].id if isinstance(n,ast.Assign) else None) for n in nodes],
    'scope':'Exact original Python intake/policy/options only; no toolchain, altered policy, Lean acceptance or performance.',
    'results':results}
Path(args.output).write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,ensure_ascii=False))
