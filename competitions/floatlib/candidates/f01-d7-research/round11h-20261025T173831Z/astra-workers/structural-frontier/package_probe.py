"""Append the two interface modules to retained source; run existing text checks only."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime, timezone
import ast,hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
basepath=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
base=basepath.read_bytes()
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
pieces=[];bodies=[];helpers=[]
for name in ('TemporalCore.lean','OrderedBlocks.lean'):
    raw=(H/name).read_bytes()
    assert raw.startswith(b'import ContractTensor\n')
    body=raw.removeprefix(b'import ContractTensor\n')
    bodies.append(body)
    namespace=re.search(rb'^namespace\s+(\S+)',body,re.M).group(1).decode()
    helpers.extend(namespace+'.'+x.decode() for x in re.findall(rb'^(?:@\[inline\]\s+)?(?:def|theorem)\s+(\w+)',body,re.M))
    pieces.append(dict(path=name,source_sha256=sha(raw),bytes=len(raw),
        append_sha256=sha(body),transformation='Remove only leading duplicate import line'))
out=H/'Probe-temporal-interface.lean'
data=base+b'\n'+b'\n'.join(bodies)
out.write_bytes(data)
assert data[:len(base)]==base and len(data)<256000
assert re.findall(rb'^import\s+([^\r\n]+)',data,re.M)==[b'ContractTensor']
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text())
env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,
     'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
    node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
    env[name]=re.compile(ast.literal_eval(node.value.args[0])) if name=='BANNED' else ast.literal_eval(node.value)
fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
v=SimpleNamespace(slot='full')
checks={k:env[k](out,v) for k in ('intake','policy')}
checks['options']=env['options'](out.read_text())
manifest=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='APPEND_INTERFACE_PROBE_STATIC_TEXT_PASS_NOT_COMPILED',
    parent=dict(path=str(basepath.relative_to(R)),sha256=sha(base),bytes=len(base)),
    probe=dict(path=out.name,sha256=sha(data),bytes=len(data),margin=256000-len(data)),
    pieces=pieces,explicit_helper_audit=helpers,text_checks=checks,
    original_text_check_source=dict(path=str(gate.relative_to(R)),sha256=sha(gate.read_bytes())),
    public_runtime_delta='NONE; complete exact retained baseline is unchanged prefix; new helpers unused by four public entries',
    proof_gap='No actual pack/loop-to-original B2 bridge or whole vector entry proof; generic order theorem is an uncompiled attempt',
    required_before_claim='Actual pinned statement compile plus explicit helper replay/dependency audit; unchanged public specs do not certify helpers',
    performance='UNKNOWN; no timing requested',CI=False,Git=False,local_Lean=False)
(H/'probe-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(dict(probe=manifest['probe'],checks=checks,helper_count=len(helpers))))
assert all(x is None for x in checks.values()),checks
