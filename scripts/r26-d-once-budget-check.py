"""Exhaust finite control episodes and bind artifacts; not Rust/Lean execution."""
from pathlib import Path
import ast
import hashlib
import importlib
import itertools
import json

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/extension90m/route-d'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    builder = importlib.import_module('r26-d-build-once-budget')
    candidate = ROOT / 'candidates/r26-d-658-once-budget'
    rust = (candidate / 'parse.rs').read_bytes()
    assert builder.source() == rust
    for snippet in [b'if budget == 2 && mode == 0', b'return (f.0, f.1, 1);',
                    b'let mut go = if f.2 == 1 { 2u32 } else { 1u32 };',
                    b'while go > 0 && l < lazy', b'go = 1;']:
        assert snippet in rust
    counts = {'episodes': 0, 'model_d1_residual_calls': 0, 'model_d2_residual_calls': 0,
              'no_transfer_episodes': 0, 'transferred_episodes': 0,
              'max_d2_residual_per_episode': 0}
    for length in range(13):
        for wins in itertools.product([False, True], repeat=length):
            for deferred in [False, True]:
                # A later query may continue after a shallow win; at first loss
                # row9 stops. Every potential episode is covered through length12.
                go = 2 if deferred else 1
                spent = 0
                oldspent = 0
                for wins_head in wins:
                    if go == 0:
                        break
                    if wins_head:
                        oldspent += 1
                        spent += go == 2
                    go = 1
                    if not wins_head:
                        go = 0
                assert spent <= int(deferred)
                counts['episodes'] += 1
                counts['model_d1_residual_calls'] += oldspent
                counts['model_d2_residual_calls'] += spent
                counts['transferred_episodes' if deferred else 'no_transfer_episodes'] += 1
                counts['max_d2_residual_per_episode'] = max(counts['max_d2_residual_per_episode'], spent)
    artifacts = []
    for name in ['r26-d-658-selective-depth', 'r26-d-658-selective-depth-proof1',
                 'r26-d-658-once-budget', 'r26-d-658-once-budget-proof1']:
        p = ROOT / 'candidates' / name
        m = json.loads((p / 'manifest.json').read_bytes())
        for file, digest in m['hashes'].items():
            raw = (p / file).read_bytes()
            assert sha(raw) == digest and len(raw) <= 524288
            artifacts.append({'path': (p / file).relative_to(ROOT).as_posix(),
                              'sha256': digest, 'bytes': len(raw)})
    for p in ROOT.glob('scripts/r26-d-*.py'):
        ast.parse(p.read_bytes(), filename=str(p))
    result = {'status': 'PASS_FINITE_CONTROL_MODEL_AND_STATIC_ARTIFACTS', 'counts': counts,
              'candidate_sha256': sha(rust), 'artifacts': artifacts,
              'limits': 'Boolean control-episode model and source/hash checks only; no native compilation, public output/time or Lean gate. Model call totals are not workload coverage or performance.'}
    (OUT / 'd2-state-preflight.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'status': result['status'], 'counts': counts}, indent=2))


if __name__ == '__main__':
    main()
