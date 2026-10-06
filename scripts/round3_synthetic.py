"""Fixed synthetic transfer check, separate from the public competition score.

These inputs are generated from this script, not private stage2. Do not use
their aggregate as a leaderboard estimate. Generation precedes their first run.
"""
from __future__ import annotations
import dataclasses
import hashlib
import json
from pathlib import Path
import random
import statistics


def inputs():
    rng = random.Random(0xDEF1A7E20261006)
    code = '\n'.join(f'def function_{i % 53}(value):\n    return (value * {i % 19 + 1} + {i % 101}) % 65521\n' for i in range(3600)).encode()
    logs = '\n'.join(f'2026-09-{1+i%27:02d}T{(i//60)%24:02d}:{i%60:02d}:00 level=INFO key={i%127} value={rng.randrange(10000)} result=accepted' for i in range(500)).encode()
    csv = ('id,region,value,count\n' + '\n'.join(f'{i},region_{i%17},{rng.randrange(65536)},{i%31}' for i in range(8500))).encode()
    unicode = '\n'.join(f'记录{i%113}：压缩测试，重复片段与变化字段。東京 café Δοκιμή {rng.randrange(1024)}' for i in range(1900)).encode()
    base = rng.randbytes(32768)
    tiny = '\n'.join(json.dumps({'event': i % 11, 'valid': i % 7 != 0, 'value': rng.randrange(10000), 'unit': 'ms'}, separators=(',', ':')) for i in range(311)).encode()
    return {'source-like.txt': code, 'short-log.txt': logs, 'table.csv': csv,
            'multilingual.txt': unicode, 'random.bin': rng.randbytes(131101),
            'window-boundary.bin': base + b'boundary' + base + rng.randbytes(8191),
            'sparse.bin': b''.join(b'\0' * (97 + i % 13) + i.to_bytes(4, 'little') for i in range(503)),
            'tiny-structured.txt': tiny}


def run_validation(config, paths, names, reports):
    from bench.corpora import Corpus
    from bench.driver import run
    from bench.results import INCUMBENT
    folder = reports / 'synthetic-transfer'
    folder.mkdir()
    provenance = {}
    for name, data in inputs().items():
        (folder / name).write_bytes(data)
        provenance[name] = {'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
    corpus = Corpus('synthetic-transfer', folder, True, {})
    print('SYNTHETIC_INPUTS ' + json.dumps(provenance), flush=True)
    metrics = []
    for block, order in enumerate((names, list(reversed(names))), 1):
        for name in order:
            measured = run(config, {name: paths[name] / 'parse.rs'}, corpus).only()
            assert not measured.failures(name) + measured.failures(INCUMBENT)
            files = [f for f in measured.files if f.raw_bytes]
            result = {'candidate': name, 'round': block,
                      'time': statistics.mean(f.methods[name].total_s / f.methods[INCUMBENT].total_s for f in files),
                      'size_pct': statistics.mean(100 * f.methods[name].output_bytes / f.raw_bytes for f in files)}
            metrics.append(result)
            print('SYNTHETIC_MEASUREMENT ' + json.dumps(result), flush=True)
            for raw in measured.raw_records:
                print(f'SYNTHETIC_RAW {block} {name} ' + json.dumps(raw), flush=True)
    return {'scope': 'eight fixed synthetic inputs; transfer diagnostic, not private stage2 or competition score',
            'inputs': provenance, 'metrics': metrics}
