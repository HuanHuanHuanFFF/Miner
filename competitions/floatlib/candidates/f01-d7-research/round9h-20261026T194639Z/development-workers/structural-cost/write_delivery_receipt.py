"""Authenticate this worker's delivery; no candidate, official, Git, or CI mutation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
assert HERE.relative_to(ROOT).as_posix() == 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-workers/structural-cost'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
validation=json.loads((HERE/'validation.json').read_text(encoding='utf-8'))
assert validation['state']=='STATIC_DELTA_AND_FINITE_ADDRESS_MODELS_PASS'
for filename,manifest in (('Kernel-indexed-b2.draft.lean','draft-manifest.json'),
                         ('Kernel-hoisted-b2.draft.lean','hoisted-draft-manifest.json')):
    m=json.loads((HERE/manifest).read_text(encoding='utf-8'))
    assert sha(HERE/filename)==m['draft']['sha256']
assert sha(HERE/'Kernel-hoisted-b2.draft.lean')=='9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1'
start=datetime.fromisoformat('2026-10-26T19:51:54+00:00')
now=datetime.now(timezone.utc)
rows=[dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(p),bytes=p.stat().st_size)
      for p in sorted(HERE.iterdir()) if p.is_file() and p.name!='delivery-manifest.json']
record=dict(at_utc=now.isoformat(),state='READY_FOR_D_REVIEW_UNCOMPILED',
            stage_start_utc=start.isoformat(),stage_budget_minutes=45,
            stage_deadline_utc='2026-10-26T20:36:54Z',elapsed_minutes=(now-start).total_seconds()/60,
            first_checkpoint_at_utc='2026-10-26T19:56Z',
            authority='Parent-delegated engineering source/cost subtask; write only this directory',
            retained_kernel=dict(path=base.relative_to(ROOT).as_posix(),sha256=sha(base),bytes=base.stat().st_size),
            recommended_draft='Kernel-hoisted-b2.draft.lean',
            implementation_state='Complete source with proof attempts; NOT_COMPILED',
            resources=dict(CI_jobs=0,local_Lean_runs=0,local_compiles=0,Git_mutations=0,child_agents=0,
                           tokens='UNKNOWN',cached_input_tokens='UNKNOWN',new_stage_timings='NOT_RUN'),
            verification=dict(static_delta=True,finite_address_steps=validation['row_trace_pairs']+validation['general_guard_steps'],
                              Lean='NOT_RUN',helper_replay='NOT_RUN',axioms='NOT_RUN',full_gate='NOT_RUN',
                              selected_new_MainFull_C='NOT_RUN',new_ASM='NOT_RUN',new_timing='NOT_RUN'),
            next_decision='D may integrate exact source, check full entry plus selected C, and only then decide complete discovery; retain original D+A+B threshold',
            artifact_files=rows)
(HERE/'delivery-manifest.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(state=record['state'],elapsed_minutes=record['elapsed_minutes'],files=len(rows),
                     recommended_sha256=sha(HERE/'Kernel-hoisted-b2.draft.lean'),
                     receipt_sha256=sha(HERE/'delivery-manifest.json')),indent=2))
