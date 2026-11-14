"""Independent source identity, exact-prefix and diagnostic-boundary checks."""
from pathlib import Path
import datetime, hashlib, json, re
HERE=Path(__file__).resolve().parent
ROOT=Path(__file__).resolve().parents[6]
BASE=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
base=BASE.read_bytes()
assert hashlib.sha256(base).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
specs=[('row-broadcast/Probe-row-broadcast8.lean','ec40e88eb85730520a1cd1e6adcbaea3c8161fc5c0f7e4b2f5795e178d24a5a6',239638,9),('representation/terminal-pair/Kernel-terminal-pair-diagnostic.lean','b6b77553d49e968db27639b84f104783a9cf474ed963ec9cff7753a7adb17962',230373,8)]
rows=[]
for relative,sha,n,count in specs:
    path=HERE/relative; raw=path.read_bytes()
    assert len(raw)==n and hashlib.sha256(raw).hexdigest()==sha
    assert raw.startswith(base) and len(raw)<=256000
    tail=raw[len(base):].decode()
    assert not re.search(r'^\s*(?:axiom\s|unsafe\s|sorry\b|admit\b|import\s)',tail,re.M)
    audit=path.parent/'HelperAudit.lean.inc'
    audittext=audit.read_text(encoding='utf-8')
    roots=re.findall(r'#print axioms\s+([\w.]+)',audittext)
    assert len(roots)==len(set(roots))==count
    assert set(roots[:4])=={'Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec'}
    rows.append({'path':str(path),'bytes':n,'sha256':sha,'prefix_exact':True,'audit_roots':roots,'count':count,'public_dispatch_unchanged':True,'Lean':'NOT_RUN','performance':'UNKNOWN'})
out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'SOURCE_IDENTITY_AND_BOUNDARIES_VERIFIED_NOT_LEAN','artifacts':rows,'scope':'Statement/codegen diagnostic sources. No new public BMM specification or whole speed claim. Row broadcast returns Array at fixed p=8; terminal pair is a complete-pair emitter with arbitrary source-array offsets. Four public specs remain B2.'}
(HERE/'ready-artifacts-review.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,ensure_ascii=False))
