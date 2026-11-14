"""Finite full-formula replay with grouped body, bias rebase and one round.

This is Python integer evidence, not a Lean/native implementation. Prior
v1 remains the observer-only body receipt; this v2 actually feeds new dense
outputs into later formula layers, with the old path on outer/zero failure.
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
OWN = HERE.parents[1]
C = OWN.parent / 'board-frontier'
MASK64 = (1 << 64) - 1


def signed64(x):
    return x if x < 1 << 63 else x - (1 << 64)


def signed128(lo, hi):
    return lo + (signed64(hi) << 64)


def merge64(lo, hi, q):
    nxt = (lo + q) & MASK64
    return nxt, (hi + (MASK64 if q >= 1 << 63 else 0) + int(nxt < lo)) & MASK64


def shift128(lo, hi, delta):
    # Literal R26 shiftLo/shiftHi cases, including mandatory delta=0 arm.
    sl = (lo << delta) & MASK64 if delta < 64 else 0
    if delta == 0:
        sh = hi
    elif delta < 64:
        sh = ((hi << delta) | (lo >> (64-delta))) & MASK64
    elif delta < 128:
        sh = (lo << (delta-64)) & MASK64
    else:
        sh = 0
    return sl, sh


def add128(lo, hi, ql, qh):
    nxt = (lo + ql) & MASK64
    return nxt, (hi + qh + int(nxt < lo)) & MASK64


def main():
    start = time.perf_counter()
    spec = importlib.util.spec_from_file_location('r27_band_parent_model', C / 'norm_frontier.py')
    f = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(f)
    mspec = importlib.util.spec_from_file_location('r27_band_actual_metadata', OWN / 'word_model_coverage.py')
    metadata_module = importlib.util.module_from_spec(mspec)
    mspec.loader.exec_module(metadata_module)
    original_linear = f.linear
    context = {}
    layer = 0
    records = []

    def prep(words):
        fs = [f.fields(w) for w in words]
        nonzero = [(i, s, m, e) for i, (s, m, e) in enumerate(fs) if m]
        meta = metadata_module.metadata(words)
        assert meta['finite'] and not meta['reversed']
        low, high = meta['base'], meta['upper']
        assert all(((w >> 23) & 255) != 255 for w in words)
        return nonzero, low, high

    def observe(x, rows, k, out, w, b, relu):
        nonlocal layer
        assert time.perf_counter() - start < 20, '20 second local discriminator limit'
        layer += 1
        baseline = original_linear(x, rows, k, out, w, b, relu)
        outputs = list(baseline)
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
            counts['four_column_shared_index_loads'] += len(nz) * (out // 4)
            for g in groups.values():
                group_sizes[len(g)] += 1
            for j, (wf, wl, wh) in enumerate(ws):
                counts['dots'] += 1
                spans[(high-low, wh-wl)] += 1
                sb, mb, ib = f.fields(b[j])
                body_base = low + wl
                terminal_base = min(body_base, ib+126) if mb else body_base
                terminal_high = max(high+wh, ib+126) if mb else high+wh
                finite_bias = ((b[j] >> 23) & 255) != 255
                eligible = (finite_bias and k < 1 << 20 and wh-wl <= 6
                            and terminal_high-terminal_base <= 58)
                assert eligible, 'This selected six-cell replay must satisfy the actual whole-layer guard.'
                if j >= out//4*4:
                    counts['original_tail_columns'] += 1
                    continue
                if not eligible:
                    counts['ineligible_dots'] += 1
                    continue
                counts['eligible_dots'] += 1
                counts['eligible_logical_MACs'] += k
                counts['grouped_nonzero_input_MACs'] += len(nz)
                grouped = 0
                body_lo, body_hi = 0, 0
                for band, terms in sorted(groups.items()):
                    group = 0
                    group_lo, group_hi = 0, 0
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
                        group_lo, group_hi = merge64(group_lo, group_hi, machine)
                        assert signed128(group_lo, group_hi) == group
                        counts['block64_merges'] += 1
                    shifted = group << (4 * band)
                    assert -(1 << 127) <= shifted < 1 << 127
                    sl, sh = shift128(group_lo, group_hi, 4*band)
                    assert signed128(sl, sh) == shifted
                    grouped += shifted
                    body_lo, body_hi = add128(body_lo, body_hi, sl, sh)
                    assert signed128(body_lo, body_hi) == grouped
                    counts['band128_shifts'] += 1
                direct = sum(a * z for a, z in zip(full, wf))
                assert grouped == direct
                assert -(1 << 127) <= grouped < 1 << 127
                max_body_bits = max(max_body_bits, abs(grouped).bit_length())
                pad = body_base-terminal_base
                bias_shift = ib+149-terminal_base
                assert pad >= 0 and (mb == 0 or bias_shift >= 23)
                bias = sb * (mb << max(0, bias_shift))
                total = (grouped << pad) + bias
                assert -(1 << 127) <= total < 1 << 127
                raw_total = sum(f.key(x[r*k+i])*f.key(w[j*k+i]) for i in range(k)) + (f.key(b[j]) << 149)
                assert (total << terminal_base) == raw_total
                if total == 0:
                    counts['exact_zero_original_fallback'] += 1
                    outputs[r*out+j] = baseline[r*out+j]
                else:
                    counts['nonzero_single_round'] += 1
                    outputs[r*out+j] = 0 if relu and total < 0 else f.round_ratio(total, 1, terminal_base-298)
                assert outputs[r*out+j] == baseline[r*out+j]
        records.append(dict(**context, layer=layer, rows=rows, k=k, out=out,
                            logical_MACs=rows*k*out, counts=dict(counts),
                            prepared_weight_words=k*out,
                            max_exact_body_bits=max_body_bits,
                            span_pairs={str(key): val for key, val in spans.items()},
                            group_size_histogram=dict(sorted(group_sizes.items()))))
        assert outputs == baseline
        return outputs

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
                  state='FINITE_ACTUAL_YC_METADATA_AND_TAIL_SCHEDULE_REPLAY_OF_BAND_COST_SOURCE',
                  prior_mechanism='R26 WideBandRuntime.lean; new evidence is whole-model call coverage, not invention of exponent bands.',
                  wall_seconds=time.perf_counter()-start, cells=cells, layers=records,
                  theorem_budget='width4 gives factorA<2^27; weight span<=6 gives factorB<2^30; 64 products have mass<2^63. terminal_base=min(body_base,nonzero_bias_idx+126), terminal_high=max(body_high,nonzero_bias_idx+126). n<=2^20 and terminal_high-terminal_base<=58 give body mass<2^126, bias mass<2^105, total<2^127.',
                  source_hashes={p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in
                                 (Path(__file__), HERE / 'BandNative.lean.inc', OWN / 'word_model_coverage.py',
                                  C / 'norm_frontier.py', C / 'norm-frontier-result.json')},
                  limitations=[
                      'Finite Python checks cover body, rebased bias and one final formula rounding; no Lean proof of actual preparation/getters/partition/rounding is supplied.',
                      'Dense outputs from the new finite model feed later formula layers; normalization uses the old exact formula. Checksums are model evidence, not Lean/native candidate checksums.',
                      'No Lean acceptance, generated code, native timing, or current champion claim.',
                      'Literal old Yc metadata is replayed, including conservative lower exponents at exact powers of two. Band iteration is ascending; the final outW%4 columns use the old path.',
                      'Four-lane execution is arithmetically replayed lane by lane. This does not inspect its generated scalar registers, callback specialization, bounds checks or allocations.',
                      'Preparation and index storage, gathered weight loads, lost four-row sharing and group overhead are unmeasured.',
                      'Input zeros are omitted by this model; existing source also has zero handling, so zero omission is not a claimed novel saving.',
                      'Old seen cells cannot become unseen confirmation data.'
                  ])
    (HERE / 'native-shape-replay.json').write_text(json.dumps(result, indent=2), encoding='utf8')
    print(json.dumps({'wall_seconds': result['wall_seconds'], 'cells': cells}, indent=2))


if __name__ == '__main__':
    main()
