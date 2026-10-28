"""Independent host check of C's fixed word model, without running its main.

Two finite binary32 addends can safely be summed through binary64 for final
binary32 rounding: relevant midpoint cases have at most 49 significant bits;
larger exponent gaps are below a binary32 half-ULP. No NaN payload claim.
"""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import struct

HERE = Path(__file__).resolve().parent
FRONT = HERE / 'independent-frontier'

def fp(u):
    return struct.unpack('<f', struct.pack('<I', u))[0]

def output(x):
    try:
        return struct.unpack('<I', struct.pack('<f', x))[0]
    except OverflowError:
        return (0x80000000 if x < 0 else 0) | 0x7f800000

def mutation(u, v, kind):
    eu, ev = (u >> 23) & 255, (v >> 23) & 255
    hi, lo, e, d = (v, u, ev, ev - eu) if eu < ev else (u, v, eu, eu - ev)
    if d >= (24 if kind == 'early_absorption_24' else 25):
        return hi
    a, b = ((hi & 0x7fffff) | 0x800000) << 3, ((lo & 0x7fffff) | 0x800000) << 3
    jam = int((b & ((1 << d) - 1)) != 0)
    if kind == 'drop_alignment_sticky':
        jam = 0
    t = a + ((b >> d) | jam)
    carry = t >> 27
    if carry:
        t = (t >> 1) | (t & 1)
    e += carry
    sign = hi & 0x80000000
    if e >= 255:
        return sign | 0x7f800000
    mantissa = (t + 3 + ((t >> 3) & 1)) >> 3
    if kind == 'OR_instead_of_add_pack':
        return sign | ((e - 1) << 23) | mantissa
    return sign | (((e - 1) << 23) + mantissa)

def main():
    source = FRONT / 'check_broad_word_add.py'
    tree = ast.parse(source.read_bytes())
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in {'eligible', 'core', 'trial'}]
    env = {'MASK': (1 << 32) - 1}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(source), 'exec'), env)
    assert output(1.0 + 2.0 ** -24) == 0x3f800000
    assert output(1.0 + 3.0 * 2.0 ** -24) == 0x3f800002
    exponent_pairs = {(e, e) for e in range(1, 255)} | {(254, 254 - d) for d in range(254)}
    exponent_pairs |= {(e, e - d) for e in (1, 2, 64, 103, 127, 128, 191, 253, 254)
                       for d in (0, 1, 2, 23, 24, 25, 26, 63, 127, 253) if e - d >= 1}
    fractions = [0, 1, 0x3fffff, 0x400000, 0x7fffff]
    trace = hashlib.sha256()
    count = 0
    for ea, eb in sorted(exponent_pairs):
        for fa in fractions:
            for fb in fractions:
                for sign in (0, 0x80000000):
                    u, v = sign | (ea << 23) | fa, sign | (eb << 23) | fb
                    for a, b in ((u, v), (v, u)):
                        actual, _ = env['trial'](a, b)
                        reference = output(fp(a) + fp(b))
                        assert actual == reference, (hex(a), hex(b), hex(actual), hex(reference))
                        trace.update(struct.pack('<III', a, b, actual))
                        count += 1
    witnesses = {
        'early_absorption_24': (0x3fffffff, 0x33800000),
        'drop_alignment_sticky': (0x3f800000, 0x33800001),
        'OR_instead_of_add_pack': (0x40000000, 0x3f800000),
    }
    detected = []
    for kind, (u, v) in witnesses.items():
        expected = output(fp(u) + fp(v))
        wrong = mutation(u, v, kind)
        assert wrong != expected
        detected.append({'kind': kind, 'u': hex(u), 'v': hex(v),
                         'reference': hex(expected), 'mutant': hex(wrong)})
    kernel = FRONT / 'Kernel-broad-word-add-probe.lean'
    # Candidate directories are siblings of f01-d7-research.
    base = next(p for p in HERE.parents if p.name == 'candidates') / 'f01-r15-dev-packed-b2-1/Kernel.lean'
    assert kernel.read_bytes().startswith(base.read_bytes())
    assert hashlib.sha256(kernel.read_bytes()).hexdigest() == '0274763264d760775e6a447848e873db418adc2e6fb651d117c5fc04b4b5d4a5'
    result = {'verified_utc': datetime.now(timezone.utc).isoformat(), 'cases': count, 'differences': 0,
              'reference': 'Host binary64 sum of two binary32 inputs, binary32 RNE packing; ties sanity checked',
              'scope': 'Same-sign normal input guard only; public fallback inspected in source, not reimplemented',
              'model_script_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
              'runtime_sha256': hashlib.sha256((FRONT / 'Runtime-broad-word-add.lean.inc').read_bytes()).hexdigest(),
              'kernel_sha256': hashlib.sha256(kernel.read_bytes()).hexdigest(), 'B2_exact_prefix': True,
              'output_trace_sha256': trace.hexdigest(), 'mutations_detected': detected,
              'Lean': 'NOT_RUN', 'performance': 'UNKNOWN', 'all_input_proof': 'MISSING'}
    (HERE / 'broad-word-add-independent-review.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))

if __name__ == '__main__':
    main()
