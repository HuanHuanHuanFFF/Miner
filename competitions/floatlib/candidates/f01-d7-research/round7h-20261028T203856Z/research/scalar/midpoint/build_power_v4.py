"""Only the two remaining actual PowerCell depth diagnostics from island5."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[8]
ROUND = HERE.parents[2]

def sha(b):
    return hashlib.sha256(b).hexdigest()

def main():
    original = HERE / 'PowerCell-v3.lean.inc'
    before = original.read_bytes()
    assert sha(before) == 'd36fe1296ba5766c67306a6e8fa3f8b950f7a17bcc673afee9b0946da76e08e2'
    linebreak = '\r\n' if b'\r\n' in before else '\n'
    def encode(s):
        return s.replace('\n', linebreak).encode('utf-8')
    pairs = [
        (encode('  have hlold : den * 16777215 ≤ 2 * num := by omega\n'),
         encode('  have hlold : den * 16777215 ≤ 2 * num := by\n    nlinarith only [hl, Nat.zero_le den]\n')),
        (encode('''        hd (by decide) (by decide)
      · omega
      · omega
'''),
         encode('''        hd (by decide) (by decide)
      · change den * 33554431 ≤ 2 * (num * 2)
        calc
          den * 33554431 ≤ 4 * num := hl
          _ = 2 * (num * 2) := by ring
      · omega
'''))
    ]
    after = before
    for old, new in pairs:
        assert after.count(old) == 1
        after = after.replace(old, new)
    reverted = after
    for old, new in reversed(pairs):
        reverted = reverted.replace(new, old)
    assert reverted == before
    target = HERE / 'PowerCell-v4.lean.inc'
    target.write_bytes(after)
    log = ROUND / 'ci-runs/40793795026/download-7ae4fa7bcbe04aca9634d4ddb69ec1ef/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-portable-island5/full-build-output.txt'
    log_bytes = log.read_bytes()
    assert sha(log_bytes) == 'b6a17252e1aaa99a3c225eac26795bb301df7d920f5b5b5a6f273ab6a0853919'
    receipt = {
        'observed_at_utc': datetime.now(timezone.utc).isoformat(),
        'round_start_utc': '2026-10-28T20:38:56Z', 'round_deadline_utc': '2026-10-29T03:38:56Z',
        'parent': {'path': str(original.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(before), 'sha256': sha(before)},
        'target': {'path': str(target.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(after), 'sha256': sha(after)},
        'actual_ci': {'run': 40793795026, 'candidate': 'f01-r24-dev-portable-island5',
                      'log_path': str(log.relative_to(ROOT)).replace('\\', '/'), 'log_sha256': sha(log_bytes),
                      'elapsed_build_seconds': 91, 'remaining_power_error_lines': [1365, 1393],
                      'options_already_tried': {'maxRecDepth': 4096, 'maxHeartbeats': 1000000}},
        'repair_1365': 'From 33554431*d <= 4*n and d >= 0, nlinarith proves 16777215*d <= 2*n without omega coefficient reconstruction.',
        'repair_1393': 'Change the evaluated closed coefficient to 33554431, reuse hl directly, and transport 4*n = 2*(n*2) by ring.',
        'exact_reversion_to_v3': True,
        'unchanged': ['All theorem statements', 'Runtime powerCell', 'minnormal v3 repair', 'All other source', 'Resource options'],
        'core_acceptance_boundary': 'Parent reports independent core13/049b01fa statement+moduleReplay+AX PASS; this does not accept island5, PowerCell, or any new fragment.',
        'verification': {'local_source_and_log_hashes': 'VERIFIED', 'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN'},
        'scope': 'Targeted old ContractTensor source repair only. D owns Git/CI; no local compilation, seed repetition, resource increase, or new runtime.'
    }
    (HERE / 'power-v4-repair-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(receipt['target']))

if __name__ == '__main__':
    main()
