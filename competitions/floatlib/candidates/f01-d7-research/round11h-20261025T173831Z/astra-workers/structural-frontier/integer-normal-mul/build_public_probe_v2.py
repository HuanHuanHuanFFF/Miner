"""Apply the shared observed-error repair to new math probes; keep every frozen source untouched."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import ast,hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
q=H.parent/'inline-u64-mul'
frozen=q/'probe-b2-v1/Probe-b2-u64-roundtrip-v1.lean';before=frozen.read_bytes()
assert sha(before)=='9f9a297e90f236c349283248cca9aa8f94c35ff24ebe9e26873e2c63d708a933'
shared=H.parent.parent/'numeric-roundtrip/repair2-manifest.json'
sm=json.loads(shared.read_text());assert sm['repair']['new']=='simpa only [Int.toNat_natCast] using (UInt32.toNat_ofNatClamp_of_lt hfit)'
old=b'simpa using (UInt64.toNat_ofNatClamp_of_lt hfit)'
new=b'simpa only [Int.toNat_natCast] using (UInt64.toNat_ofNatClamp_of_lt hfit)'
assert before.count(old)==1
repaired=before.replace(old,new)
primary=H/'Probe-b2-u64-roundtrip-repair2.lean';primary.write_bytes(repaired)
base=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert repaired[:len(base)]==base
layout=(H/'Public-math-layout-v1.lean.txt').read_bytes();assert layout.startswith(before)
public=repaired+b'\nsection R18PublicMULBridgeProbe\nset_option maxRecDepth 8192\n'+layout[len(before):]+b'\nend R18PublicMULBridgeProbe\n'
prune=json.loads((H/'byte-budget-preview.json').read_text())
for row in sorted(prune['removed'],key=lambda x:-x['start']):
 assert sha(public[row['start']:row['end']])==row['sha256']
 public=public[:row['start']]+public[row['end']:]
out=H/'Probe-numeric-mul-public-bridge-v2.lean';out.write_bytes(public)
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
rows=[]
for path in (primary,out):
 data=path.read_bytes();assert b'\r' not in data and path.read_text().encode()==data
 checks={k:env[k](path,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](path.read_text())
 assert all(v is None for v in checks.values()),checks
 rows.append(dict(path=path.name,bytes=len(data),sha256=sha(data),margin=256000-len(data),checks=checks))
pm=json.loads((q/'probe-b2-v1/manifest.json').read_text())
primary_roots=pm['explicit_helper_audit']
assert len(primary_roots)==13
appendix=public[len(base)-prune['saved']:].decode();roots=[];namespace=''
for line in appendix.splitlines():
 if line.startswith('namespace '):namespace=line.split()[1]
 elif line.startswith('end ') and line.split()[1]==namespace:namespace=''
 m=re.match(r'^(?:@\[inline\]\s+)?(?:def|theorem)\s+(\w+)',line)
 if m:
  assert namespace,(line,namespace)
  roots.append(namespace+'.'+m.group(1))
assert len(roots)==len(set(roots))
assert all(x in roots for x in primary_roots)
for name,names in [('HelperAudit-u64-repair2.lean.inc',primary_roots),('HelperAudit-public-bridge-v2.lean.inc',roots)]:
 (H/name).write_bytes((''.join('#print axioms '+x+'\n' for x in names)).encode())
j=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='NEW_SHARED_REPAIR_AND_PUBLIC_MATH_INPUTS_NOT_COMPILED',
 files=rows,repair=dict(source=str(shared.relative_to(R)),source_sha256=sha(shared.read_bytes()),old=old.decode(),new=new.decode(),
  evidence='Same final simplifier failure observed in UInt32 run40293041239; fixed lemma verified by numeric worker; UInt64 application is a new uncompiled derivation'),
 primary_roots=primary_roots,primary_support_roots=pm['dependency_support_roots'],public_roots=roots,
 proof_leaf_pruning=dict(plan='byte-budget-preview.json',saved=prune['saved'],removed=prune['removed']),
 public_runtime='Original four B2 entry definitions remain unchanged; new guardedMul_spec is a separate appended theorem. This file is for math/public-interface checking, not performance.',
 limitations=['U64 repair2 and all field/public proofs NOT_COMPILED','New public input is not exact B2 prefix because12 unused ordinary proof leaves were removed only from this new copy',
 'Do not cancel or relabel any already-started9f9 run','No new integer performance candidate or queue'],
 first_compile='Prefer the small240189B repaired numeric probe first; public-math input is dependent, not an independent confirmation',
 frozen_preserved=dict(numeric9f9=sha(frozen.read_bytes()),numeric_v3=sha((q/'Bridge-u64-integer-v3-lf.lean.inc').read_bytes())),CI=False,Git=False,local_Lean=False)
(H/'public-probe-v2-manifest.json').write_bytes((json.dumps(j,indent=2)+'\n').encode())
print(json.dumps(dict(state=j['state'],files=rows,primary_roots=len(primary_roots),public_roots=len(roots))))
