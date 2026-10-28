"""Finite address model for the conditional cache-view bridge, not a Lean/IEEE proof."""
from pathlib import Path
import hashlib
import itertools
import json
import re

HERE = Path(__file__).resolve().parent
ZERO = ('POS_ZERO',)
sha = lambda b: hashlib.sha256(b).hexdigest()


def run():
    runtime = (HERE / 'KernelIndexed8Cost.lean').read_bytes()
    assert sha(runtime) == '8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
    leaf = (HERE / 'Nat8CacheViewHRead.lean.inc').read_bytes()
    source = leaf.decode()
    assert re.findall(r'^theorem (\w+)', source, re.M) == ['cacheView_hread']
    assert not re.search(r'\b(sorry|axiom|unsafe|extern|implemented_by)\b', source)
    assert 'hcol : 2 * g.val + c.val < p' in source
    assert 'b * n * R22Pair8.groups p + g.val' in source
    assert 'b * n * p + 2 * g.val + c.val + i.val * p' in source
    checks = 0
    mutants = {name: None for name in ('batch', 'stride', 'pair', 'column', 'raw_batch')}
    for batch, n, p in itertools.product(range(1, 5), range(6), range(10)):
        groups = (p + 1) // 2
        full_size = batch * n * p
        for raw_size in sorted({0, 1, full_size // 2, full_size, full_size + 2}):
            raw = [('B', q) for q in range(raw_size)]
            get = lambda q: raw[q] if q < len(raw) else ZERO
            cache = [(get(row * p + 2 * g),
                      get(row * p + 2 * g + 1) if 2 * g + 1 < p else ZERO)
                     for row in range(batch * n) for g in range(groups)]
            cget = lambda q, c: cache[q][c] if q < len(cache) else ZERO
            for b, g, c, k in itertools.product(range(batch), range(groups), range(2), range(n)):
                if 2 * g + c >= p:
                    continue
                ci = b * n * groups + g + k * groups
                ri = b * n * p + 2 * g + c + k * p
                assert ci == (b * n + k) * groups + g
                assert ri == (b * n + k) * p + 2 * g + c
                assert cget(ci, c) == get(ri)
                checks += 1
                candidates = {
                    'batch': cget(b * groups + g + k * groups, c),
                    'stride': cget(b * n * groups + g + k * p, c),
                    'pair': cget(b * n * groups + 2 * g + k * groups, c),
                    'column': get(b * n * p + g + c + k * p),
                    'raw_batch': get(b * p + 2 * g + c + k * p),
                }
                for name, wrong in candidates.items():
                    if mutants[name] is None and wrong != get(ri):
                        mutants[name] = dict(batch=batch, n=n, p=p, b=b, g=g, c=c,
                                             k=k, raw_size=raw_size, expected=get(ri), wrong=wrong)
    assert all(mutants.values()), mutants
    # The omitted hcol is observably false: p3, last pair's right padding differs
    # from a raw read at column3, which points to the next row (or next batch).
    odd_falsifier = dict(batch=2, n=1, p=3, b=0, g=1, c=1, k=0,
                        cached=ZERO, invalid_raw=('B', 3))
    assert odd_falsifier['cached'] != odd_falsifier['invalid_raw']
    deps = []
    for filename, expected in (
        ('Nat8Projection-v1.lean.inc', '79574fb1b64febf7d3cd328fe41c2f11ac2172e81177fd2cb057aa74e574d6dd'),
        ('Nat8CacheSelected.lean.inc', 'a457ed45ade0ab620456da9f397c429517c4764ad19e10f793b60b21caadb5c1'),
    ):
        data = (HERE / filename).read_bytes()
        assert sha(data) == expected
        deps.append(dict(path=filename, sha256=expected, bytes=len(data)))
    result = dict(fragment='Nat8CacheViewHRead.lean.inc', sha256=sha(leaf), bytes=len(leaf),
                  roots=['Submission.R22CacheSelected.cacheView_hread'],
                  dependencies=deps,
                  external_dependency=dict(path='research/streaming-public/Pair8CacheProof.lean.inc',
                    sha256='2850a16cbce661e5ec242a8d24ac08e7fe6e8bb4556399974ef586d7411d93a5'),
                  runtime_sha256=sha(runtime), status='NOT_COMPILED_NOT_RUN',
                  finite_symbolic_checks=checks, caught_address_mutants=mutants,
                  first_falsifier_if_column_premise_removed=odd_falsifier,
                  new_kernel_emitted=False,
                  scope='Valid selected field only; finite address model is not a Lean or Float32 proof.')
    (HERE / 'nat8-cache-hread-manifest.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: result[k] for k in ('sha256', 'bytes', 'finite_symbolic_checks', 'status')}))


if __name__ == '__main__':
    run()
