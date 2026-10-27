"""Connect the reviewed numeric guard to the real public MUL entry."""
from pathlib import Path
from datetime import datetime,timezone
import difflib,hashlib,json,re
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest();save=lambda p,x:p.write_bytes((json.dumps(x,ensure_ascii=False,indent=2)+'\n').encode())
worker=HERE/'astra-workers/structural-frontier/integer-normal-mul'
producer=(worker/'Probe-numeric-mul-public-bridge-v2.lean').read_bytes()
assert sha(producer)=='365f49b1180bae24f217e83089e7a70e71bea6e22696f0b2197a11dac6e7871e' and len(producer)==255561 and b'\r' not in producer
record=json.loads((worker/'public-probe-v2-manifest.json').read_bytes())
text=producer.decode();marker='section R18PublicMULBridgeProbe\n';assert text.count(marker)==1
split=text.index(marker);trimmed=text[:split];append=text[split:]
parent=(C/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes();base=parent.decode()
def locate(s):
    n=s.index('@[inline] def nativeMul ')
    begin=s.index('@[inline] def mul (x y : Binary32)',n)
    needle='  · exact nativeMul_spec x y\n';end=s.index(needle,begin)+len(needle)
    return begin,end
a,b=locate(trimmed);x,y=locate(base);legacy=trimmed[a:b];assert legacy==base[x:y]
fallback=legacy.replace('def mul (','def mul0 (',1).replace('theorem mul_spec (','theorem mul0_spec (',1).replace(': mul x y =',': mul0 x y =',1).replace('  unfold mul\n','  unfold mul0\n',1)
assert 'theorem mul0_spec' in fallback and '  unfold mul0\n' in fallback
ns=append.index('namespace Submission.R18NumericMulSpec')
p=append.index('theorem preserved_fallback_entry_spec ',ns);q=append.index('end Submission.R18NumericMulSpec',p)
removed=append[p:q];assert 'guardedMul_spec Submission.mul Submission.mul_spec' in removed
append=append[:p]+append[q:]
p=append.index('theorem guardedMul_spec ',ns);q=append.index('end Submission.R18NumericMulSpec',p)
proof=append[p:q];assert proof.count('\n  dsimp only\n')==1
append=append[:p]+proof.replace('\n  dsimp only\n','\n  try dsimp only\n')+append[q:]
assert not re.search(r'\bSubmission\.mul(?:_spec)?\b',append)
wrapper='''namespace Submission
open FloatLib.Floats Competition
@[inline] def mul (x y : Binary32) : Binary32 :=
  R17NumericMulInteger.guardedMul mul0 x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R18NumericMulSpec.guardedMul_spec mul0 mul0_spec x y
'''
source=(trimmed[:a]+fallback+'\nend Submission\n\n'+append+'\n'+wrapper+trimmed[b:]).encode()
assert len(source)<=256000,len(source)
name='f01-r17-dev-u64-mul1';folder=C/name;folder.mkdir();(folder/'Kernel.lean').write_bytes(source)
parts=[]
for filename,data in [('development-public-mul1-math.lean',append.encode()),('development-public-mul1-wrapper.lean',wrapper.encode()),('development-public-mul1-base-trim.patch',''.join(difflib.unified_diff(base.splitlines(True),trimmed.splitlines(True),fromfile='B2-622d',tofile='producer-trimmed-B2')).encode())]:
    path=HERE/filename;path.write_bytes(data);parts.append(dict(path=path.relative_to(ROOT).as_posix(),sha256=sha(data),bytes=len(data)))
roots=record['public_roots'];oldroot='Submission.R18NumericMulSpec.preserved_fallback_entry_spec';assert oldroot in roots
roots=[n for n in roots if n!=oldroot]+['Submission.mul_spec'];assert len(roots)==len(set(roots))==63
meta=dict(candidate=name,candidate_file='Kernel.lean',candidate_sha256=sha(source),candidate_bytes=len(source),created_at_utc=datetime.now(timezone.utc).isoformat(),parent='f01-r15-dev-packed-b2-1',parent_sha256=sha(parent),components=parts,
    producer_math_source_sha256=sha(producer),producer_cleanup='Producer removed12 ordinary unreferenced proof leaves; original source and inverse-replay receipt retained in research scope. Source/compiler must verify this derivative.',
    mechanism='Actual public MUL calls UInt64 exact product/numeric roundtrip guard with original B2 mul0 fallback; public add unchanged; SUM/BMM callers may reach new MUL, so full4-operation gate required.',
    proof_change='Replace redundant appended old-public specialization with actual public mul_spec; only tolerate an already-normal goal at guardedMul_spec dsimp. No new premise.',
    intended_validation='Exact-source statement/kernel/63-helper audit then original full gate and clean cost versus B2/control41. No performance claim at creation.',
    proof_status='NOT_COMPILED',performance='NOT_RUN',explicit_helper_audit=roots,helper_audit_expected_count=len(roots),helper_audit_source_sha256=sha(source),helper_audit_required_endpoints=['Submission.R18NumericMulSpec.guardedMul_spec','Submission.mul_spec'],helper_audit_module_sha256=sha((HERE/'development-helper-audit.py').read_bytes()))
save(folder/'manifest.json',meta)

worker=HERE/'astra-workers/numeric-roundtrip';r=json.loads((worker/'repair2-manifest.json').read_bytes());raw=(ROOT/r['dependent_output_probe']['path']).read_bytes()
assert sha(raw)=='32b824f5000db80c124d49270c55bd572197ab3e9274b209b723b1fea362a542' and len(raw)==244908 and b'\r' not in raw
audit=(worker/'OutputProbeAudit.lean.inc').read_bytes();names=[n.decode() for n in re.findall(rb'^#print axioms ([A-Za-z0-9_.]+)\s*$',audit,re.M)];assert len(names)==len(set(names))==30
name2='f01-r17-dev-add-output-probe1';f=C/name2;f.mkdir();(f/'Kernel.lean').write_bytes(raw)
part=HERE/'development-add-output-probe1-fragment.lean';assert raw.startswith(parent);part.write_bytes(raw[len(parent):])
save(f/'manifest.json',dict(candidate=name2,candidate_file='Kernel.lean',candidate_sha256=sha(raw),candidate_bytes=len(raw),parent='f01-r15-dev-packed-b2-1',parent_sha256=sha(parent),components=[dict(path=part.relative_to(ROOT).as_posix(),sha256=sha(part.read_bytes()),bytes=part.stat().st_size)],
    mechanism='Dependent ADD output/model proof probe; declared normalization premises remain, public ADD/runtime unchanged.',proof_status='NOT_COMPILED',performance='NOT_RUN',explicit_helper_audit=names,helper_audit_expected_count=30,helper_audit_source_sha256=sha(raw),helper_audit_required_endpoints=[names[-1]],helper_audit_module_sha256=sha((HERE/'development-helper-audit.py').read_bytes())))
save(HERE/'development-public-entry-batch.json',dict(at_utc=datetime.now(timezone.utc).isoformat(),mul=dict(candidate=folder.name,sha256=sha(source),bytes=len(source),roots=len(roots)),add_output=dict(candidate=name2,sha256=sha(raw),bytes=len(raw),roots=30),public_gate='NOT_RUN',performance='NOT_RUN'))
print(json.dumps(dict(mul=folder.name,mul_sha256=sha(source),mul_bytes=len(source),mul_roots=len(roots),add_output=name2)))
