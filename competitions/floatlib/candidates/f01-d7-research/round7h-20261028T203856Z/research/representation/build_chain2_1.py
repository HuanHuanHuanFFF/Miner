"""Old-scope portable mathematics package. Does not start Lean/CI/benchmarks."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,ast
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
base=(C/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
fragment_path=HERE/'TwoChain128.lean.inc'
fragment=fragment_path.read_bytes()
blob=base+b'\n'+fragment
assert len(blob)<=256000 and blob[:len(base)]==base
assert re.search(rb'(?m)^\s*(?:import|axiom|unsafe)\b',fragment) is None
for token in [b'sorry',b'implemented_by',b'@[extern',b'native_decide']:
    assert token not in fragment
out=C/'f01-r24-research-representation-chain2-1'
out.mkdir(exist_ok=True)
(out/'Kernel.lean').write_bytes(blob)
helper='f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
roots=['Submission.R24TwoChain128.'+n for n in ['merge_eq_add128','merge_represents','extend_represents',
    'signed128_of_represents','loop_represents','total_abs_lt_82','run2_exact_signed_sum']]
manifest=dict(candidate=out.name,candidate_file='Kernel.lean',candidate_sha256=sha(blob),candidate_bytes=len(blob),
    created_at_utc=datetime.now(timezone.utc).isoformat(),validation_mode='statement-only',diagnostic_only=True,
    diagnostic_timeout_seconds=180,proof_status='NOT_RUN',queue_status='NOT_QUEUED_DO_NOT_ADD_WITHOUT_D_SCHEDULING',
    performance='NOT_RUN',formal_submission='NOT_SUBMITTED',official_submission_inherited=False,
    helper_audit_module='development-helper-audit-v8.py',helper_audit_module_path=helper,
    helper_audit_module_sha256=sha((C/helper).read_bytes()),explicit_helper_audit=roots,
    helper_audit_required_endpoints=roots,helper_audit_expected_count=len(roots),helper_audit_source_sha256=sha(blob),
    diagnostic_evaluations=[],runtime_base_sha256=sha(base),runtime_base_prefix_bytes=len(base),
    byte_identical_base_prefix_verified=True,
    components=[dict(path=fragment_path.relative_to(ROOT).as_posix(),sha256=sha(fragment),bytes=len(fragment))],
    public_endpoints='Complete B2 prefix and all four old public endpoints/proofs are byte-identical.',
    scope='Clean-room old ContractTensor portable two-chain signed128 word-sum mathematics probe; no new ContractExact kernel.',
    runtime='run2 -> loop -> high/merge uses List UInt64 plus four scalar UInt64 accumulators; Int/Nat interpretations occur only in separate proof-facing declarations.',
    semantic_endpoint='For a List of standard two-complement signed64 words, length<2^20 and every abs(decoded term)<2^62, signed128(run2 terms)=the exact Int sum of those same decoded terms.',
    encoding='Standard two-complement, no deferred negative-count correction. Former S-c callers require a separate proven adapter and terminal correction audit.',
    remaining=['Lean typing/replay/axiom audit','original raw-product/shift term encoder','array/indexed caller loop',
        'original base/tiny-bias guard','original final rounding/signed-zero observation','actual lowering/cost'],
    nonclaims=['No speedup or 2x claim','Existing convolution multichain is not novel coverage',
        'No copied former champion implementation','No full-gate or adoption claim'],
    sources=[dict(ref='0d91825727839f597fd06b22fdd038ea21480f0c',license='MIT',
        path='FloatLib/Kernels/FixedWord/Product/Proof.lean',blob='bc4df19b192adbe51fc32512818e3679fe6f8aef'),
      dict(ref='0d91825727839f597fd06b22fdd038ea21480f0c',license='MIT',
        path='FloatLib/Kernels/FixedWord/Product/Runtime.lean',blob='94d7ec9cbdf3b2b641c734128b0f6d6fba67774b'),
      dict(ref='0d91825727839f597fd06b22fdd038ea21480f0c',license='MIT',
        path='FloatLib/Kernels/FixedWord/Core/Proof/UInt128.lean',blob='d9935670e5d70c31578b908af0134320ad87d8b2')],
    local_Lean=False,CI_owner='D',window_start_utc='2026-10-28T20:38:56Z',shared_deadline_utc='2026-10-29T03:38:56Z',
    actual_phase_first_utc='2026-10-28T23:55:43Z',tokens='UNKNOWN',cached_input_tokens='UNKNOWN')
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
receipt=dict(manifest=manifest,builder_sha256=sha(Path(__file__).read_bytes()),checked_at_utc=datetime.now(timezone.utc).isoformat(),
    static_checks=['exact B2 prefix','256000B cap','no new import/unsafe/axiom/sorry/extern','v8/180 path/hash',
                   'root-relative component path','original R24 deadline'],Lean='NOT_RUN',queue='NOT_QUEUED')
(HERE/'chain2-1-source-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
ast.parse(Path(__file__).read_text(encoding='utf-8'))
print(json.dumps(dict(candidate=out.name,sha256=sha(blob),bytes=len(blob),fragment_sha256=sha(fragment),roots=roots,status='NOT_RUN_NOT_QUEUED')))
