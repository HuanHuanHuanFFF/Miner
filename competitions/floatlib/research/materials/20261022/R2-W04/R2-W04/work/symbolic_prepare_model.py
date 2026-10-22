#!/usr/bin/env python3
"""Finite symbolic control-flow model, not Lean execution or a Float emulator.

The opaque encode/narrow/import composite is replaced with an arbitrary, pure
word-to-word oracle. Tests exercise rejection and invariants without assuming
any real numerical conversion identity. Python object identity tracks reuse
of the already checked encoded value, not Float bit identity or performance.
"""
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import json

POS_ZERO = 0x00000000
WORDS = (
    0x00000000, 0x80000000, 0x00000001, 0x007fffff,
    0x00800000, 0x3f800000, 0xbf800000, 0x7f7fffff,
    0x7f800000, 0xff800000, 0x7fc00001, 0x7fa00001,
    0xffc00002, 0x80000001,
)

@dataclass(frozen=True, eq=False)
class Encoded:
    original_word: int
    decoded_word: int

class Trace:
    def __init__(self, transform):
        self.transform = transform
        self.events = []
        self.encoded = []

    def encode(self, word, owner, index):
        encoded = Encoded(word, self.transform(word))
        self.encoded.append(encoded)
        self.events.append((owner, 'encode', index))
        return encoded


def prepare(words, trace, owner):
    trace.events.append((owner, 'allocate', len(words)))
    out = []
    k = 0
    while k < len(words):
        assert len(out) == k
        assert all(d.decoded_word == words[i] for i, d in enumerate(out))
        d = trace.encode(words[k], owner, k)
        trace.events.append((owner, 'check', k))
        if d.decoded_word != words[k]:
            trace.events.append((owner, 'none', k))
            return None
        old = out.copy()
        out.append(d)
        trace.events.append((owner, 'push', k))
        assert out[-1] is d
        assert all(out[i] is old[i] for i in range(k))
        k += 1
    assert len(out) == len(words)
    trace.events.append((owner, 'some', k))
    return out


def read(prepared, index):
    return prepared[index].decoded_word if index < len(prepared) else POS_ZERO


def select_path(a, b, trace):
    af = prepare(a, trace, 'A')
    if af is None:
        return 'original', a, b
    bf = prepare(b, trace, 'B')
    if bf is None:
        return 'original', a, b
    return 'checked', af, bf


def run():
    preparation_cases = 0
    paired_cases = 0
    dimension_cases = 0
    negative_examples = []
    # This finite oracle set includes possible conversion rejection. It asserts
    # no facts about the actual opaque Lean conversions.
    alphabet = (0x00000000, 0x80000000, 0x00000001, 0x7f800000, 0x7fc00001)
    arrays = [tuple(x) for n in range(5) for x in product(alphabet, repeat=n)]
    for mask in range(1 << len(alphabet)):
        rejected = {x for i, x in enumerate(alphabet) if (mask >> i) & 1}
        transform = lambda x, r=rejected: (x ^ 1) if x in r else x
        for xs in arrays:
            trace = Trace(transform)
            result = prepare(xs, trace, 'X')
            failures = [i for i, x in enumerate(xs) if transform(x) != x]
            first_failure = failures[0] if failures else len(xs)
            assert len(trace.encoded) == min(first_failure + 1, len(xs))
            pushes = sum(event[1] == 'push' for event in trace.events)
            assert pushes == first_failure
            option_events = [e for e in trace.events if e[1] in ('some', 'none')]
            assert len(option_events) == 1
            assert (result is None) == bool(failures)
            if result is not None:
                assert len(result) == len(xs)
                assert all(result[i] is trace.encoded[i] for i in range(len(xs)))
                for i in list(range(len(xs) + 3)) + [2 ** 32]:
                    assert read(result, i) == (xs[i] if i < len(xs) else POS_ZERO)
            preparation_cases += 1

    short_arrays = [tuple(x) for n in range(4) for x in product(alphabet[:3], repeat=n)]
    for mask in range(8):
        rejected = {x for i, x in enumerate(alphabet[:3]) if (mask >> i) & 1}
        transform = lambda x, r=rejected: (x ^ 1) if x in r else x
        for a, b in product(short_arrays, repeat=2):
            trace = Trace(transform)
            path, first, second = select_path(a, b, trace)
            a_bad = any(transform(x) != x for x in a)
            b_bad = any(transform(x) != x for x in b)
            assert (path == 'original') == (a_bad or b_bad)
            if path == 'original':
                assert first is a and second is b
            if a_bad:
                assert all(owner != 'B' for owner, _, _ in trace.events)
            paired_cases += 1

    # Special raw-word probes demonstrate why a word predicate is necessary.
    transforms = {
        'collapse_negative_zero': lambda x: 0 if x == 0x80000000 else x,
        'canonicalize_nan_payload': lambda x: 0x7fc00000 if x in (0x7fc00001, 0x7fa00001, 0xffc00002) else x,
        'flush_min_subnormal': lambda x: 0 if x == 1 else x,
    }
    for name, transform in transforms.items():
        for word in WORDS:
            trace = Trace(transform)
            result = prepare((word,), trace, 'X')
            if transform(word) != word:
                assert result is None
                negative_examples.append({'model': name, 'raw': f'{word:08x}', 'readback': f'{transform(word):08x}', 'result': 'rejected'})

    # Dimension bookkeeping only: no multiplication or addition is modeled.
    for batch, m, n, p in product(range(3), repeat=4):
        a = (0,) * (batch * m * n)
        b = (0,) * (batch * n * p)
        trace = Trace(lambda x: x)
        path, af, bf = select_path(a, b, trace)
        assert path == 'checked' and len(af) == len(a) and len(bf) == len(b)
        if n == 0:
            assert len(a) == len(b) == 0
        dimension_cases += 1

    return {
        'status': 'PASS',
        'classification': 'SYMBOLIC_CONTROL_FLOW_ONLY',
        'emulates_float_conversion': False,
        'is_lean_compilation': False,
        'is_runtime_or_performance_evidence': False,
        'preparation_cases': preparation_cases,
        'paired_short_circuit_cases': paired_cases,
        'dimension_bookkeeping_cases': dimension_cases,
        'negative_examples': negative_examples,
        'claims': [
            'prefix length and decoded-word equality checked at each model iteration',
            'push preserves old object identities and appends the checked object',
            'all-index reading including positive-zero out of bounds on successful preparation',
            'first failure terminates preparation without processing later words',
            'A failure performs no B preparation',
            'A or B failure selects the original input objects',
            'one Option-like terminal event per prepare call',
        ],
    }


if __name__ == '__main__':
    result = run()
    output = Path(__file__).with_name('symbolic_prepare_results.json')
    output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))
