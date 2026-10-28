"""Independent finite boundary checks for the cold-only extreme MUL shortcut."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import struct

HERE = Path(__file__).resolve().parent
fp = lambda u: struct.unpack('<f', struct.pack('<I', u))[0]


def bits(x):
    try:
        return struct.unpack('<I', struct.pack('<f', x))[0]
    except OverflowError:
        return 0xff800000 if x < 0 else 0x7f800000


def selected(u, v):
    ex, ey = (u >> 23) & 255, (v >> 23) & 255
    s, sign = ex + ey, (u ^ v) & 0x80000000
    if s <= 102:
        return sign
    if s >= 382 and ex < 255 and ey < 255:
        return sign | 0x7f800000
    return None


if __name__ == '__main__':
    source = HERE / 'independent-frontier/Runtime-extreme-cold-mul.lean.inc'
    assert hashlib.sha256(source.read_bytes()).hexdigest() == 'ac7c9df8aee30277befe4b6aae2e7f43fbf81043d6e00ab35127126f0f3ebd59'
    trace = hashlib.sha256()
    count = 0
    for total in list(range(103)) + list(range(382, 509)):
        exs = {max(0, total - 254), total // 2, min(254, total)}
        for ex in sorted(exs):
            ey = total - ex
            assert 0 <= ex < 255 and 0 <= ey < 255
            for a in (0, 1, 0x3fffff, 0x400000, 0x7ffffe, 0x7fffff):
                for b in (0, 1, 0x3fffff, 0x400000, 0x7ffffe, 0x7fffff):
                    for su, sv in ((0, 0), (0, 1), (1, 0), (1, 1)):
                        u, v = (su << 31) | (ex << 23) | a, (sv << 31) | (ey << 23) | b
                        actual, reference = selected(u, v), bits(fp(u) * fp(v))
                        assert actual == reference
                        trace.update(struct.pack('<III', u, v, actual))
                        count += 1
    counterexamples = []
    for label, u, v, wrong in (
            ('zero_threshold103', (51 << 23) | 0x7fffff, (52 << 23) | 0x7fffff, 0),
            ('infinity_threshold381', 190 << 23, 191 << 23, 0x7f800000)):
        reference = bits(fp(u) * fp(v))
        assert selected(u, v) is None and reference != wrong
        counterexamples.append({'mutation': label, 'u': hex(u), 'v': hex(v), 'correct': hex(reference), 'wrong': hex(wrong)})
    for u, v in ((0x7f800000, 0), (0xff800000, 0x80000000), (0x7fc00001, 1), (0xff800123, 0x7fffffff)):
        assert selected(u, v) is None
    out = {'utc': datetime.now(timezone.utc).isoformat(), 'cases': count, 'differences': 0,
           'trace_sha256': trace.hexdigest(), 'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
           'counterexamples': counterexamples,
           'reference': 'Exact binary64 product of binary32 finite inputs (at most48 significant bits), then binary32 RNE packing',
           'scope': 'Finite boundary model plus endpoint paper proof. No actual Lean/CPU callback or performance. Every excluded special remains old B2 fallback; no NaN payload claim from host arithmetic.'}
    (HERE / 'extreme-cold-mul-independent-review.json').write_text(json.dumps(out, indent=2) + '\n')
    print(json.dumps({'cases': count, 'differences': 0, 'counterexamples': counterexamples}))
