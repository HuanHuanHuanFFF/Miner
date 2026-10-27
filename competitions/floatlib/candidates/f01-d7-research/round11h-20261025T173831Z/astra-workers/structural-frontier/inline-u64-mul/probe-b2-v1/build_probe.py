"""Freeze a math-only B2-prefix probe; original fragments and candidate runtime remain unchanged."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import ast,hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
basepath=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
parentpath=R/'competitions/floatlib/candidates/f01-r16-dev-native-repack1/Kernel.lean'
bridgepath=H.parent/'Bridge-u64-integer-v3-lf.lean.inc'
base,parent,bridge=(p.read_bytes() for p in (basepath,parentpath,bridgepath))
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(parent)=='c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac'
assert sha(bridge)=='2261f1e317310bfb6505eb3ee333ad8b6b31f9ad13307f728719ecd3920fb906'
parts=[];pieces=[];support=[]
for name,cutoff,out in (
 ('Submission.R14NatNormal',b'/-- Unlike the old NormalBand helper','support-nat-normal.lean.inc'),
 ('Submission.R14ExponentShift',b'@[inline] def ex (u : UInt32)','support-exponent-shape.lean.inc')):
 start=parent.index(('namespace '+name+'\n').encode())
 stop=parent.index(cutoff,start)
 end_start=parent.index(('end '+name+'\n').encode(),stop)
 ending=parent[end_start:end_start+len(('end '+name+'\n').encode())]
 body=parent[start:stop]+ending
 assert ('namespace '+name).encode() not in base
 (H/out).write_bytes(body);parts.append(body)
 support.extend(name+'.'+d.decode() for d in re.findall(rb'^(?:theorem|def)\s+(\w+)',body,re.M))
 pieces.append(dict(path=out,sha256=sha(body),bytes=len(body),source=str(parentpath.relative_to(R)),source_sha256=sha(parent),
   source_byte_start=start,source_byte_stop_exclusive=stop,closing_namespace_byte_start=end_start,
   transform='Copy exact contiguous support prefix and its original closing namespace; omit unrelated later declarations'))
roots=['Submission.R17UInt64Integer.'+d.decode() for d in re.findall(rb'^(?:theorem|def)\s+(\w+)',bridge,re.M)]
assert len(roots)==13 and len(set(roots))==13
parts.append(bridge)
pieces.append(dict(path=str(bridgepath.relative_to(H.parent)),sha256=sha(bridge),bytes=len(bridge),transform='NONE; frozen LF fragment copied exactly'))
header=b'\nsection R17UInt64InterfaceProbe\nset_option maxRecDepth 8192\n\n'
data=base+header+b'\n'.join(parts)+b'\nend R17UInt64InterfaceProbe\n'
out=H/'Probe-b2-u64-roundtrip-v1.lean';out.write_bytes(data)
assert data[:len(base)]==base and len(data)<=256000
assert b'\r' not in data and out.read_text(encoding='utf-8').encode('utf-8')==data
assert re.findall(rb'^import\s+([^\r\n]+)',data,re.M)==[b'ContractTensor']
audit=H/'HelperAudit.lean.inc';audit.write_bytes((''.join('#print axioms '+r+'\n' for r in roots)).encode())
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](out,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](out.read_text())
assert all(v is None for v in checks.values()),checks
manifest=dict(created_utc=datetime.now(timezone.utc).isoformat(),state='FROZEN_B2_PREFIX_MATH_INTERFACE_PROBE_NOT_COMPILED',
 parent=dict(path=str(basepath.relative_to(R)),sha256=sha(base),bytes=len(base)),
 support_source=dict(path=str(parentpath.relative_to(R)),sha256=sha(parent)),
 probe=dict(path=out.name,sha256=sha(data),bytes=len(data),margin=256000-len(data)),pieces=pieces,
 explicit_helper_audit=roots,dependency_support_roots=support,
 audit_file=dict(path=audit.name,sha256=sha(audit.read_bytes()),bytes=audit.stat().st_size),
 public_runtime_delta='NONE; exact B2 prefix including four entries/specs unchanged. Appended declarations are mathematical definitions/proofs only.',
 static_checks=dict(original_gate_path=str(gate.relative_to(R)),original_gate_sha256=sha(gate.read_bytes()),
   intake_policy_options=checks,comments_included=True,canonical_LF=True,read_bytes_equals_read_text_utf8=True,one_import=True),
 required_compile='Pinned statement then complete module replay and explicit 13-root dependency audit; original four specs alone do not certify the appendix',
 first_unknown='Elaboration of the numeric UInt64 decode/truncate/clamp proof and the new product-specific normalization helpers',
 not_run=['Lean','Kernel replay','Helper dependency audit','C/ASM','Performance'],
 tokens='UNKNOWN',cached_input='UNKNOWN',CI=False,Git=False,local_Lean=False)
(H/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
print(json.dumps(dict(probe=manifest['probe'],helpers=len(roots),support_roots=len(support),checks=checks,LF=True)))
