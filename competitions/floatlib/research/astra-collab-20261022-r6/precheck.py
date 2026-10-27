from pathlib import Path
import ast, re, json, hashlib
from datetime import datetime, timezone
ROOT=Path(__file__).resolve().parents[4]
HERE=Path(__file__).resolve().parent
gate=ROOT/'competitions/floatlib/research/materials/20261022/R2-W01c/FloatLib_R2-W01c/public_sources/official/gate.py'
tree=ast.parse(gate.read_text())
node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
banned=re.compile(ast.literal_eval(node.value.args[0]))
results=[]
for p in sorted((ROOT/'competitions/floatlib/candidates').glob('f01-r6-*/Kernel.lean')):
    b=p.read_bytes(); s=b.decode(); m=json.loads(p.with_name('manifest.json').read_text())
    assert hashlib.sha256(b).hexdigest()==m['candidate_sha256']
    assert len(b)==m['candidate_bytes'] and len(b)<=256000
    match=banned.search(s)
    assert match is None, (p,match.group())
    assert [x for x in s.splitlines() if re.search(r'\bimport\b',x)]==['import ContractTensor']
    results.append({'candidate':p.parent.name,'sha256':m['candidate_sha256'],'bytes':len(b),'status':'PASS_HASH_SIZE_IMPORT_BANNED_STATIC_ONLY','lean':'NOT_RUN_UNLESS_SEPARATE_CI_EVIDENCE'})
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'official_gate_sha256':hashlib.sha256(gate.read_bytes()).hexdigest(),'candidates':results}
(HERE/'policy-precheck.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
