from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import hashlib,json,re,ast,difflib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
base=(H.parent/'Kernel-temporal-b2.lean').read_bytes()
assert sha(base)=='c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c'
original=base.decode();text=original
# Old B2 is unreferenced by c70 except tileIndex, after removing its unused saved public entry.
begin=text.index('namespace Submission.R15PackedB2\n')
pack=text.index('\ndef packB ',begin)
end=text.index('end Submission.R15PackedB2',pack)+len('end Submission.R15PackedB2')
old_b2=text[begin:end]
kept=text[begin:pack]+'\n\nend Submission.R15PackedB2'
text=text[:begin]+kept+text[end:]
# Remove the old renamed public bmm/spec, whose only caller was itself.
pos=text.index('\ndef bmmBeforeTemporal (')
begin=text.rfind('\nnamespace Submission\n',0,pos)
end=text.index('end Submission',pos)+len('end Submission')
old_saved=text[begin:end];text=text[:begin]+text[end:]
assert set(re.findall(r'R15PackedB2\.(\w+)',text))=={'tileIndex'}
# Replace only the current public c70 bmm namespace with the new public entry.
pos=text.rindex('\ndef bmm (');begin=text.rfind('\nnamespace Submission\n',0,pos)
end=text.index('end Submission',pos)+len('end Submission')
old_public=text[begin:end];text=text[:begin]+text[end:]
pruned=text
frag=(H/'DualTemporal.lean.inc').read_bytes()
out=pruned.encode()+b'\n'+frag
path=H/'Kernel-dual-temporal-a4.lean';path.write_bytes(out)
assert len(out)<256000
assert re.findall(rb'^import\s+([^\r\n]+)',out,re.M)==[b'ContractTensor']
assert len(re.findall(rb'^def bmm \(',out,re.M))==1
assert len(re.findall(rb'^theorem bmm_spec\b',out,re.M))==1
# Preserve the whole prefix through the prior thin-pair implementation, including all scalar/sum code.
stable=original.index('namespace Submission.R15PackedB2\n')
assert out[:stable]==base[:stable]
patch=''.join(difflib.unified_diff(original.splitlines(keepends=True),pruned.splitlines(keepends=True),fromfile='c70c.lean',tofile='pruned-c70c.lean'))
(H/'pruning.patch').write_bytes(patch.encode())
# Store the exact removal blocks and their locations so the pruning has a byte-level inverse recipe.
(H/'removed-original-b2.txt').write_bytes(old_b2.encode())
(H/'removed-old-saved-public.txt').write_bytes(old_saved.encode())
(H/'removed-current-public.txt').write_bytes(old_public.encode())
roots=[];ns=[]
for line in frag.decode().splitlines():
 m=re.match(r'namespace\s+(\S+)',line)
 if m:ns.append(m[1]);continue
 m=re.match(r'end\s+(\S+)',line)
 if m:assert ns.pop()==m[1];continue
 m=re.match(r'theorem\s+(\w+)',line)
 if m:roots.append('.'.join(ns+[m[1]]))
for name in ['Submission.add_spec','Submission.mul_spec','Submission.sum_spec']:roots.append(name)
assert not ns
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
 env[name]=re.compile(ast.literal_eval(node.value.args[0])) if name=='BANNED' else ast.literal_eval(node.value)
fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](path,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](out.decode())
assert all(v is None for v in checks.values())
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'source':path.name,'source_sha256':sha(out),'source_bytes':len(out),'margin_bytes':256000-len(out),'parent_sha256':sha(base),'pruned_base_sha256':sha(pruned.encode()),'pruned_base_bytes':len(pruned.encode()),'stable_prefix_bytes':stable,'fragment_sha256':sha(frag),'fragment_bytes':len(frag),'pruning_patch_sha256':sha(patch.encode()),'removed_blocks':{'old_B2':{'bytes':len(old_b2.encode()),'sha256':sha(old_b2.encode())},'old_saved_public':{'bytes':len(old_saved.encode()),'sha256':sha(old_saved.encode())},'old_current_public':{'bytes':len(old_public.encode()),'sha256':sha(old_public.encode())}},'explicit_helper_roots':roots,'expected_root_count':len(roots),'text_policy':checks,'formal':'NOT_RUN','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','domain':'3<=p<=8,n>1,m>=4, outer UnderflowZero retained; all other inputs use c70 dispatch','mechanism':'One flat A4 cache over row/k, pure prepared-field temporal loop, original output/finish/replay; no cross-row tile cache','caveat':'Pruning only textual reference closure checked; exact compiled module/kernel replay still required. New A allocation/lifetime/controls are part of full cost.'}
(H/'build-receipt.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({k:manifest[k] for k in ('source_sha256','source_bytes','margin_bytes','pruned_base_bytes','fragment_bytes','expected_root_count','text_policy','formal')}))
