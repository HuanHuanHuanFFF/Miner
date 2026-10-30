"""Extend the R26 band idea to already-seen complete-model call inputs.

The old rational model still produces outputs. This checks every grouped
integer body at its actual dense call, not an integrated Lean candidate.
"""
from pathlib import Path
from collections import Counter
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import struct
import sys
import time

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
C = HERE.parent / 'board-frontier'
MASK64 = (1 << 64) - 1


def signed64(x):
    return x if x < 1 << 63 else x - (1 << 64)


def main():
    start = time.perf_counter()
    spec = importlib.util.spec_from_file_location('r27_band_parent_model', C / 'norm_frontier.py')
    f = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(f)
    original_linear = f.linear
    context = {}
    layer = 0
    records = []

    def prep(words):
        fs = [f.fields(w) for w in words]
        nonzero = [(i, s, m, e) for i, (s, m, e) in enumerate(fs) if m]
        low = min((e for _, _, _, e in nonzero), default=0)
        high = max((e for _, _, _, e in nonzero), default=low)
        assert all(((w >> 23) & 255) != 255 for w in words)
        return nonzero, low, high

    def observe(x, rows, k, out, w, b, relu):
        nonlocal layer
        assert time.perf_counter() - start < 20, '20 second local discriminator limit'
        layer += 1
        ws = []
        for j in range(out):
            nz, low, high = prep(w[j*k:(j+1)*k])
            values = [0] * k
            for i, s, m, e in nz:
                values[i] = s * (m << (e-low))
            ws.append((values, low, high))
        counts = Counter()
        spans = Counter()
        group_sizes = Counter()
        max_body_bits = 0
        for r in range(rows):
            nz, low, high = prep(x[r*k:(r+1)*k])
            groups = {}
            full = [0] * k
            for i, s, m, e in nz:
                band = (e - low) // 4
                factor = s * (m << ((e-low) % 4))
                groups.setdefault(band, []).append((i, factor))
                full[i] = s * (m << (e-low))
            counts['prepared_input_words'] += len(nz)
            counts['index_words'] += len(nz)
            counts['four_column_shared_index_loads'] += len(nz) * ((out + 3) // 4)
            for g in groups.values():
                group_sizes[len(g)] += 1
            for wf, wl, wh in ws:
                counts['dots'] += 1
                spans[(high-low, wh-wl)] += 1
                eligible = k <= 1 << 20 and wh-wl <= 6 and high-low+wh-wl <= 58
                if not eligible:
                    counts['ineligible_dots'] += 1
                    continue
                counts['eligible_dots'] += 1
                counts['eligible_logical_MACs'] += k
                counts['grouped_nonzero_input_MACs'] += len(nz)
                grouped = 0
                for band, terms in groups.items():
                    group = 0
                    for begin in range(0, len(terms), 64):
                        block = terms[begin:begin+64]
                        products = [a * wf[i] for i, a in block]
                        mass = sum(map(abs, products))
                        assert mass < 1 << 63
                        exact = sum(products)
                        machine = 0
                        for p in products:
                            machine = (machine + (p & MASK64)) & MASK64
                        assert signed64(machine) == exact
                        group += signed64(machine)
                        counts['block64_merges'] += 1
                    shifted = group << (4 * band)
                    assert -(1 << 127) <= shifted < 1 << 127
                    grouped += shifted
                    counts['band128_shifts'] += 1
                direct = sum(a * z for a, z in zip(full, wf))
                assert grouped == direct
                assert -(1 << 127) <= grouped < 1 << 127
                max_body_bits = max(max_body_bits, abs(grouped).bit_length())
        records.append(dict(**context, layer=layer, rows=rows, k=k, out=out,
                            logical_MACs=rows*k*out, counts=dict(counts),
                            prepared_weight_words=k*out,
                            max_exact_body_bits=max_body_bits,
                            span_pairs={str(key): val for key, val in spans.items()},
                            group_size_histogram=dict(sorted(group_sizes.items()))))
        return original_linear(x, rows, k, out, w, b, relu)

    f.linear = observe
    seed = 27051001
    expected = json.loads((C / 'norm-frontier-result.json').read_text())['cells']
    cells = []
    for kind in ('normal', 'wide', 'sparse'):
        for rows in (1, 8):
            context.clear()
            context.update(kind=kind, seed=seed, profile='typical')
            layer = 0
            i, h, h2 = f.dimensions(seed, 'typical')
            x = f.gen(kind, rows*i, seed+999)
            x = f.linear(x, rows, i, h, f.weights(kind, seed, 1, i, h*i), f.bias(seed, 2, h), True)
            x = f.norm(x, rows, h, f.scale(seed+3, h))
            x = f.linear(x, rows, h, h2, f.weights(kind, seed, 4, h, h2*h), f.bias(seed, 5, h2), True)
            x = f.norm(x, rows, h2, f.scale(seed+6, h2), f.bias(seed, 7, h2))
            x = f.linear(x, rows, h2, 10, f.weights(kind, seed, 8, h2, 10*h2), f.bias(seed, 9, 10), False)
            digest = hashlib.sha256(b''.join(struct.pack('<I', v) for v in x)).hexdigest()
            old = next(v for v in expected if v['seed'] == seed and v['profile'] == 'typical' and v['kind'] == kind and v['rows'] == rows)
            assert digest == old['output_sha256']
            rr = [v for v in records if v['kind'] == kind and v['rows'] == rows]
            total = Counter()
            for row in rr:
                total.update(row['counts'])
            cells.append(dict(kind=kind, rows=rows, logical_MACs=sum(v['logical_MACs'] for v in rr),
                              counts=dict(total), original_formula_fixture_sha256=digest))
    result = dict(at_utc=datetime.now(timezone.utc).isoformat(),
                  state='FINITE_GROUPED_WORD_BODY_CHECK_AT_SEEN_FULL_MODEL_CALLS',
                  prior_mechanism='R26 WideBandRuntime.lean; new evidence is whole-model call coverage, not invention of exponent bands.',
                  wall_seconds=time.perf_counter()-start, cells=cells, layers=records,
                  theorem_budget='width4 gives factorA<2^27; weight span<=6 gives factorB<2^30; 64 products have mass<2^63. n<=2^20 and total exponent span<=58 give total mass<2^126.',
                  source_hashes={p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in
                                 (Path(__file__), C / 'norm_frontier.py', C / 'norm-frontier-result.json')},
                  limitations=[
                      'Exact checks cover body only; bias, finite input, zero, final rounding and actual getters still require proofs.',
                      'Whole outputs stay on the old rational model; their hashes are fixture bindings, not new-kernel checksums.',
                      'No Lean acceptance, generated code, native timing, or current champion claim.',
                      'Preparation and index storage, gathered weight loads, lost four-row sharing and group overhead are unmeasured.',
                      'Input zeros are omitted by this model; existing source also has zero handling, so zero omission is not a claimed novel saving.',
                      'Old seen cells cannot become unseen confirmation data.'
                  ])
    (HERE / 'band-full-model-census.json').write_text(json.dumps(result, indent=2), encoding='utf8')
    print(json.dumps({'wall_seconds': result['wall_seconds'], 'cells': cells}, indent=2))


if __name__ == '__main__':
    main()
