"""Use one carrier: preserve producer declaration order and old internal graph."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest();save=lambda p,x:p.write_bytes((json.dumps(x,ensure_ascii=False,indent=2)+'\n').encode())
worker=HERE/'astra-workers/structural-frontier/integer-normal-mul/public-entry-v1'
original=(worker/'Kernel.lean').read_bytes();assert sha(original)=='176c70cbd602082c3c4727234487605c1c4945eb808180cac82230d74ebb3831'
assert len(original)==255700 and b'\r' not in original
text=original.decode();ns=text.index('namespace R18.R18NumericMulSpec')
p=text.index('theorem guardedMul_spec ',ns);q=text.index('theorem preserved_fallback_entry_spec ',p)
proof=text[p:q];assert proof.count('\n  dsimp only\n')==1
source=(text[:p]+proof.replace('\n  dsimp only\n','\n  try dsimp only\n')+text[q:]).encode();assert len(source)==255704<256000
audit_path=next(p for p in worker.glob('*Audit*') if p.is_file());audit=audit_path.read_bytes()
roots=[x.decode() for x in re.findall(rb'^#print axioms ([A-Za-z0-9_.]+)\s*$',audit,re.M)];assert len(roots)==len(set(roots))==63
roots+= [n for n in ('Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec') if n not in roots]
assert len(roots)==67
helper=(HERE/'development-helper-audit.py').read_text().replace("r'Submission\\.[A-Za-z0-9_.]+'", "r'(?:Submission|R18)\\.[A-Za-z0-9_.]+'").replace('1 <= len(names) <= 64','1 <= len(names) <= 128')
assert helper!=(HERE/'development-helper-audit.py').read_text()
hpath=HERE/'development-helper-audit-v2.py';hpath.write_bytes(helper.encode())
name='f01-r17-dev-u64-public1';folder=C/name;folder.mkdir();(folder/'Kernel.lean').write_bytes(source)
part=HERE/'development-u64-public1-source.lean';part.write_bytes(source)
meta=dict(candidate=name,candidate_file='Kernel.lean',candidate_sha256=sha(source),candidate_bytes=len(source),created_at_utc=datetime.now(timezone.utc).isoformat(),parent='f01-r15-dev-packed-b2-1',parent_sha256='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58',components=[dict(path=part.relative_to(ROOT).as_posix(),sha256=sha(source),bytes=len(source))],
    producer_source_sha256=sha(original),mechanism='Real public MUL invokes original v3 UInt64 numeric core with old R18.mul fallback. Other public operations alias unchanged producer functions; internal declaration order and SUM/BMM reference graph remain.',
    carrier_decision='Choose producer namespace-alias carrier; D ddaf relocated carrier remains NOT_RUN, no parallel performance queue.',proof_change='Only tolerate no-progress dsimp at the already-unfolded guardedMul_spec target, a compiler-observed prior symptom; no premise/runtime change.',
    intended_validation='Actual four public obligations plus67 explicit roots, then clean original full performance gate; not a speed claim.',proof_status='NOT_COMPILED',performance='NOT_RUN',
    explicit_helper_audit=roots,helper_audit_expected_count=len(roots),helper_audit_source_sha256=sha(source),helper_audit_required_endpoints=['R18.R18NumericMulSpec.guardedMul_spec','Submission.mul_spec'],helper_audit_module='development-helper-audit-v2.py',helper_audit_module_sha256=sha(hpath.read_bytes()))
save(folder/'manifest.json',meta)
diag=ROOT/'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py';s=diag.read_text()
old="helper_path=profiler.parent.parent/'f01-d7-research/round11h-20261025T173831Z/development-helper-audit.py'"
new="helper_name=helper_manifest.get('helper_audit_module','development-helper-audit.py')\n        assert helper_name in ('development-helper-audit.py','development-helper-audit-v2.py')\n        helper_path=profiler.parent.parent/'f01-d7-research/round11h-20261025T173831Z'/helper_name"
assert s.count(old)==1;diag.write_bytes(s.replace(old,new).encode())
blocks=[n.value for n in ast.walk(ast.parse(diag.read_text())) if isinstance(n,ast.Constant) and isinstance(n.value,str) and 'g.STAGES=' in n.value];assert len(blocks)==1;compile(blocks[0],str(diag)+':embedded','exec')
save(HERE/'development-carrier-choice.json',dict(at_utc=datetime.now(timezone.utc).isoformat(),chosen=name,sha256=sha(source),bytes=len(source),roots=67,unrun_alternative='f01-r17-dev-u64-mul1 / ddaf257e',reason='Preserve producer declaration order and old internal reference graph; avoid forward-reference uncertainty and a second performance carrier.',support_change='Versioned namespace-aware helper audit only; old helper bytes remain unchanged. Original gate/contracts/bench/pins unchanged.'))
print(json.dumps(dict(candidate=name,sha256=sha(source),bytes=len(source),roots=67)))
