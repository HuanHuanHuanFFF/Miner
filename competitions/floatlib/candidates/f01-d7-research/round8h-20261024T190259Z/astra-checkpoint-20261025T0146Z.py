"""Refresh the single research state after fresh consent and actual CI feedback."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

base=Path(__file__).resolve().parent;root=base.parents[4];now=datetime.now(timezone.utc).isoformat()
auth=json.loads((base/'development-public-scope-authorization.json').read_bytes())
assert len(auth['answers'])==2 and all('授权本轮剩余时间' in a for a in auth['answers'])
verification=dict(checked_utc='2026-10-25T01:38:22Z',source='mcp read_thread direct userMessage',
    message_id='01a1709c-8cc8-73b2-942f-3f14e935ea2c',role='userMessage',
    scope_receipt='development-public-scope-authorization.json',
    scope_receipt_sha256=sha256((base/'development-public-scope-authorization.json').read_bytes()).hexdigest(),
    expires_utc=auth['expires_at_utc'],coordinator='D only; R no independent push/CI',
    historical_207_correction_preserved=True,private_chat_content_copied=False)
(base/'astra-current-public-scope-verification.json').write_text(json.dumps(verification,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
ref_path=base/'astra-remote-ref-observation-20261025T012252Z.json'
ref=json.loads(ref_path.read_bytes());remote=json.loads(ref['source_tool_content'])
remote_observation=dict(observed_utc=ref['observed_utc'],sha=remote['object']['sha'],
    tool_content_sha256=sha256(ref['source_tool_content'].encode()).hexdigest(),
    receipt=ref_path.name,not_a_current_head_assertion=True)

feedback=[]
for name in ['integer-exponent3','word-add-entry1','allword-combined1']:
    p=base/f'development-proof-f01-r14-dev-{name}-40149766137.json'
    f=json.loads(p.read_bytes());output=(root/f['compiler_output']).read_bytes()
    assert sha256(output).hexdigest()==f['compiler_output_sha256']
    feedback.append(dict(candidate=f['candidate'],sha256=f['kernel_sha256'],run=f['run'],
        statement_pass=f['statement_pass'],output_sha256=f['compiler_output_sha256']))
repair=json.loads((base/'astra-repair-40149766137.json').read_bytes())
decision=json.loads((base/'development-thin2-first-d-decision.json').read_bytes())
assert sha256((root/decision['source_result']).read_bytes()).hexdigest()==decision['source_result_sha256']
dev=json.loads((root/'competitions/floatlib/coordination/development-status.json').read_bytes())
record=dict(timestamp_utc=now,state='REAL_COMPILER_REPAIRS_DISPATCHED_UNDER_FRESH_VERIFIED_SCOPE',
    authorization=verification,remote_observation=remote_observation,
    immutable_failed_sources=feedback,repair_request=repair['files'],
    developer_active_jobs_observed=dev['active_jobs'],
    thin2_decision=dict(source='development-thin2-first-d-decision.json',
        source_sha256=sha256((base/'development-thin2-first-d-decision.json').read_bytes()).hexdigest(),
        full_gate_reported=True,performance='PARK_FIRST_CLEAN_D_HEADLINE_FAILED',
        headline=decision['headline'],threshold=decision['required_headline_max'],
        scope='Developer result observed and report hash checked; no R statistical recomputation/adoption.'),
    next='Receive exact40151550349 feedback; repair only real errors or inspect accepted-source costs. No new runtime representation.')
(base/'astra-checkpoint-20261025T0146Z.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
s_path=base/'astra-status.json';s=json.loads(s_path.read_text(encoding='utf-8'))
s['updated_at_utc']=now;s['state']=record['state'];s['current_publication_authority']=verification
s['publication_checkpoint']['historical_only']=True
s['publication_checkpoint']['current_scope_superseded_by']='astra-current-public-scope-verification.json'
s['actual_runtime_candidate_checkpoint']=dict(candidate='f01-r14-dev-allword-combined2',
    sha256='27cc5fc68063659cd1ead7aa0d963eae2251207a48d8f659d9b54355bafd0167',
    state='STATEMENT_RUNNING_40151550349_SOURCE_a2cc9bf0')
s['proof_status']='FIRST_FIVE_STATEMENT_FAILED_40149766137; THREE_REPAIRED_SOURCES_RUNNING_40151550349'
s['active_repair']=dict(receipt='astra-repair-40149766137.json',state='INTEGRATED_BY_D_NOT_YET_ACCEPTED')
s['latest_peer_status_observed']=dict(updated_utc=dev['updated_at_utc'],active_jobs=dev['active_jobs'])
s['next_action']=record['next']
for name in ['20261025T010810987563Z-r14-development-combined-capacity-review.md',
    '20261025T011447297937Z-r14-development-fresh-authorization-ci-running.md',
    '20261025T011651552963Z-r14-development-two-column-prepared-pair-exploration.md',
    '20261025T012100731050Z-r14-development-real-compile-errors-math-repair.md',
    '20261025T012624603661Z-r14-development-thin-d-running-and-word-fixes.md',
    '20261025T013745457836Z-r14-development-math-repairs-integrated-next-plan.md',
    '20261025T014159151907Z-r14-development-thin-full-negative-math-repair-running.md']:
    if name not in s['processed_shared_message_ids']:s['processed_shared_message_ids'].append(name)
for pattern in ['astra-*401497*','astra-combined-pruning-audit.*','astra-current-public-scope-verification.json',
                'astra-checkpoint-20261025T0146Z.json','astra-add-retained-codegen-audit.*']:
    for p in base.glob(pattern):
        rel=p.relative_to(root).as_posix()
        if rel not in s['artifacts']:s['artifacts'].append(rel)
tmp=base/'astra-status.json.tmp';tmp.write_text(json.dumps(s,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');tmp.replace(s_path)
print(json.dumps(dict(updated_utc=now,verified_direct_human_authority=True,
    failed_source_logs_checked=len(feedback),active_jobs=dev['active_jobs'],next=record['next']),ensure_ascii=False,indent=2))
