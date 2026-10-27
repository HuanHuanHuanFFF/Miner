"""Compact the current research entry; retain the full previous state verbatim."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json
import subprocess

base=Path(__file__).resolve().parent;root=base.parents[4];now=datetime.now(timezone.utc).isoformat()
state_path=base/'astra-status.json';old=state_path.read_bytes()
history=base/'astra-status-before-20261025T0245Z.json'
if not history.exists():history.write_bytes(old)
dev=json.loads((root/'competitions/floatlib/coordination/development-status.json').read_bytes())
decision=json.loads((base/'development-add2-first-d-decision.json').read_bytes())
run=root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40152158687'
verdicts=list(run.rglob('f01-r14-dev-word-add-entry2-verdict.json'))
assert len(verdicts)==1
raw=verdicts[0].read_bytes();v=json.loads(raw)
assert v['passed'] and v['mode']=='gate' and v['stage']=='score' and len(v['rounds'])==25
assert v['verifier_fingerprint']==v['verifier_fingerprint_end']
input_path=verdicts[0].parent/'inputs/f01-r14-dev-word-add-entry2/Kernel.lean'
assert sha256(input_path.read_bytes()).hexdigest()=='f958071e037ea5627a34d41b296d07cc97fd13eec41117de7c9b184bf0fad653'
proof=dict(candidate='f01-r14-dev-word-add-entry2',sha256='f958071e037ea5627a34d41b296d07cc97fd13eec41117de7c9b184bf0fad653',
    run=40152158687,seed=1425016,full_original_gate=True,rounds=25,
    verdict=verdicts[0].relative_to(root).as_posix(),verdict_sha256=sha256(raw).hexdigest(),
    verifier_fingerprint=v['verifier_fingerprint'],
    decision='PARK_PERFORMANCE_REGRESSION',performance_source='development-add2-first-d-decision.json',
    headline=decision.get('headline'),add_ratio=decision.get('add'))
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,timeout=2).decode().strip()
state=dict(state='R14_FROZEN_RUNTIME_FINAL_VERIFICATION_AND_TERMINATION_MINIMIZATION',updated_at_utc=now,
    owner='R / math and Lean research',branch='huan/codex-gpt',local_head_observed=head,
    window=dict(start_utc='2026-10-24T19:02:59Z',runtime_freeze_target_utc='2026-10-25T02:02:59Z',deadline_utc='2026-10-25T03:02:59Z',
                no_new_algorithm_directions=True,started_ci_terminal_collection_required=True),
    authority=dict(state='FRESH_DIRECT_HUMAN_SCOPE_VERIFIED',receipt='astra-current-public-scope-verification.json',
        development_receipt='development-public-scope-authorization.json',expires_utc='2026-10-25T03:02:59Z',
        coordinator='D exclusively owns Git/index/push/CI/adoption; R no independent push/CI',
        old_207_history='astra-push-authority-correction-20261024T2200Z.json'),
    retained_candidate=dict(path='competitions/floatlib/candidates/f01-d12-scalar-combined',sha256='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172',adoption_changed=False),
    accepted_math_source=proof,
    thin_cache=dict(source='177b86c631f7c156d9f56230caa68546fd3675441dfde8a4954ead398d6eaa03',
        full_gate_reported=True,first_d='PARK_0.97271018555_EXCEEDS_0.97',receipt='development-thin2-first-d-decision.json'),
    biased_rne=dict(state='PROCESS_TERMINATION_UNKNOWN_NOT_MATH_COUNTEREXAMPLE',
        runs=[40151550349,40153361143,40154200932],symptom='VerifyFull invocation returns-15 with empty Lean diagnostics',
        no_resource_or_oom_cause_proven=True,proof_option='astra-biased-rne4-quotient.json',nat_trigger='astra-mul-termination-isolation.json'),
    current_developer_jobs_observed=dev['active_jobs'],developer_updated_utc=dev['updated_at_utc'],
    fallback=dict(candidate='f01-r14-dev-mul-cache-rse1',sha256='35fe53b007e213050399fd07c6d529c9f24545091670aeb48e3a98d12bd0e984',
        runtime_primitive_changed=True,receipt='development-freeze-followup-certified-rounder.json',
        next='Check exact parent/Nat-only/RSE result separately; existing rseAny_eq and FixedWord RSE_toNat match the actual new callee.'),
    diagnosis_skill=dict(name='diagnosing-bugs',phase='Remote red signal exists; minimization/current-parent control still pending; no new fix/representation inferred.',
        local_lean=False,delegated_remote_loop='D original ci-diagnostics compile-only on pinned standard runner'),
    downloads=dict(original_files=4,e_path='E:/Download/FloatLib/20261025-R14',branch_receipt='astra-verify-web-branch-history.json',
        material_index='astra-web-pro-materials/README.md',public_index='development-web-materials-public/index.json',archives_received=0,
        web_pro_state='PRO_DISABLED_USAGE_LIMIT_REACHED; previous actual response backend UNKNOWN'),
    source_audits=['astra-word-add-entry-audit.json','astra-combined-pruning-audit.json','astra-d-support-integration-audit.json'],
    history=dict(path=history.name,sha256=sha256(history.read_bytes()).hexdigest()),
    next_action='Review D final resource-control receipts and rse1 actual gate status; provide read-only lemma/interface review and final evidence handoff by deadline. No source-family expansion.',
    acceptance_target_status='UNACHIEVED_UNLESS_D_LATER_VERIFIES_ALL_REQUIRED_FROZEN_CONFIRMATIONS',
    formal_submission='NOT_AUTHORIZED_NOT_SUBMITTED')
receipt=base/'astra-add2-full-gate-independent-check.json'
receipt.write_text(json.dumps(proof,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
tmp=base/'astra-status.json.tmp';tmp.write_text(json.dumps(state,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');tmp.replace(state_path)
print(json.dumps(dict(updated_utc=now,full_add_gate_verified=True,performance='PARK_REGRESSION',head=head,active_jobs=dev['active_jobs']),ensure_ascii=False,indent=2))
