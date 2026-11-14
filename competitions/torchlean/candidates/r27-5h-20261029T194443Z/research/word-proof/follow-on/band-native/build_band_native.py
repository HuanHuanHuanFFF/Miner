"""Owned next-round band cost recipe. Whole upstream source stays in memory."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROUND = HERE.parents[3]
PIN = '1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
COMPACTOR = '4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def once(text, before, after):
    assert text.count(before) == 1, (before, text.count(before))
    return text.replace(before, after, 1)


def transform(raw, submission=23, variant='band64-four-column-cost'):
    assert submission == 23 and variant == 'band64-four-column-cost'
    assert sha(raw) == PIN
    cp = HERE / 'frozen_compact_public23.py'
    assert sha(cp.read_bytes()) == COMPACTOR
    compact, _, _ = load(cp, 'r27_band_compactor').transform(raw, 'proof')
    assert sha(compact) == 'fc7b1e9e1b258f5254c75e046972fdc3bdc630b5b20fb35c9821839883c62019'
    s = compact.decode()
    s = once(s, 'def kernels:Kernels where', 'def retainedKernels:Kernels where')
    s = once(s, 'theorem correct:Obligation kernels:=', 'theorem retainedCorrect:Obligation retainedKernels:=')
    s = once(s, '[Obligation,kernels,h,', '[Obligation,retainedKernels,h,')
    helper = (HERE / 'BandNative.lean.inc').read_text(encoding='utf8')
    actual = '\ndef kernels:Kernels := { retainedKernels with dense := ⟨R27Band.linear,retainedKernels.dense.2⟩ }\n'
    s = once(s, 'end Submission\n', helper + actual + 'end Submission\n')
    result = s.encode()
    assert len(result) <= 256000, len(result)
    assert b'theorem correct:' not in result
    assert b'theorem retainedCorrect:Obligation retainedKernels:=' in result
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--receipt', type=Path, required=True)
    args = parser.parse_args()
    result = transform(args.source.read_bytes())
    policy = load(ROUND / 'development/native/patch_public.py', 'r27_band_policy').policy_check(result)
    report = {'at_utc': datetime.now(timezone.utc).isoformat(),
              'state': 'NEXT_ROUND_COST_SOURCE_ONLY_NOT_COMPILED_NOT_QUEUED',
              'base_submission': 23, 'base_sha256': PIN,
              'candidate_sha256': sha(result), 'candidate_bytes': len(result),
              'free_bytes': 256000-len(result),
              'runtime_sha256': sha((HERE/'BandNative.lean.inc').read_bytes()),
              'runtime_bytes': (HERE/'BandNative.lean.inc').stat().st_size,
              'recipe_sha256': sha(Path(__file__).read_bytes()),
              'compactor_sha256': COMPACTOR, 'policy': policy,
              'new_correct': False,
              'retained_proof': 'Original retainedCorrect binds retainedKernels only. No assertion for new kernels.',
              'runtime_scope': 'Whole dense.linear for compatible finite shape/range; four columns share grouped input/index loads; final outW%4 columns and outer failures use public23. Other kernels remain public23.',
              'terminal': 'Bias-aware Yp/Yu guard range<=58, pair rebase, original YL/YD, original Yai on zero sentinel; act relu outside terminal.',
              'cost_boundary': 'Includes BX/BV scans, global pair guard, all weight factor preparation, per-row groups/index arrays, every gather, block/group carry, original bias/finalizer/fallback and output allocation/destruction in an eventual full-call harness.',
              'risks': ['Nat recursion per MAC may cost more than the original USize loop.',
                        'Four-column sharing loses original four-row weight reuse.',
                        'Weight preparation adds a pass even for batch1.',
                        'Array UInt32 entries remain pointer-sized.',
                        'New source and its actual metadata/partition/getter proofs have not been accepted.'],
              'finite_evidence': '../../band-full-model-census-v3.json and ../../band-guard-counterexamples.json model the arithmetic/guards; actual Lean source has additional scheduling and tail fallback, not executed.',
              'priority': 'Hold outside current frozen candidates. First small compile plus complete native cost only if next-round owner selects this route; do not build large proof first.',
              'publication': 'Only owned fragment/recipe/compactor/receipt. Reconstructed whole source stayed in memory; no source file written.'}
    args.receipt.write_text(json.dumps(report, indent=2), encoding='utf8')
    print(json.dumps({k: report[k] for k in ('state', 'candidate_sha256', 'candidate_bytes', 'free_bytes', 'runtime_bytes', 'policy')}))


if __name__ == '__main__':
    main()
