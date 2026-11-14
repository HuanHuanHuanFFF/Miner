"""Preserve the frozen D fragment and make the one observed match repair."""
from pathlib import Path
import hashlib
import json
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[8]
ROUND = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z'
HERE = Path(__file__).resolve().parent
SOURCE = ROUND / 'development-scalar/quotient-boundary/CellPower-v2.lean.inc'
LOG = ROUND / 'ci-runs/40790240320/download-bb16f0118e144ff29b6e39122b6838ef/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-portable-island3/full-build-output.txt'

def digest(b):
    return hashlib.sha256(b).hexdigest()

def main():
    before = SOURCE.read_bytes()
    expected = '8bea0d97835458a3ffaca3dd3944f2f624bf89d3b1fea04fb43b6f76e89c7313'
    assert digest(before) == expected
    source = before.decode('utf-8')
    old = '''  · have hregion' : num < 8388608 * den := by omega
    have hlog := ratio_log22 num den hd hb.1 hregion'
    simp [Model.NativeBinary32.roundRatScaled, Nat.ne_of_gt hd, hn, hlog,
      hq, hp23, hp24, FloatLib.Numerics.RationalBinary.scaleByPowerOfTwo]
'''
    # Match the original line endings exactly; all other bytes remain untouched.
    newline = '\r\n' if b'\r\n' in before else '\n'
    old = old.replace('\n', newline)
    new = old + '''    cases Nat.decLe (Model.pow2 23) (FloatLib.Numerics.roundQuotientEven num den) with
    | isTrue hle => rfl
    | isFalse hnle =>
        exact False.elim (hnle (by
          simpa only [hp23, hq] using (Nat.le_refl 8388608)))
'''.replace('\n', newline)
    assert source.count(old) == 1
    after = source.replace(old, new).encode('utf-8')
    target = HERE / 'PowerCell-v3.lean.inc'
    target.write_bytes(after)
    assert after.replace(new.encode(), old.encode()) == before
    receipt = {
        'observed_at_utc': datetime.now(timezone.utc).isoformat(),
        'round_start_utc': '2026-10-28T20:38:56Z',
        'round_deadline_utc': '2026-10-29T03:38:56Z',
        'source': {'path': str(SOURCE.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(before), 'sha256': digest(before)},
        'target': {'path': str(target.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(after), 'sha256': digest(after)},
        'actual_ci': {'run': 40790240320, 'candidate_sha256': 'dddf4f7a89934cd6d1a705b7e4bc78db3f6448047a2ee7901c31b6bd50ece0ec',
                      'log_path': str(LOG.relative_to(ROOT)).replace('\\', '/'), 'log_sha256': digest(LOG.read_bytes()),
                      'result': 'POLICY_PASS_ELABORATION_FAILED_20_SECONDS'},
        'changed': 'Only discharge the observed min-normal Nat.decLe match using its proposition and the already established hq/hp23.',
        'unchanged': ['All theorem statements', 'All runtime definitions', 'Both recursion-depth omega proof bodies', 'Original D fragment and frozen candidate'],
        'exact_reversion_to_parent': True,
        'recursion_diagnostic': 'D may set maxRecDepth 4096 and maxHeartbeats 1000000 within existing allowed gate bounds. This fragment does not add options or alter arithmetic for the two depth errors.',
        'verification': {'local_source_bytes': 'VERIFIED', 'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN'},
        'scope': 'Old ContractTensor helper only. No new target implementation, native compilation, CI or Git by B.'
    }
    (HERE / 'power-v3-repair-receipt.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(receipt['target']))

if __name__ == '__main__':
    main()
