"""Import true public ADD and retain a versioned bounded helper auditor."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest();save=lambda p,x:p.write_bytes((json.dumps(x,ensure_ascii=False,indent=2)+'\n').encode())
worker=HERE/'astra-workers/numeric-roundtrip/public-add-v1';record=json.loads((worker/'manifest.json').read_bytes())
raw=(worker/'Kernel.lean').read_bytes();assert sha(raw)==record['candidate']['sha256']=='7e1524c818285ce2c7721140fd0cff23560416abc6ea9a2c72ddf1be9a588be7'
assert len(raw)==254923 and b'\r' not in raw
audit_path=next(p for p in worker.glob('*Audit*') if p.is_file());audit=audit_path.read_bytes()
names=[n.decode() for n in re.findall(rb'^#print axioms ([A-Za-z0-9_.]+)\s*$',audit,re.M)];assert len(names)==len(set(names))==71
helper=(HERE/'development-helper-audit-v2.py').read_text().replace('(?:Submission|R18)', '(?:Submission|R18|R18A)')
path=HERE/'development-helper-audit-v3.py';path.write_bytes(helper.encode())
name='f01-r17-dev-add-public1';folder=C/name;folder.mkdir();(folder/'Kernel.lean').write_bytes(raw)
part=HERE/'development-add-public1-source.lean';part.write_bytes(raw)
meta=dict(candidate=name,candidate_file='Kernel.lean',candidate_sha256=sha(raw),candidate_bytes=len(raw),created_at_utc=datetime.now(timezone.utc).isoformat(),parent='f01-r15-dev-packed-b2-1',parent_sha256='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58',components=[dict(path=part.relative_to(ROOT).as_posix(),sha256=sha(raw),bytes=len(raw))],
    mechanism='Real public sorted numeric ADD; fixed old R18A.add fallback, other three public functions alias original implementation. All4 original gates still required.',proof_status='NOT_COMPILED',performance='NOT_RUN',
    explicit_helper_audit=names,helper_audit_expected_count=71,helper_audit_source_sha256=sha(raw),helper_audit_required_endpoints=['Submission.add_spec'],helper_audit_module='development-helper-audit-v3.py',helper_audit_module_sha256=sha(path.read_bytes()))
save(folder/'manifest.json',meta)
diag=ROOT/'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py';s=diag.read_text();old="assert helper_name in ('development-helper-audit.py','development-helper-audit-v2.py')";assert s.count(old)==1
diag.write_bytes(s.replace(old,"assert helper_name in ('development-helper-audit.py','development-helper-audit-v2.py','development-helper-audit-v3.py')").encode())
blocks=[n.value for n in ast.walk(ast.parse(diag.read_text())) if isinstance(n,ast.Constant) and isinstance(n.value,str) and 'g.STAGES=' in n.value];assert len(blocks)==1;compile(blocks[0],str(diag)+':embedded','exec')
save(HERE/'development-full-mul-failure.json',dict(run=40302810209,candidate='f01-r17-dev-u64-public1',sha256='23adf0984bef02e611143cfc7e40d64d65c99caa0f4d11a0648812b2fb6f1e73',stage='statement',reported_lines=[6849,6873,6907],compiler_summary='Three rewrite-pattern failures; original full gate only retained truncated reasons. Exact unchanged-source diagnostic follows; performance NOT_RUN.'))
print(json.dumps(dict(candidate=name,sha256=sha(raw),bytes=len(raw),roots=len(names))))
