"""Lightweight source/model checks, never a Lean or native compilation claim."""
from pathlib import Path
import hashlib
import importlib.util
import json
import random
import sys
from datetime import datetime, timezone

sys.dont_write_bytecode = True

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-broad'

def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod

t = load('r26_existing_tiered', OLD / 'exact_dot_tiered_model.py')
m = t.m

def source_checks():
    records = []
    base = (ROOT / 'competitions/torchlean/candidates/r25-90m-20261029T064916Z/development/contract-port/norm-cache-proof1/Kernel.lean').read_bytes()
    for name in ('fp1', 'fp-word2', 'fp-word-conv3', 'fp-raw4', 'fp-raw5', 'fp-word-conv6-local', 'fp-raw7-local', 'word-official8-draft'):
        raw = (HERE / name / 'Kernel.lean').read_bytes()
        receipt = json.loads((HERE / name / 'source-receipt.json').read_text(encoding='utf-8'))
        assert hashlib.sha256(raw).hexdigest() == receipt['sha256']
        assert len(raw) == receipt['bytes'] < 256000
        source = raw.decode('utf-8')
        prefix = source[:source.index('namespace Submission.FastMul')].rstrip()
        prefix = prefix.replace('def retainedKernels : Kernels where', 'def kernels : Kernels where')
        prefix = prefix.replace('theorem retainedCorrect : Obligation retainedKernels := by', 'theorem correct : Obligation kernels := by')
        prefix = prefix.replace('simp only [Obligation, retainedKernels, specKernels,', 'simp only [Obligation, kernels, specKernels,')
        assert prefix == base.decode('utf-8').rstrip()
        assert 'theorem correct :' not in source
        assert 'sorry' not in source and 'unsafe ' not in source
        assert 'def referencePrepared' not in source
        assert 'return 0x7fc00000' not in source
        records.append({'id': name, 'sha256': receipt['sha256'], 'base_prefix_roundtrip': True,
                        'new_correct_theorem': False, 'old_rejection_replay_present': False})
    return records

def model_checks():
    fixtures = json.loads((OLD / 'exact-dot-cost-fixtures.json').read_text(encoding='utf-8'))
    rows = []
    counts = {'word64': 0, 'word128': 0, 'original_fallback': 0}
    for f in fixtures['dot_cases']:
        a, b = f['a'], f['b']
        c = m.cache(a, b)
        if t.eligible64(c):
            actual, tier = t.model64(c), 'word64'
        elif c['eligible']:
            actual, tier = m.native_model(c), 'word128'
        else:
            actual, tier = None, 'original_fallback'
        if actual is not None:
            assert actual == f['expected'], f['id']
        counts[tier] += 1
        rows.append({'id': f['id'], 'tier': tier, 'model_checked': actual is not None})
    rng = random.Random(26029)
    random_count = 0
    for kind, low, high in [('narrow', 121, 125), ('wide128', 89, 118), ('outside', 1, 254)]:
        for n in (0, 1, 2, 7, 32, 127):
            for rep in range(20):
                a = [m.normal_word(rng, low, high) for _ in range(n)]
                b = [m.normal_word(rng, low, high) for _ in range(n)]
                if n and rep % 3 == 0:
                    a[rng.randrange(n)] = rng.randrange(2) << 31
                expected, c = m.oracle(a, b)
                if t.eligible64(c):
                    assert t.model64(c) == expected
                elif c['eligible']:
                    assert m.native_model(c) == expected
                random_count += 1
    return {'fixture_count': len(rows), 'fixture_tiers': counts, 'fixtures': rows,
            'random_normal_or_zero_count': random_count,
            'scope': 'Python exact Fraction and word models only; no fresh native or Lean claim'}

def raw_native(a, b):
    c = m.cache(a, b)
    if not c['finite'] or not c['matched']:
        return None, 'original_fallback'
    n = len(a)
    width = 48 + c['hi'] - c['lo'] + ((n - 1).bit_length() if n > 1 else 0)
    if n > 1 << 20 or width > 128:
        return None, 'original_fallback'
    nz = bool(n)
    acc = 0
    pos = neg = 0
    for wa, wb in zip(a, b):
        ma, ia, sa = m.parts(wa)
        mb, ib, sb = m.parts(wb)
        prod = ma * mb
        negative = sa ^ sb
        nz = nz and prod == 0 and negative
        # Lean UInt32 shift subtraction may wrap for zero terms only.
        shift = ((ia + ib - c['lo']) & 0xffffffff) % 64 if width <= 62 else ia + ib - c['lo']
        term = prod << shift if prod else 0
        if width <= 62:
            acc = (acc + (-term if negative else term)) & m.MASK
            signed = acc - (1 << 64) if acc >> 63 else acc
            assert abs(signed) < 1 << 62
        elif negative:
            neg += term
            assert neg < 1 << 128
        else:
            pos += term
            assert pos < 1 << 128
    total = (acc - (1 << 64) if acc >> 63 else acc) if width <= 62 else pos - neg
    magnitude = abs(total)
    actual = m.round_word(total < 0 if total else nz, magnitude & m.MASK, magnitude >> 64, c['lo'] - 298)
    return actual, 'word64' if width <= 62 else 'word128'

def raw_model_checks():
    fixtures = json.loads((OLD / 'exact-dot-cost-fixtures.json').read_text(encoding='utf-8'))
    counts = {'word64': 0, 'word128': 0, 'original_fallback': 0}
    for f in fixtures['dot_cases']:
        actual, tier = raw_native(f['a'], f['b'])
        counts[tier] += 1
        if actual is not None:
            assert actual == f['expected'], f['id']
    rng = random.Random(2602904)
    count = 0
    subnormal_fast = 0
    for n in (0, 1, 2, 7, 32, 64):
        for rep in range(80):
            def word():
                if rep % 4 == 0:
                    return (rng.getrandbits(1) << 31) | rng.randrange(1 << 23)
                if rep % 4 == 1:
                    return m.normal_word(rng, 1, 8) if rng.randrange(2) else (rng.getrandbits(1) << 31) | rng.getrandbits(23)
                return m.normal_word(rng, 89, 118) if rep % 4 == 2 else m.normal_word(rng, 1, 254)
            a, b = [word() for _ in range(n)], [word() for _ in range(n)]
            expected, _ = m.oracle(a, b)
            actual, tier = raw_native(a, b)
            if actual is not None:
                assert actual == expected, (n, rep)
                subnormal_fast += any(0 < (w & 0x7fffffff) < 0x800000 for w in a + b)
            count += 1
    return {'old_fixture_count': len(fixtures['dot_cases']), 'old_fixture_tiers': counts,
            'extra_random_cases': count, 'extra_with_subnormal_and_word_tier': subnormal_fast,
            'scope': 'Raw finite word64/128 Python arithmetic model, not native or proof evidence'}

def main():
    report = {'updated_utc': datetime.now(timezone.utc).isoformat(),
              'source_checks': source_checks(), 'model_checks': model_checks(),
              'raw_model_checks': raw_model_checks(),
              'lean_compile': 'NOT_RUN', 'native_compile': 'NOT_RUN',
              'all_input_proof': 'NOT_PROVED', 'official_full_model': 'PENDING_ROOT_RUNNER'}
    (HERE / 'preflight.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: v for k, v in report.items() if k != 'model_checks'}, indent=2))
    print(json.dumps({k: v for k, v in report['model_checks'].items() if k != 'fixtures'}, indent=2))

if __name__ == '__main__':
    main()
