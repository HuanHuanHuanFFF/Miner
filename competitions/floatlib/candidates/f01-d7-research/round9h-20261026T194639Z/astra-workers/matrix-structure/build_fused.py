from pathlib import Path
import hashlib,json,ast,re
from types import SimpleNamespace
from datetime import datetime,timezone
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda x:hashlib.sha256(x).hexdigest()
raw=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(raw)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
text=raw.decode();pos=text.rindex('\ndef bmm (')
tail=text[pos:].replace('def bmm (','def bmmBeforeFusedOutput (',1).replace('theorem bmm_spec','theorem bmmBeforeFusedOutput_spec',1).replace('(bmm batch','(bmmBeforeFusedOutput batch',1).replace('unfold bmm\n','unfold bmmBeforeFusedOutput\n',1)
frag=(H/'FusedOutput.lean.inc').read_bytes()
out=(text[:pos]+tail+'\n').encode()+frag
assert len(out)<256000
back=out[:-len(frag)].removesuffix(b'\n').replace(b'def bmmBeforeFusedOutput (',b'def bmm (',1).replace(b'theorem bmmBeforeFusedOutput_spec',b'theorem bmm_spec',1).replace(b'(bmmBeforeFusedOutput batch',b'(bmm batch',1).replace(b'unfold bmmBeforeFusedOutput',b'unfold bmm',1)
assert back==raw
path=H/'Kernel-fused-output-b2.lean';path.write_bytes(out)
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text())
env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
 env[name]=re.compile(ast.literal_eval(node.value.args[0])) if name=='BANNED' else ast.literal_eval(node.value)
fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](path,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](out.decode())
assert all(v is None for v in checks.values())
checks_count=0
for p in range(129):
 for g in range((p+1)//2):
  old=list(range(2*g,2*g+min(2,p-2*g)))
  new=[2*g]+([2*g+1] if 2*g+1<p else [])
  assert old==new;checks_count+=1
meta={'at_utc':datetime.now(timezone.utc).isoformat(),'baseline_sha256':sha(raw),'source_sha256':sha(out),'source_bytes':len(out),'fragment_sha256':sha(frag),'original_text_policy':checks,'baseline_exact_inverse':True,'finite_emit_boundary_cases':checks_count,'formal':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN','mechanism':'Fused loop terminal and direct two-output writer; original B2 preparation, exact MAC order, guard and fallback retained','scope':'Complete source draft; backup structural discriminator, not automatic additional CI queue'}
(H/'fused-build.json').write_text(json.dumps(meta,indent=2)+'\n')
print(json.dumps(meta))
