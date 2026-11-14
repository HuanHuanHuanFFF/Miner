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
      'proof_status':'NOT_RUN_TARGETED_UINT64_NONZERO_PROOF_REPAIR',
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
      'repair_parent':{
        'candidate':'f01-r24-research-scalar-quotient1',
        'kernel_sha256':'dd1f130159a727f63c1f91382e36ebd35956347fc73d69e44b0cc71b3ea291c2',
        'run':40779515020,'source_commit':'6d98f9ae6c3d6b3b9bce665c4a056f3b7baa5b97',
        'error':'Submission.lean:6672: Preorder UInt64 unavailable for ne_of_gt',
        'log_path':'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/ci-runs/40779515020/download-eae6df33b309440a85a664a669ee16b0/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-research-scalar-quotient1/full-build-output.txt',
        'log_sha256':'493efe30d97f09fc0658430a3760520ffd7b2dd729eab9281625d29cbe6386f1',
        'change':'Only hden proof: convert the UInt64 strict inequality and equality to Nat, then omega. Runtime definitions, theorem statements, root names and B2 prefix unchanged.'
      },
      'shared_start_utc':'2026-10-28T20:38:56Z',
      'shared_deadline_utc':'2026-10-29T03:38:56Z',
      'deadline_basis':'Original R24 seven-hour window. R/D source audit corrected a restored-display misreading: the apparent3.5h instruction was historical2026-10-26, not a new current instruction. No new round or extension.'
    }
    (D/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    print(json.dumps({'candidate':D.name,'sha256':digest,'bytes':len(source),'fragment_sha256':sha(fragment),'roots':ROOTS}))

if __name__=='__main__':main()
