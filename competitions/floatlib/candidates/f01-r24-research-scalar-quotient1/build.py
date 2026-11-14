"""Assemble the old-scope proof-only probe; no Lean, CI, Git or network action."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json

D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
BASE=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
HELPER=R/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
BASE_SHA='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
HELPER_SHA='5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
ROOTS=['Submission.R24QuotientCertificate.checker_sound','Submission.R24QuotientCertificate.rounded_toNat']
sha=lambda b:hashlib.sha256(b).hexdigest()

def main():
    base=BASE.read_bytes(); fragment=(D/'Quotient.lean.inc').read_bytes()
    assert sha(base)==BASE_SHA and sha(HELPER.read_bytes())==HELPER_SHA
    assert b'\r' not in fragment
    source=base+b'\n'+fragment
    assert len(source)<=256000
    assert source[:len(base)]==base
    assert source.count(b'import ContractTensor')==1
    assert b'import ContractExact' not in source
    (D/'Kernel.lean').write_bytes(source)
    digest=sha(source)
    manifest={
      'candidate':D.name,'candidate_file':'Kernel.lean','candidate_sha256':digest,
      'candidate_bytes':len(source),'created_at_utc':datetime.now(timezone.utc).isoformat(),
      'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':180,
      'proof_status':'NOT_RUN_WORD_QUOTIENT_AND_RNE_HELPERS',
      'performance':'NOT_RUN_NO_CHANGED_PUBLIC_ENDPOINTS','formal_submission':'NOT_SUBMITTED',
      'official_submission_inherited':False,
      'helper_audit_module':HELPER.name,
      'helper_audit_module_path':'f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py',
      'helper_audit_module_sha256':HELPER_SHA,
      'explicit_helper_audit':ROOTS,'helper_audit_required_endpoints':ROOTS,
      'helper_audit_expected_count':2,'helper_audit_source_sha256':digest,'diagnostic_evaluations':[],
      'runtime_prefix':{'path':BASE.relative_to(R).as_posix(),'sha256':BASE_SHA,'bytes':len(base),'byte_identical':True},
      'fragment':{'path':(D/'Quotient.lean.inc').relative_to(R).as_posix(),'sha256':sha(fragment),'bytes':len(fragment)},
      'scope':'Old ContractTensor/B2 four endpoints byte-identical. Two conditional all-UInt64 helper roots refine the actual guarded product/subtraction and existing word RNE. No native-proposal accuracy premise, new axioms, extern, compiler changes or new-track implementation.',
      'domain':'n<2^49,0<d<2^25,q<2^25; check also requiresq*d<=n andn-q*d<d. The proposalq is arbitrary.',
      'missing':['No Binary32 rational/scale transport','No RMS/LayerNorm kernel','No current native caller/ASM/cost','No original full-gate or adoption'],
      'shared_deadline_utc':'2026-10-29T03:38:56Z'
    }
    (D/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    print(json.dumps({'candidate':D.name,'sha256':digest,'bytes':len(source),'fragment_sha256':sha(fragment),'roots':ROOTS}))

if __name__=='__main__':main()
