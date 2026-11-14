"""Exact interpreter of public addLimbs64's dirty slots, not native profiling."""
from pathlib import Path
import hashlib
import importlib.util
import json

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('r24_mixer_shape', HERE / 'mixer_firstnorm_model.py')
model = importlib.util.module_from_spec(spec)
spec.loader.exec_module(model)


def decode(word):
    exponent = (word >> 23) & 255
    assert exponent < 255
    mantissa = (word & 0x7fffff) + ((1 << 23) if exponent else 0)
    return mantissa, max(exponent - 1, 0), bool(word >> 31)


def accumulate(slots, magnitude, shift):
    index, remainder = divmod(shift, 32)
    assert index + 1 < 18
    low = (magnitude % (1 << (32 - remainder))) << remainder
    high = magnitude >> (32 - remainder)
    slots[index] += low
    slots[index + 1] += high
    return max(slots).bit_length()


def fold_value(slots):
    value = wide_steps = nonzero_steps = 0
    for slot in reversed(slots):
        value = (value << 32) + slot
        wide_steps += value >= 1 << 63
        nonzero_steps += value != 0
    return value, wide_steps, nonzero_steps


def inspect(words):
    parts = [decode(word) for word in words]
    base = min((i for m, i, _ in parts if m), default=255)
    positive = [0] * 18
    negative = [0] * 18
    square = [0] * 18
    dirty_bits = 0
    for mantissa, index, sign in parts:
        shift = max(index - base, 0)
        dirty_bits = max(dirty_bits, accumulate(negative if sign else positive, mantissa, shift))
        dirty_bits = max(dirty_bits, accumulate(square, mantissa * mantissa, 2 * shift))
    pos, pos_wide, pos_live = fold_value(positive)
    neg, neg_wide, neg_live = fold_value(negative)
    q, q_wide, q_live = fold_value(square)
    exact_s = sum((-1 if sign else 1) * mantissa * (1 << max(index - base, 0))
                  for mantissa, index, sign in parts)
    exact_q = sum(mantissa * mantissa * (1 << (2 * max(index - base, 0)))
                  for mantissa, index, _ in parts)
    assert pos - neg == exact_s and q == exact_q
    assert max(positive + negative) < len(words) * (1 << 32)
    assert max(square) < len(words) * (1 << 46)
    return {
        'n': len(words), 'base': base, 'max_dirty_slot_bits': dirty_bits,
        'dirty_slot_reaches_63bit_boundary': dirty_bits > 63,
        'source_norm_scans': 3 * len(words), 'source_array_modify_calls': 4 * len(words),
        'source_limbValA_steps': 54,
        'fold_result_at_least_2pow63_steps': pos_wide + neg_wide + q_wide,
        'nonzero_fold_steps': pos_live + neg_live + q_live,
        'sum_bits': abs(exact_s).bit_length(), 'square_bits': exact_q.bit_length(),
    }


def main():
    seed = 24292317
    groups = []
    for profile in ('typical', 'scale', 'boundary'):
        tokens, channels = model.dimensions(seed, profile)
        for kind in ('normal', 'wide', 'sparse'):
            words = model.m.gen(kind, tokens * channels, seed + 999)
            rows = [inspect(words[i * channels:(i + 1) * channels]) for i in range(tokens)]
            groups.append({'profile': profile, 'kind': kind, 'tokens': tokens,
                           'channels': channels, 'rows': rows})
    # Largest public norm width and a constructed shift producing the largest
    # allowed high square contribution (even shift modulo32 is30).
    directed = inspect([0x00ffffff] + [0x087fffff] * 256)
    assert directed['n'] == 257
    all_rows = [row for group in groups for row in group['rows']]
    summary = {
        'rows': len(all_rows), 'input_words': sum(row['n'] for row in all_rows),
        'max_dirty_slot_bits': max(row['max_dirty_slot_bits'] for row in all_rows),
        'dirty_slots_at_least_2pow63_rows': sum(row['dirty_slot_reaches_63bit_boundary'] for row in all_rows),
        'source_array_modify_calls': sum(row['source_array_modify_calls'] for row in all_rows),
        'source_limbValA_steps': sum(row['source_limbValA_steps'] for row in all_rows),
        'fold_result_at_least_2pow63_steps': sum(row['fold_result_at_least_2pow63_steps'] for row in all_rows),
    }
    report = {
        'scope': 'Own-seed exact source-operation model, not selected native C/ASM, GMP call counts or timing.',
        'seed': seed, 'public_all_profile_max_norm_width': 257,
        'universal_dirty_slot_bounds': {
            'sum_slot': 'slot < n * 2^32',
            'square_slot': 'slot < n * 2^46 (square shift is even, high split shifts by >=2)',
            'all_current_public_dimensions': 'n<=257 implies every dirty slot<2^55<2^63',
            'more_general_safe_n': 'n<=2^17 implies all dirty slots<2^63',
        },
        'summary': summary, 'directed_width257': directed, 'groups': groups,
        'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    }
    (HERE / 'dirty-moment-results.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'summary': summary, 'directed_width257': directed}, indent=2))


if __name__ == '__main__':
    main()
