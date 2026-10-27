"""Bounded coverage diagnostic from the pinned official BenchSuite input generator.

Generator formulas translated from conjectures-io/conjectures-optimisation-float-kernels
4b7e83841cc0c32c6529f533923c73d33b5ecf97, lean/bench/BenchSuite.lean, MIT.
Official source bytes and its LICENSE are retained in astra-official-source/.
This translation has not itself been compared against Lean execution; outputs are
source-model observations, never timing, formal proof, or holdout confirmation.
"""
import hashlib
import json
import time
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
PLAN = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40129155932/download-4a7e72734bfd446db9a1914af1e7bc01/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
GEN = HERE / 'astra-official-source/lean/bench/BenchSuite.lean'
assert hashlib.sha256(GEN.read_bytes()).hexdigest() == '2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f'
U32, U64 = (1 << 32) - 1, (1 << 64) - 1


def word(seed, index, stream):
    z = (seed + index * 0x9e3779b97f4a7c15 + stream * 0xd1b54a32d192ed03) & U64
    z = ((z ^ (z >> 30)) * 0xbf58476d1ce4e5b9) & U64
    z = ((z ^ (z >> 27)) * 0x94d049bb133111eb) & U64
    return (z ^ (z >> 31)) & U32


def draw(c, i, role, k):
    return word(c['seed'], i, role * 16 + k)


def ctz(w):
    return (w & -w).bit_length() - 1 if w else 32


def clamp(e):
    return max(1, min(254, e))


def ordinary(c, i, j, role):
    w = draw(c, j, role, 1)
    e = c['center'] - min(ctz(w), c['spread']) if c['mag'] == 1 else c['center'] - c['spread'] + w % (2 * c['spread'] + 1)
    shift = 0 if c['scaleBlock'] == 0 else draw(c, i // c['scaleBlock'], role, 2) % (2 * c['scaleShift'] + 1) - c['scaleShift']
    keep = 0x7fffff if c['mantBits'] >= 23 else 0x7fffff ^ ((1 << (23 - c['mantBits'])) - 1)
    frac = draw(c, j, role, 3) & keep
    sign = 0 if draw(c, j, role, 4) % 100 < c['positive'] else 0x80000000
    return sign | (clamp(e + shift) << 23) | frac


def special(c, i, role):
    kinds = [b for b in range(5) if (c['specMask'] >> b) & 1]
    kind = kinds[draw(c, i, role, 5) % len(kinds)] if kinds else 1
    sign = draw(c, i, role, 6) & 0x80000000
    low = draw(c, i, role, 7) & 0x7fffff
    return [sign | 0x7f800000, sign | 0x7f800000 | low | 1,
            sign | 0x7f7fffff, sign | low | 1, sign][kind]


def is_special(c, i, role, row):
    if c['specRate'] == 0:
        return False
    if c['specPlace'] == 1:
        period = c['specPeriod']
        n = i + c['seed'] + 7 * role
        return (n % period if period else n) == 0
    if c['specPlace'] == 2:
        return draw(c, i // c['specBurst'], role, 8) % 100000 < c['specRate']
    if c['specPlace'] == 3:
        return (i % row == 0 or i % row == row - 1) and draw(c, i, role, 9) % 100000 < c['specRate']
    return draw(c, i, role, 9) % 100000 < c['specRate']


def zero(c, i, role):
    w = draw(c, i, role, 10)
    kind = c['zeroKind']
    if kind == 1:
        return 0x80000000
    if kind == 2:
        return w & 0x80000000
    if kind == 3:
        return (w & 0x807fffff) | ((1 + w % 30) << 23)
    return 0


def element(c, i, role, row):
    if c['mag'] == 2:
        return draw(c, i, role, 0)
    if is_special(c, i, role, row):
        return special(c, i, role)
    if c['zeroPct'] > 0 and draw(c, i // c['zeroCluster'], role, 11) % 100 < c['zeroPct']:
        return zero(c, i, role)
    if c['subPct'] > 0 and draw(c, i // c['subBlock'], role, 12) % 100 < c['subPct']:
        return (draw(c, i, role, 13) & 0x807fffff) | 1
    j = draw(c, i, role, 14) % c['codebook'] if c['codebook'] > 0 else i
    return ordinary(c, i, j, role)


def partner(c, i, a):
    w = draw(c, i, 1, 15)
    r = c['relation']
    if r == 1:
        return a
    if r == 2:
        return a ^ 0x80000000
    if r in (3, 7):
        mask = (1 << min(23, c['relParam'])) - 1
        b = (a & ~mask) | (w & mask)
        return b ^ 0x80000000 if r == 3 else b
    if r == 4:
        return element(c, 0, 1, 31)
    if r == 5 and w % 100 < c['relParam']:
        return w & 0x80000000 if c['kernel'] == 'add' else (w & 0x80000000) | 0x3f800000
    if r == 6:
        ea = (a >> 23) & 255
        if ea not in (0, 255):
            return (w & 0x807fffff) | (clamp(ea - c['relParam']) << 23)
    return element(c, i, 1, 31)


def main():
    started = time.perf_counter()
    limit_seconds, maximum_pairs, per_case = 3.0, 25000, 256
    cases = json.loads(PLAN.read_bytes())['cases']
    rows, total, trace = [], 0, hashlib.sha256()
    grouped = defaultdict(lambda: {'pairs': 0, 'eligible_mul': 0, 'eligible_add_align': 0, 'finite_opposite': 0})
    for c in cases:
        if c['kernel'] not in ('add', 'mul') or not c['timed']:
            continue
        n = min(per_case, c['work'])
        counts = {'pairs': n, 'eligible_mul': 0, 'eligible_add_align': 0, 'finite_opposite': 0}
        for j in range(n):
            if total >= maximum_pairs or time.perf_counter() - started >= limit_seconds:
                raise RuntimeError('Bound exceeded')
            lo, hi = j * c['work'] // n, (j + 1) * c['work'] // n
            i = lo + word(c['seed'], j, 63) % (hi - lo)
            a = element(c, i, 0, 31)
            b = partner(c, i, a)
            ea, eb = (a >> 23) & 255, (b >> 23) & 255
            counts['eligible_mul'] += int(1 <= ea <= 254 and 1 <= eb <= 254 and 128 <= ea + eb <= 380)
            counts['eligible_add_align'] += int(24 <= min(ea, eb) and max(ea, eb) <= 252 and abs(ea - eb) <= 7)
            counts['finite_opposite'] += int((a ^ b) == 0x80000000 and ea != 255)
            for v in (i, a, b):
                trace.update(v.to_bytes(4, 'little'))
            total += 1
        group = ':'.join(c['name'].split(':')[:2])
        for k, v in counts.items():
            grouped[group][k] += v
        rows.append({'name': c['name'], 'relation': c['relation'], 'relParam': c['relParam'], 'work': c['work'], **counts})
    result = {
        'at_utc': datetime.now(timezone.utc).isoformat(),
        'purpose': 'Input-domain opportunity diagnostic for already proposed multiply and developer aligned-add routes; no new candidate.',
        'source_plan': str(PLAN.relative_to(ROOT)),
        'source_plan_sha256': hashlib.sha256(PLAN.read_bytes()).hexdigest(),
        'source_run': 40129155932, 'seed': 1425006,
        'official_generator_sha256': hashlib.sha256(GEN.read_bytes()).hexdigest(),
        'sampling': '256 deterministic jittered strata over actual work indices per timed scalar case, stream63 for sampling positions only.',
        'limits': {'seconds': limit_seconds, 'pairs': maximum_pairs},
        'elapsed_seconds': time.perf_counter() - started,
        'pairs': total, 'cases': len(rows), 'trace_sha256': trace.hexdigest(),
        'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'group_counts': dict(grouped), 'case_counts': rows,
        'limitations': 'Python source translation, not cross-checked against Lean-generated operands. Exposed discovery draw only. Pair counts are unweighted, not removable time or speed, and cannot establish formal equivalence or adoption. No saved timing data were modified.'
    }
    Path(__file__).with_suffix('.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: result[k] for k in ['pairs', 'cases', 'elapsed_seconds', 'group_counts']}))


if __name__ == '__main__':
    main()
