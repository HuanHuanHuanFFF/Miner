"""Fixed released-symptom replay and original-byte verification, no compiler run."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()

if __name__ == '__main__':
    run = HERE.parent / 'ci-runs/40609195034'
    index_path = run / 'original-artifact-hashes.json'
    ix = json.loads(index_path.read_bytes())
    assert ix['artifact']['workflow_run']['id'] == 40609195034
    assert ix['artifact']['workflow_run']['head_sha'] == '686a992fc3a9e34a7d78dfdb35bb9545a926651a'
    base = (run / ix['directory']).resolve()
    assert base.is_relative_to(run.resolve())
    total = 0
    for name, meta in ix['files'].items():
        p = (base / name).resolve()
        assert p.is_relative_to(base) and p.stat().st_size == meta['bytes'] and sha(p) == meta['sha256']
        total += meta['bytes']
    suite = base / 'diagnostics/f01-d7-public-suite/public-suite'
    candidate = 'f01-r22-dev-outline-public1'
    source = suite / f'inputs/{candidate}/Kernel.lean'
    assert sha(source) == '88cdf318d952d74df95ecabed5e2bbadeab76d4827af1c4e5fd88e43d9d8f054'
    summary = json.loads((suite / 'summary.json').read_bytes())
    b2, new = summary['results']
    assert b2['candidate'] == 'f01-r15-dev-packed-b2-1' and b2['full_gate'] and len(b2['rounds']) == 25
    assert new['candidate'] == candidate and not new['full_gate'] and new['stage'] == 'statement'
    replay = suite / f'diagnostics/{candidate}/replay.log'
    assert 'exit=-15 in 28.7s' in replay.read_text(encoding='utf-8')
    assert (suite / f'{candidate}-failure-statement-diagnostic.log').stat().st_size == 0
    records = list((suite / f'codegen/{candidate}').glob('*/capture-record.json'))
    assert len(records) == 1
    capture = json.loads(records[0].read_bytes())
    assert capture['timed_out'] is False and capture['gate_returncode'] == 1
    gate = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate) == capture['gate_source_sha256']
    out = {'utc': datetime.now(timezone.utc).isoformat(), 'run': 40609195034,
           'head': ix['artifact']['workflow_run']['head_sha'], 'original_files': len(ix['files']),
           'original_bytes': total, 'index_sha256': sha(index_path), 'candidate_source_sha256': sha(source),
           'B2_control': 'Original fullgate25round PASS; exact new source has no timing/adoption',
           'released_symptom': 'lake build VerifyFull exit=-15 in28.7s; complete build output empty; original statement rejected',
           'capture_timed_out': False, 'gate_source_sha256': sha(gate),
           'known_timeout_semantics': 'Pinned run() timeout kills process group withSIGKILL and returns124. Adapter entry budget900s/build cap1800s, no evidence of a30s cap.',
           'loop_state': 'Original fullgate and failure-only compiler replay both red. This command verifies saved evidence only, not a fresh compile. Minimal real compiler/process/resource feedback loop belongs to D runner diagnostics.',
           'cause': 'UNKNOWN', 'no_type_error_identified': True,
           'ranked_falsifiable_hypotheses': [
               {'rank': 1, 'cause': 'Build resource pressure / scope termination', 'prediction': 'Same-source diagnostic shows cgroupOOM event or memory peak reaching the actual cap before SIGTERM; a declaration prefix narrows it.'},
               {'rank': 2, 'cause': 'External process/session lifecycle termination', 'prediction': 'NoOOM event; process/scope exit evidence identifies parent termination or signal sender. Failure also without codegen observer already weakens observer-only explanation.'},
               {'rank': 3, 'cause': 'Specific proof elaboration or compile expansion', 'prediction': 'A deterministic prefix or declaration boundary fails while its predecessor completes, with phase/resource evidence. A type error, if present, must be captured rather than inferred from empty text.'}],
           'rules': 'Do not raise/relax gate caps, replace original gate, or call diagnostic completion formal acceptance. Separate candidate-only proof repair from runtime changes.'}
    (HERE / 'originals-verified-40609195034-statement-failure.json').write_text(json.dumps(out, indent=2) + '\n')
    print(json.dumps({k: out[k] for k in ('run', 'original_files', 'original_bytes', 'released_symptom', 'cause')}))
