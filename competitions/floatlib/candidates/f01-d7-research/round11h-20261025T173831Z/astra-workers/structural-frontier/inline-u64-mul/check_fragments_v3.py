"""Fixed original text policy on fragments and byte capacity arithmetic; no package or compiler."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import ast,hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
names=['Bridge-u64-product-v1.lean.inc','Runtime-u64-mul-v1.lean.inc','Bridge-u64-integer-v3-lf.lean.inc','Runtime-u64-mul-integer-v3-lf.lean.inc','Diagnostic-entry-v2.lean.inc']
rows=[]
for name in names:
 p=H/name;text=p.read_text();namespace=re.search(r'^namespace\s+(\S+)',text,re.M).group(1)
 checks={'intake':env['intake'](p,SimpleNamespace(slot='full')),'policy':env['policy'](p,SimpleNamespace(slot='full')),'options':env['options'](text)}
 assert all(x is None for x in checks.values()),(name,checks)
 helpers=[namespace+'.'+x for x in re.findall(r'^(?:@\[inline\]\s+)?(?:def|theorem)\s+(\w+)',text,re.M)]
 rows.append(dict(path=name,bytes=p.stat().st_size,sha256=sha(p),checks=checks,helpers=helpers))
base=R/'competitions/floatlib/candidates/f01-r16-dev-native-repack1/Kernel.lean'
assert sha(base)=='c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac'
size=base.stat().st_size+sum((H/n).stat().st_size+1 for n in names[2:])
runtime=(H/names[3]).read_text()
assert runtime.count('.toFloat32')==1 and runtime.count('.toUInt64')==3
assert '.toBits' not in runtime and '.ofBits' not in runtime
j=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='FRAGMENT_TEXT_POLICY_PASS_NO_COMPILATION',
 rows=rows,selected_runtime_static={'uint64_product':1,'forward_cast':1,'reverse_cast':1,'toBits_sites':0,'ofBits_sites':0},
 theoretical_c972_append_with_entry_bytes=size,margin=256000-size,full_file_created=False,
 limitations=['Fragments are not a full candidate; text policy does not prove dependency closure or any theorem',
 'No selected machine-code or performance evidence; source cast count is not an instruction count'],
 gate=dict(path=str(gate.relative_to(R)),sha256=sha(gate)))
(H/'fragment-check-v3.json').write_text(json.dumps(j,indent=2)+'\n')
print(json.dumps({k:j[k] for k in ('state','theoretical_c972_append_with_entry_bytes','margin','selected_runtime_static')}))
