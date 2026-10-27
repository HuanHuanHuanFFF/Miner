from pathlib import Path
import ast, re, json, hashlib, argparse
from datetime import datetime, timezone
ROOT=Path(__file__).resolve().parents[4]
HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--candidate',action='append');ap.add_argument('--output',default='policy-precheck.json');args=ap.parse_args()
gate=HERE/'upstream/gate-4b7e838.py'
assert hashlib.sha256(gate.read_bytes()).hexdigest()=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text())
node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
banned=re.compile(ast.literal_eval(node.value.args[0]))
def literal_assignment(name):
    n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
    return ast.literal_eval(n.value)
official_options=literal_assignment('OPTIONS')
official_attributes=literal_assignment('ATTRIBUTES')
# The original pure options function is loaded unchanged; no gate/build/remote code executes.
options_node=next(n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name=='options')
options_env={'re':re,'OPTIONS':official_options}
exec(compile(ast.Module(body=[options_node],type_ignores=[]),str(gate),'exec'),options_env)
results=[]
for p in sorted((ROOT/'competitions/floatlib/candidates').glob('f01-r7-*/Kernel.lean')):
    if args.candidate and p.parent.name not in args.candidate:continue
    b=p.read_bytes(); s=b.decode(); m=json.loads(p.with_name('manifest.json').read_text())
    assert hashlib.sha256(b).hexdigest()==m['candidate_sha256']
    assert len(b)==m['candidate_bytes'] and len(b)<=256000
    match=banned.search(s)
    assert match is None, (p,match.group())
    assert [x for x in s.splitlines() if re.search(r'\bimport\b',x)]==['import ContractTensor']
    reason=options_env['options'](s)
    assert reason is None,(p,reason)
    for attrs in re.findall(r'@\[([^\]]*)\]',s):
        for a in attrs.split(','):
            name=a.split()[-1] if a.split() else ''
            assert name in official_attributes,(p,'attribute',a)
    results.append({'candidate':p.parent.name,'sha256':m['candidate_sha256'],'bytes':len(b),'status':'PASS_HASH_SIZE_IMPORT_BANNED_OPTIONS_ATTRIBUTES_STATIC_ONLY','lean':'NOT_RUN_UNLESS_SEPARATE_CI_EVIDENCE'})
assert results, 'No selected candidate found'
if args.candidate:assert {r['candidate'] for r in results}==set(args.candidate)
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'official_commit':'4b7e83841cc0c32c6529f533923c73d33b5ecf97','official_gate_sha256':hashlib.sha256(gate.read_bytes()).hexdigest(),'candidates':results}
target=HERE/args.output;assert target.resolve().is_relative_to(HERE.resolve())
target.write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
