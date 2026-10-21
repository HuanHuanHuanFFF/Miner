"""Finite checks of the inherited-match invariant; no production DP or quality claim."""
from pathlib import Path
import hashlib
import itertools
import json
import random

ROOT = Path(__file__).resolve().parents[1]


def valid(s, p, length, distance):
    return (3 <= length <= 258 and 1 <= distance <= min(p, 32768)
            and p + length <= len(s)
            and s[p:p+length] == s[p-distance:p-distance+length])


def records(s, p):
    found = []
    for distance in range(1, p+1):
        length = 0
        while length < min(258, len(s)-p) and s[p+length] == s[p-distance+length]:
            length += 1
        if length >= 3:
            found.append((length, distance))
    return found


def check_trajectory(s, p0, pe, variant):
    # No cost/choice dependence: original XL/XD depends on max record extent only.
    xl = xd = 0
    observations = 0
    for i in range(pe-1, p0-1, -1):
        rows = records(s, i)
        if variant == 1:
            rows = rows[::2]
        elif variant == 2:
            rows = rows[1::2]
        elif variant == 3:
            rows.reverse()
        prev, pd = i+2, 0
        for length, distance in rows:
            assert valid(s, i, length, distance)
            if i+length > prev:
                prev, pd = i+length, distance
        el = min(258, xl+1)
        inherited = xl >= 3 and xd >= 1 and xd <= i and s[i] == s[i-xd]
        if inherited:
            assert valid(s, i, el, xd)
            observations += 1
        if inherited and i+el > prev:
            xl = el
        else:
            xl, xd = prev-i, pd
        assert xd == 0 or valid(s, i, xl, xd)
    return observations


def mixing_witness():
    rng = random.Random(26012)
    for _ in range(20000):
        s = bytes(rng.randrange(2)+97 for _ in range(32))
        for q in range(2, len(s)-3):
            rows = records(s, q)
            if not rows:
                continue
            longest = max(rows)
            for shorter in rows:
                if shorter[0] < longest[0] and shorter[1] <= q-1 and s[q-1] == s[q-1-shorter[1]]:
                    length = min(258, longest[0]+1)
                    if not valid(s, q-1, length, shorter[1]):
                        return {'input_ascii': s.decode(), 'original_position': q,
                                'original_valid_pair': list(longest),
                                'alternative_valid_pair': list(shorter),
                                'incorrect_mixed_pair_at_predecessor': [length, shorter[1]],
                                'incorrect_mixed_pair_byte_valid': False}
    raise AssertionError('Missing mixed-length/distance witness')


def main():
    trajectories = observations = 0
    for n in range(3, 11):
        for symbols in itertools.product(b'ab', repeat=n):
            s = bytes(symbols)
            for pe in (n, max(1, n-2)):
                for variant in range(4):
                    observations += check_trajectory(s, 0, pe, variant)
                    trajectories += 1
    for n in (257, 258, 259, 260, 513):
        s = (b'abba'*((n+3)//4))[:n]
        for pe in (n, n-2, min(n, 258)):
            for variant in range(4):
                observations += check_trajectory(s, max(0, pe-10), pe, variant)
                trajectories += 1
    result = {'status': 'VERIFIED_FINITE_INHERITED_MATCH_INVARIANT_WITH_MIXING_COUNTEREXAMPLE',
              'trajectories': trajectories, 'valid_inherited_prefix_observations': observations,
              'mixing_counterexample': mixing_witness(),
              'assumptions': ['Every observed record max length/distance is byte valid.',
                              'Only original XL/XD recurrence drives inherited candidates.',
                              'Finite selection policies all/even/odd/reversed; tail p0/pe and 258 cap exercised.'],
              'limits': ['This checks a finite invariant model, not original Rust/Lean obligations, native trajectory or encoder quality.',
                         'Original cache record validity is an explicit assumption; production candidate still needs exact gate.',
                         'Changing best/choice must not replace original XL or XD by a different winning pair.'],
              'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    out = ROOT/'evidence/round26/route-b/overlap-invariant-model.json'
    out.write_bytes((json.dumps(result, indent=2)+'\n').encode())
    print(json.dumps(result))


if __name__ == '__main__':
    main()
