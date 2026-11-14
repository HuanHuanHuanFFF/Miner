from pathlib import Path
from fractions import Fraction
import collections
import datetime
import hashlib
import json

H = Path(__file__).resolve().parent
PARENT_COUNTER = H.parent.parent / 'fp-cost/counterexample-radius718.json'

def round53(value):
    shift = max(value.bit_length() - 53, 0)
    if shift == 0:
        return value
    quotient, remainder = divmod(value, 1 << shift)
    halfway = 1 << (shift - 1)
    return (quotient + (remainder > halfway or (remainder == halfway and quotient & 1))) << shift

def simulate(mantissas):
    a = (1 << 24) - 1
    accumulator = exact = 0
    groups = collections.defaultdict(list)
    for i, b in enumerate(mantissas, 1):
        product = a * b
        exact += product
        old = accumulator
        accumulator = round53(old + product)
        local_error = accumulator - old - product
        groups[(i - 1).bit_length()].append(local_error)
    return accumulator - exact, [
        {'ceil_log2_index': j, 'count': len(values), 'local_error_units': dict(collections.Counter(values)),
         'sum_error_units': sum(values)}
        for j, values in sorted(groups.items())]

parent = json.loads(PARENT_COUNTER.read_text())
assert parent['at_utc'] < '2026-10-29T23:20:00Z'
assert parent['xword_repeated'] == '0x3fffffff' and parent['n'] == 512
words = [int(word, 16) for word in parent['ywords']]
assert all(((word >> 23) & 255) == 127 for word in words)
mantissas = [(1 << 23) + (word & 0x7fffff) for word in words]
error, groups = simulate(mantissas)
assert error == 2720
for group in groups:
    j = group['ceil_log2_index']
    expected = 0 if j <= 5 else 1 << (j - 6)
    assert set(group['local_error_units']) == {expected}

family = []
for L in range(5, 17):
    terms = [((1 << 24) - 1)] * 32
    for j in range(6, L + 1):
        delta = 3 * (1 << (j - 6))
        terms.extend([((1 << 24) - delta)] * (1 << (j - 1)))
    assert len(terms) == 1 << L
    actual, trace = simulate(terms)
    bound = Fraction((1 << (2 * L)) - (1 << 10), 96)
    family.append({'L': L, 'n': len(terms), 'error_units': actual,
                   'aligned_bound_units': str(bound), 'saturates_bound': actual == bound,
                   'all_operands_normal': all((1 << 23) <= m < (1 << 24) for m in terms)})

result = {
    'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'state': 'EXACT_FINITE_BINade_TRACE_AND_FAMILY_NOT_LEAN_PROOF',
    'source_counter_at_utc': parent['at_utc'],
    'source_counter_sha256': hashlib.sha256(PARENT_COUNTER.read_bytes()).hexdigest(),
    'source_created_before_freeze': True,
    'source_first_content_read_by_A_after_freeze': True,
    'unit': '2^-46',
    'n512_error_units': error,
    'n512_global_binade_sum_bound_units': str(Fraction((1 << 18) - 1, 96)),
    'n512_first32_exact_contribution_removed_units': str(Fraction((1 << 10) - 1, 96)),
    'n512_aligned_bound_units': 2720,
    'n512_each_local_step_saturates_aligned_binade_bound': True,
    'n512_groups': groups,
    'constructed_family': family,
    'limitations': 'This traces exact 53-bit RNE integer arithmetic for a structured all-normal family. The universal one-third bound is separately paper-derived; actual Float API/producer/whole-kernel Lean correctness is not supplied here. No frozen radius or candidate changed; no performance claim.',
    'selection_basis': 'Pre-freeze counter and existing SUM3 half-ULP library interface, independent of post-freeze FP23 performance data.'
}
(H / 'BINADE-ERROR-TRACE.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({'n512_error_units': error, 'groups': groups, 'family': family}, indent=2))
