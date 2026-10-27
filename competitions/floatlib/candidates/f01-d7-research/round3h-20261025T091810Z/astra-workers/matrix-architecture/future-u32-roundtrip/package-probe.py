"""Assemble only existing namespaces; run fixed text checks, never Lean/CI."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import hashlib,json,re,ast
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
basepath=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean';base=basepath.read_bytes()
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
support=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/scalar-representation/next-add-u32/Add-native-high-support.lean'
sdata=support.read_bytes();pieces=[];parts=[];audit=[]
for name in ('R14NatNormal','R14WordAddRounding'):
 ns='Submission.'+name;marker=('namespace '+ns).encode();end=('end '+ns).encode()
 assert marker not in base and sdata.count(marker)==1 and sdata.count(end)==1
 lo=sdata.index(marker);hi=sdata.index(end,lo)+len(end)
 if sdata[hi:hi+2]==b'\r\n':hi+=2
 elif sdata[hi:hi+1]==b'\n':hi+=1
 raw=sdata[lo:hi];path=H/(name+'-complete.lean');path.write_bytes(raw);parts.append(raw)
 pieces.append(dict(path=path.name,sha256=sha(raw),bytes=len(raw),original_path=str(support.relative_to(R)),original_sha256=sha(sdata),original_byte_start=lo,original_byte_end_exclusive=hi,transform='NONE; exact complete namespace bytes'))
 for decl in re.findall(rb'^(?:theorem|def)\s+([A-Za-z0-9_]+)',raw,re.M):audit.append(ns+'.'+decl.decode())
original=H/'HighRoundtrip-bridge.lean';b=original.read_bytes();assert b.startswith(b'/-')
end=b.index(b'-/')+2
header=b'/- R16 numerical round-trip proof probe. NOT_COMPILED. -/'
clean=header+b[end:];(H/'HighRoundtrip-probe-fragment.lean').write_bytes(clean);parts.append(clean)
pieces.append(dict(path='HighRoundtrip-probe-fragment.lean',sha256=sha(clean),bytes=len(clean),original_path=original.name,original_sha256=sha(b),transform='Replace leading prose header only; theorem statements and bodies unchanged'))
audit.extend('Submission.R16UInt32Roundtrip.'+d.decode() for d in re.findall(rb'^(?:theorem|def)\s+([A-Za-z0-9_]+)',clean,re.M))
data=base+b'\n'+b'\n'.join(parts);out=H/'Probe-high-u32-roundtrip.lean';out.write_bytes(data)
assert len(data)<=256000 and data[:len(base)]==base
assert re.findall(rb'^import\s+([^\r\n]+)',data,re.M)==[b'ContractTensor']
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
gatehash=sha(gate.read_bytes());assert gatehash=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
 env[name]=re.compile(ast.literal_eval(node.value.args[0])) if name=='BANNED' else ast.literal_eval(node.value)
fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
v=SimpleNamespace(slot='full');checks={k:env[k](out,v) for k in ('intake','policy')};checks['options']=env['options'](out.read_text())
manifest=dict(created_utc=datetime.now(timezone.utc).isoformat(),state='DEPENDENCY_CLOSED_APPEND_PROBE_NOT_COMPILED',
 parent=dict(path=str(basepath.relative_to(R)),sha256=sha(base),bytes=len(base)),
 probe=dict(path=out.name,sha256=sha(data),bytes=len(data),margin=256000-len(data)),pieces=pieces,
 original_text_checks=dict(gate_path=str(gate.relative_to(R)),gate_sha256=gatehash,functions=['intake','policy','options'],comments_included=True,result=checks),
 explicit_helper_audit=audit,
 fixed_interface_evidence=[dict(path=name,sha256=sha((H/name).read_bytes())) for name in ('receipt.json','bridge-check.json','fixed-import-chain.json')],
 dependency_closure=[
  'ContractTensor -> Contract -> FloatLib -> Floats -> Formats -> IEEE754 -> Native.Integer -> ToInt/Rounding',
  'Pinned Native.ToInt supplies Model.toInt_toModel_eq; Native.Model supplies Model.toModel_ofFloat32Model',
  'Pinned Model.ExactValue supplies exactValue_eq_finite_of_toDyadic?_eq_some; Operations.Runtime supplies roundDyadicToInt',
  'Pinned Lean exposes Float32.toUInt32, Float32.Model.toUInt32, UnpackedFloat.toUInt32, UInt32.toNat_ofNatClamp_of_lt',
  'Exact B2 supplies R2W01c.uint32_model_eq_roundDyadic, R2W01c.fields32_toDyadic, raw-normal helpers, FastMul.log2_shift',
  'Exact extracted R14NatNormal namespace precedes R14WordAddRounding, which precedes new round-trip bridge'],
 public_runtime_delta='NONE: exact entire B2 retained as prefix; its add/mul/sum/bmm and four specs are unedited. Appended helper definitions are unreferenced by those entries.',
 required_next_check='Statement compile plus explicit kernel/dependency/standard-policy audit of every listed helper; unchanged four specs alone do not certify appended proofs.',
 not_claimed=['Compiled Lean','Helper axiom audit passed','Full gate acceptance','Speed or code-layout equality'],
 local_Lean=False,CI=False,Git=False)
(H/'packaged-probe-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(dict(probe=manifest['probe'],text_checks=checks,explicit_helpers=len(audit))))
assert all(x is None for x in checks.values()),checks
