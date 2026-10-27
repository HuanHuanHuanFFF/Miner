"""Seen-input source-model screen; never a timing or confirmation sample."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import hashlib
import json
import math
import struct
import time
import types

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
MODEL = HERE.parent / 'round8h-20261024T190259Z/astra-public-input-domain.py'
GEN = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/BenchSuite.lean'
PLAN = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168687803/download-13caf4644cf1467e8717d9474d417b8a/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'


def load_generator():
    # Rebind only a relocated byte-identical source; keep the historical model intact.
    code = MODEL.read_text(encoding='utf-8')
    old = "GEN = HERE / 'astra-official-source/lean/bench/BenchSuite.lean'"
    assert code.count(old) == 1
    code = code.replace(old, 'GEN = ROOT / ' + repr(GEN.relative_to(ROOT).as_posix()))
    module = types.ModuleType('seen_input_model')
    module.__file__ = str(MODEL)
    exec(compile(code, str(MODEL), 'exec'), module.__dict__)
    return module


def value(raw):
    return struct.unpack('<f', struct.pack('<I', raw))[0]


def add_raw(a, b):
    result = value(a) + value(b)
    if math.isnan(result):
        return 0x7fc00000
    try:
        return struct.unpack('<I', struct.pack('<f', result))[0]
    except OverflowError:
        return 0xff800000 if result < 0 else 0x7f800000


def main():
    g = load_generator()
    started = time.monotonic()
    counters = {8: Counter(), 16: Counter()}
    rows = []
    trace = hashlib.sha256()
    elements = 0
    for case in json.loads(PLAN.read_bytes())['cases']:
        if case['kernel'] != 'sum' or not case['timed']:
            continue
        local = {8: Counter(), 16: Counter()}
        samples = min(4, case['batch'])
        for j in range(samples):
            batch_index = j * case['batch'] // samples
            words = [g.element(case, batch_index * case['length'] + i, 0, case['length'])
                     for i in range(case['length'])]
            elements += len(words)
            assert elements <= 300000 and time.monotonic() - started < 12
            prefixes = [0]
            for word in words:
                prefixes.append(add_raw(prefixes[-1], word))
                trace.update(word.to_bytes(4, 'little'))
            for block in (8, 16):
                stats = local[block]
                stats['sampled_elements'] += len(words)
                # Start after the seed-consuming first element; include full blocks only.
                for k in range(1, len(words) - block + 1, block):
                    stats['blocks'] += 1
                    acc = prefixes[k]
                    exponent = (acc >> 23) & 255
                    if not 26 <= exponent <= 254:
                        stats['accumulator_guard_rejected'] += 1
                        continue
                    stats['candidate_blocks'] += 1
                    threshold = (exponent - 25) << 23
                    okay = True
                    for word in words[k:k + block]:
                        stats['certificate_raw_reads'] += 1
                        if (word & 0x7fffffff) >= threshold:
                            okay = False
                            break
                    if okay:
                        assert prefixes[k + block] == acc, (case['name'], batch_index, k)
                        stats['accepted_blocks'] += 1
                        stats['skippable_elements'] += block
                    else:
                        stats['failed_scans_then_original_block'] += 1
        for block in (8, 16):
            counters[block].update(local[block])
        rows.append({'case': case['name'], 'length': case['length'], 'batch': case['batch'],
                     'sampled_vectors': samples, 'blocks': {str(k): dict(v) for k, v in local.items()}})
    result = {'as_of_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'Already-seen R15 discovery inputs, four stratified vectors per case; source-model and host binary32 arithmetic only. No Lean proof, cycle timing, or independent confirmation.',
              'source_plan': PLAN.relative_to(ROOT).as_posix(),
              'source_plan_sha256': hashlib.sha256(PLAN.read_bytes()).hexdigest(),
              'generator_sha256': hashlib.sha256(GEN.read_bytes()).hexdigest(),
              'historical_translation_sha256': hashlib.sha256(MODEL.read_bytes()).hexdigest(),
              'certificate': 'For normal finite accumulator raw exponent e>=26, each absolute input word strictly below ((e-25)<<23). This conservative half-gap handles binade lower edges and both signs.',
              'predeclared_block_sizes': [8, 16], 'sampled_elements': elements,
              'trace_sha256': trace.hexdigest(), 'counts': {str(k): dict(v) for k, v in counters.items()},
              'rows': rows, 'seconds': time.monotonic() - started,
              'limits': '300000 input elements / 12 cooperative seconds. Scan reads and fallback rereads are costs; element coverage is not time share or predicted speed.'}
    (HERE / 'development-sum-absorption-screen.json').write_text(
        json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'sampled_elements': elements, 'counts': result['counts'], 'seconds': result['seconds']}))


if __name__ == '__main__':
    main()
