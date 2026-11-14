"""Close this implementation role only after the common fixed deadline."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent.parent
DEADLINE = datetime.fromisoformat('2026-10-29T09:55:15+00:00')
START = datetime.fromisoformat('2026-10-29T09:02:18+00:00')
MAIN_SHA = 'ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()

def save(path, data):
    path.write_text(json.dumps(data, indent=2) + '\n', encoding='utf-8')

def main():
    now = datetime.now(timezone.utc)
    assert now >= DEADLINE, 'Do not close the active role before the shared deadline'
    sources = []
    for path in sorted(HERE.glob('*/Kernel.lean')):
        receipt = json.loads((path.parent / 'source-receipt.json').read_text(encoding='utf-8'))
        assert sha(path) == receipt['sha256'] and path.stat().st_size == receipt['bytes']
        sources.append({'id': path.parent.name, 'sha256': sha(path), 'bytes': path.stat().st_size})
    assert sha(HERE / 'fp-word-conv6-local/Kernel.lean') == MAIN_SHA
    policy = json.loads((HERE / 'policy-preflight.json').read_text(encoding='utf-8'))
    assert any(r['id'] == 'fp-word-conv6-local' and r['sha256'] == MAIN_SHA and r['passed'] for r in policy['results'])
    root_status = json.loads((ROUND / 'development-status.json').read_text(encoding='utf-8'))
    report = {
        'role': 'Dnative_Sol', 'state': 'ROLE_WINDOW_ENDED',
        'shared_start_utc': '2026-10-29T08:55:15Z', 'actual_join_utc': START.isoformat(),
        'common_deadline_utc': DEADLINE.isoformat(), 'finished_utc': now.isoformat(),
        'role_elapsed_wall_seconds': (now - START).total_seconds(),
        'window_complete': True, 'overall_champion_goal_complete': False,
        'main_candidate': 'fp-word-conv6-local', 'main_sha256': MAIN_SHA,
        'main_original_intake_policy': 'PASS',
        'fresh_Lean_native_evidence_reviewed': False,
        'all_input_proof': 'NOT_PROVED', 'full_model_score': 'UNKNOWN',
        'latest_root_status_snapshot': root_status,
        'source_inventory': sources,
        'existing_CI_owner': 'Droot; collect existing 40852769757 terminal artifacts',
        'follow_on_sources': ['fp-raw7-local', 'word-official8-draft'],
        'local_native_Lean_builds': 'NONE_BY_INSTRUCTION', 'Git_CI_actions': 'NONE_BY_THIS_ROLE',
        'post_0938_new_runtime_variants_or_job_requests': 'NONE',
        'tokens': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN', 'model_CPU': 'UNKNOWN',
        'elapsed_time_is_not_model_CPU': True,
    }
    save(HERE / 'closeout.json', report)
    state = json.loads((HERE / 'status.json').read_text(encoding='utf-8'))
    state.update(state='ROLE_WINDOW_ENDED', finished_utc=now.isoformat(),
                 current_work='No new work; existing CI collection belongs to Droot',
                 fresh_native_evidence_reviewed=False)
    save(HERE / 'status.json', state)
    inventory = json.loads((HERE / 'source-inventory.json').read_text(encoding='utf-8-sig'))
    inventory.update(updated_utc=now.isoformat(), existing_retry_run='40852769757',
                     native_compile='UNKNOWN_NO_FRESH_NATIVE_EVIDENCE_REVIEWED',
                     full_model_measurement='UNKNOWN_NO_FRESH_NATIVE_EVIDENCE_REVIEWED',
                     role_state='ROLE_WINDOW_ENDED')
    save(HERE / 'source-inventory.json', inventory)
    (HERE / 'HANDOFF.md').write_text('''# R26 native implementation — final role handoff

- Common deadline09:55:15 UTC reached; actual join09:02:18. `closeout.json` records wall time, not model CPU. Strict files only; no local Lean/native build, Git/CI, child dispatch, or post09:38 new runtime variant/job request by this role.
- Frozen main `fp-word-conv6-local/Kernel.lean`, **60479B / ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540**, exact original intake/policy PASS. Actual new kernels remain UNPROVED; retainedCorrect certifies only the preserved bcb817 retainedKernels. No fresh native evidence was reviewed here.
- Follow-on `fp-raw7-local` **63751B / 890eb4da…0bd639**, policy PASS: fused raw/Float producer, no encoded array, finite subnormal word tiers. `word-official8-draft` **63852B / ec81a74f…21c0bce**, policy PASS: no FP attempt, one official terminal finishWord. Both NOT_COMPILED and unadopted. Old global-instance policy failures are preserved.
- `READY.json`, `source-inventory.json`, `build_native.py`, and `file-hashes.json` bind artifacts. Bias remains inside the same exact dot; all special/out-of-width inputs retain original dotFn semantics; zero output extents precede preparation.
- Source/model evidence only: 62 existing fixtures and360 additional normal/zero cases;480 raw cases (195 subnormal-containing fast cases);60840 directed rounding cases;22724 symbolic output sequences. `preflight.json`, `rounding-falsifier.json`, `index-falsifier.json` contain exact scopes. These do not establish native correctness or speed.
- Prior CI40849705068 failed at host loguru import;40851060907 failed at the first start-cutoff assertion (commands0/results0). Both produced no candidate compile/checksum/score. Existing same-source retry **40852769757 / commit12e6d73f**, dispatched09:50:23, is Root-owned; final collection/analysis must use its immutable artifact. Score remains UNKNOWN in this role.
- Next minimum action: collect that existing run; inspect actual build errors or selected C/ASM and all original30cells×6workloads pairs. `inspect_native_c.py` is ready. Historical R24 helpers already had scalar UInt64 state; see `HISTORICAL-C-EVIDENCE.md`. Raw factor bridge, `PROOF-FRONTIER.md`, and optional133-check `FallbackFixtureMain.lean` remain NOT_COMPILED. No full proof, champion or adoption claim.
''', encoding='utf-8')
    manifest = {p.relative_to(HERE).as_posix(): {'bytes': p.stat().st_size, 'sha256': sha(p)}
                for p in HERE.rglob('*') if p.is_file() and p.name != 'file-hashes.json'}
    save(HERE / 'file-hashes.json', manifest)
    print(json.dumps({'state': report['state'], 'finished_utc': report['finished_utc'],
                      'main_sha256': MAIN_SHA, 'files': len(manifest),
                      'fresh_native_evidence_reviewed': False, 'score': 'UNKNOWN'}, indent=2))

if __name__ == '__main__':
    main()
