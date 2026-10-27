"""Frozen runtime + plain diagnostic caller on byte-exact B2; policy only, no Lean/CI.
Outputs must not exist: source and receipts are immutable after this build.
"""
from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import ast,hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'AGENTS.md').exists())
sha=lambda b:hashlib.sha256(b).hexdigest()
def ident(p):
 b=p.read_bytes();return {'path':str(p.relative_to(R)),'bytes':len(b),'sha256':sha(b)}
parent=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
runtime=H.parent.parent/'numeric-roundtrip/Runtime-sorted-roundtrip-v1.lean.inc'
caller=H/'Diagnostic-entry-b2-add.lean.inc'
base,body,entry=(p.read_bytes() for p in (parent,runtime,caller))
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(body)=='e08543ac5c20cd53c39b010edfc684226032926418ea3125df8aa4a3805f799e'
for b in (base,body,entry):
 assert b'\r' not in b and not b.startswith(b'\xef\xbb\xbf')
 assert b.decode('utf-8').encode('utf-8')==b
assert b'namespace Submission.R17NumericAdd' not in base
assert 'guardedAdd Submission.add x y' in entry.decode()
assert not re.search(r'@\[|\b(export|extern)\b',entry.decode())
for leaf in ('mantissa','mkW','fromRaw','add'):
 assert re.search(r'\bdef\s+'+leaf+r'\b',base.decode()),leaf
roots=[];locations=[]
for path,data in ((runtime,body),(caller,entry)):
 stack=[]
 for i,line in enumerate(data.decode().splitlines(),1):
  m=re.match(r'^namespace\s+(\S+)\s*$',line)
  if m:stack.append(m.group(1));continue
  if re.match(r'^end(?:\s+\S+)?\s*$',line):
   assert stack;stack.pop();continue
  m=re.match(r'^(?:@\[[^\]]*\]\s*)?(?:def|abbrev|theorem)\s+(\w+)\b',line)
  if m:
   name='.'.join(stack+[m.group(1)]);roots.append(name)
   locations.append({'name':name,'source':str(path.relative_to(R)),'line':i})
 assert not stack
assert len(roots)==len(set(roots))
assert roots[-1]=='Submission.R17NumericAdd.diagnosticEntry'
assert {n.rsplit('.',1)[-1] for n in roots}=={'sortedAdd','guardedAdd','diagnosticEntry'}
data=base+b'\n'+body+b'\n'+entry
target=H/'Probe-b2-add-u32-lowering-v1.lean'
with target.open('xb') as f:f.write(data)
assert target.read_bytes()==data and target.read_text(encoding='utf-8').encode()==data
assert len(data)<=256000 and data[:len(base)]==base
with (H/'HelperAudit.lean.inc').open('x',encoding='utf-8') as f:
 f.write(''.join('#print axioms '+n+'\n' for n in roots))
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](target,SimpleNamespace(slot='full')) for k in ('intake','policy')}
checks['options']=env['options'](data.decode())
assert all(v is None for v in checks.values()),checks
report={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'DIAGNOSTIC_SOURCE_AND_ORIGINAL_TEXT_POLICY_READY_NOT_COMPILED',
 'source':ident(target),'parent':ident(parent),'runtime':ident(runtime),'caller':ident(caller),
 'concat':'Exact B2 bytes + oneLF + exact e085 runtime bytes + oneLF + caller bytes',
 'public_runtime_and_spec_delta':'NONE: all original B2 bytes preserved as exact prefix; only namespaced runtime/ordinary diagnostic def appended',
 'fallback':'Original B2 Submission.add only',
 'added_attributes':'NONE; two inline attributes are already in frozen e085, ordinary caller has none',
 'explicit_helper_roots':roots,'explicit_helper_root_count':len(roots),'helper_declaration_locations':locations,
 'helper_audit_source':ident(H/'HelperAudit.lean.inc'),
 'helper_audit_boundary':'Type/definition/dependency checks only. New ADD equivalence is not proved by these definitions or original four specs.',
 'text_precheck':checks,'gate_sha256':sha(gate.read_bytes()),'comments_scanned':True,
 'LF_only':True,'UTF8_no_BOM':True,'read_bytes_equals_read_text_encode':True,'remaining_bytes':256000-len(data),
 'runtime_global_names':'R2W01b.mantissa, Submission.FastMul.mkW, R7W02.fromRaw, original Submission.add are present in B2; expField is the fixed imported primitive already used by B2.',
 'Lean':'NOT_RUN','C_ASM':'NOT_RUN','performance':'NOT_RUN','CI':'NOT_STARTED_BY_WORKER','tokens':'UNKNOWN'}
with (H/'manifest.json').open('x',encoding='utf-8') as f:json.dump(report,f,indent=2);f.write('\n')
print(json.dumps({'state':report['state'],'source':report['source'],'roots':roots,'root_count':len(roots),'checks':checks,'LF':True},indent=2))
