"""Bounded R26 source/receipt audit; no Rust, Lean, CI, network or Git calls."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import itertools
import json
import random
import statistics

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/range-review'
M = 1 << 23
U32 = (1 << 32) - 1
INPUTS = {}


def read(path):
    raw = (ROOT / path).read_bytes()
    INPUTS[path] = {'sha256': hashlib.sha256(raw).hexdigest(), 'bytes': len(raw)}
    return raw


def obj(path):
    return json.loads(read(path))


def function(src, name):
    start = src.index('pub fn ' + name + '(')
    op = src.index('{', start)
    depth, pos = 1, op + 1
    while depth:
        depth += (src[pos] == '{') - (src[pos] == '}')
        pos += 1
    return src[start:pos]


def packed(cost, price, length):
    return (((cost + price) & U32) << 9 & U32) | length


def safe(costs, price, modulus=M):
    low, high = min(costs), max(costs)
    return high - low < modulus and (low + price) % modulus <= (high + price) % modulus


def case(name, costs, price, lengths=(3, 4), scope='arbitrary helper state; not a reachable parse-input witness'):
    keys = [packed(c, price, l) for c, l in zip(costs, lengths)]
    raw = min(range(len(costs)), key=lambda i: (costs[i], lengths[i]))
    exact = min(range(len(costs)), key=lambda i: keys[i])
    assert raw != exact
    return dict(name=name, costs=costs, price=price, lengths=lengths, packed_keys=keys,
                raw_argmin=raw, packed_argmin=exact, safe_guard=safe(costs, price), scope=scope)


def mask_offsets(costs, strict=False):
    masks = [0] * len(costs)
    mask = 0
    for p in range(len(costs) - 1, -1, -1):
        mask = (mask << 1) & U32
        while mask:
            low = mask & -mask
            offset = low.bit_length() - 1
            if costs[p + offset] > costs[p] if strict else costs[p + offset] >= costs[p]:
                mask &= mask - 1
            else:
                break
        mask |= 1
        masks[p] = mask
    return masks


def counts_summary(t):
    buckets = [('width1_3', 1, 3), ('width4_7', 4, 7), ('width8_15', 8, 15),
               ('width16_31', 16, 31), ('width32_63', 32, 63), ('width64_127', 64, 127),
               ('width128_plus', 128, 256)]
    assert sum(t[k] for k, _, _ in buckets) == t['variable_queries']
    assert 16 * t['aligned16_blocks'] + t['partial_terms'] == t['variable_terms']
    short = buckets[:4]
    long = buckets[4:]
    long_min = max(sum(t[k] * low for k, low, _ in long),
                   t['variable_terms'] - sum(t[k] * high for k, _, high in short))
    long_max = min(sum(t[k] * high for k, _, high in long),
                   t['variable_terms'] - sum(t[k] * low for k, low, _ in short))
    terms, segments = t['variable_terms'], t['price_segments']
    return dict(counts=t, mean_query_width=terms / t['variable_queries'],
                mean_price_segment_width=terms / segments,
                query_width_at_most_3_pct=100 * t['width1_3'] / t['variable_queries'],
                query_width_below_8_pct=100 * (t['width1_3'] + t['width4_7']) / t['variable_queries'],
                query_width_at_least_32_pct=100 * sum(t[k] for k, _, _ in long) / t['variable_queries'],
                terms_in_width_at_least_32_bounds=[long_min, long_max],
                aligned16_term_coverage_pct=100 * 16 * t['aligned16_blocks'] / terms,
                ideal_32_prefix_chunks_bounds=[segments, segments + (terms - segments) // 32],
                ideal_scalar_offer_reduction_ceiling_pct=100 * (terms - segments) / terms,
                scope='Integer accounting only: no machine-time bound, no guard/pop/singleton distribution.')


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    source_paths = ['references/round24-public-552/parse.rs',
                    'references/round18-public-586/parse.rs',
                    'candidates/r18-586-selective-rf/parse.rs',
                    'candidates/r18-586-a-block8/parse.rs',
                    'candidates/r10-record-nonempty/parse.rs',
                    'candidates/r10-backward-prefixmask/parse.rs']
    sources = {p: read(p).decode().replace('\r\n', '\n') for p in source_paths}
    names = ['a_dp_pass', 'a_store_choice', 'a_sample_pass', 'a_set_costs', 'a_set_costs_huff', 'a_engine']
    mapping = {name: {p: hashlib.sha256(function(sources[p], name).encode()).hexdigest()
                      for p in source_paths[:3]} for name in names}
    assert all(len(set(v.values())) == 1 for v in mapping.values())
    d_same = function(sources[source_paths[0]], 'd_dp') == function(sources[source_paths[4]], 'd_dp')
    assert d_same
    for p in ['references/round24-public-552/Parse.lean', 'candidates/r18-586-a-block8/manifest.json',
              'candidates/r10-backward-prefixmask/manifest.json', 'docs/rounds/round10.md',
              'evidence/round18/block-aw-decision.json', 'evidence/round18/block-ax-decision.json']:
        read(p)
    r18 = obj('evidence/round18/37995550516/aranges-au-native/diagnostics/r18-a-ranges/ranges.json')
    assert r18['source_hashes']['parse.rs'] == INPUTS[source_paths[2]]['sha256']
    prefix = obj('evidence/round10/37702101006/mask-k/gate/prefixmask-diagnostics/prefixmask.json')
    assert prefix['frozen_source_sha256'] == INPUTS[source_paths[5]]['sha256']
    old_screen = obj('evidence/round10/37702101006/mask-k/gate/state.json')
    old_metrics = {(r['candidate'],r['round']):r['time'] for r in old_screen['metrics']}
    old_slowdowns = [100 * (old_metrics[('r10-backward-prefixmask', b)] /
                            old_metrics[('r10-record-nonempty', b)] - 1) for b in [1, 2]]
    base = 'evidence/round26/38182721892/repeat-b9-native/diagnostics/'
    repeat = obj(base + 'r26-b-a-repeat/receipt.json')
    profile = obj(base + 'r18-functions/functions.json')
    native_inventory = obj(base + 'raw-artifact-files.json')['files']
    for rel in ['r26-b-a-repeat/receipt.json', 'r18-functions/functions.json']:
        assert INPUTS[base + rel] == native_inventory[rel]
    expected = INPUTS[source_paths[0]]['sha256']
    assert repeat['source_hashes']['parse.rs'] == profile['source_hashes']['parse.rs'] == expected
    active = [r['file'] for r in repeat['rows'] if r['counts']['a_engine_calls']]
    sample_dp_calls = profile['totals']['a_dp_pass']['calls'] - repeat['totals']['full_dp_calls']
    inferred_dp_positions = repeat['totals']['full_dp_positions'] + sample_dp_calls * 4096
    subset = {k: sum(r[k] for r in r18['rows'] if r['file'] in active) for k in r18['totals']}
    phase_rows = {r['file']: r for r in profile['rows']}
    paired_models = []
    history = 'evidence/round24/38082906439/screen-h/gate/'
    history_inventory = obj(history + 'raw-artifact-files.json')['files']
    for label in ['public552', 'public552-shadow']:
        for block in [1, 2]:
            rel = f'round{block}-{label}.jsonl'
            records = [json.loads(l) for l in read(history + rel).splitlines() if l.strip()]
            assert INPUTS[history + rel] == history_inventory[rel]
            assert records[0]['methods'][label]['source_sha256'] == expected
            axis, dp_term = 0., 0.
            for row in records[1:]:
                if row['kind'] != 'file':
                    continue
                def medrep(method):
                    reps = sorted([r for r in method['reps'] if r['phase'] == 'measured'], key=lambda r: r['total_s'])
                    return reps[len(reps) // 2]
                c, inc = medrep(row['methods'][label]), medrep(row['methods']['incumbent'])
                ph = phase_rows[row['file']]
                assert ph['input_sha256'] == row['sha256']
                axis += c['total_s'] / inc['total_s'] / 28
                dp_term += c['time_s'] / inc['total_s'] / 28 * ph['functions']['a_dp_pass']['inclusive_ns'] / ph['functions']['parse']['inclusive_ns']
            paired_models.append(dict(control=label, block=block, historical_axis=axis,
                                      all_A_DP_relative_axis_pct_proxy=100 * dp_term / axis))
    counterexamples = [
        case('23bit_shift_wrap', [M - 1, M], 0),
        case('addition_crosses_23bit_boundary', [0, 1], M - 1),
        case('equal_residue_tie_prefers_shorter_length', [M, 0], 0),
        case('u32_cost_wrap_with_capped_literal_recurrence', [128, (1 << 32) - 1024],
             (1048576 - 2432 + 64 + 128) & U32,
             scope='Local suffix-cost recurrence compatible with literal price1152 and nxt2432; no full parse-input reachability claim.'),
    ]
    # The guard is validated in a deliberately small modular domain, plus seeded u32 cases.
    reduced, reduced_safe, failures = 0, 0, 0
    for a, b, c, price in itertools.product(range(16), range(16), range(16), range(8)):
        costs = [a, b, c]
        reduced += 1
        if safe(costs, price, 8):
            reduced_safe += 1
            failures += min(range(3), key=lambda i: (costs[i], i)) != min(range(3), key=lambda i: ((costs[i]+price)%8, i))
    assert failures == 0
    rng = random.Random(260032)
    actual, accepted = 20000, 0
    for _ in range(actual):
        n = rng.randrange(1, 33)
        center = rng.randrange(1 << 32)
        spread = rng.choice([16, M//2, M, M*2, 1 << 32])
        costs = [(center+rng.randrange(spread)) & U32 for _ in range(n)]
        price = rng.randrange(1 << 32)
        if safe(costs, price):
            accepted += 1
            assert min(range(n), key=lambda i: (costs[i], i)) == min(range(n), key=lambda i: packed(costs[i], price, i+3))
    # Validate mask recurrence/shortest ties for finite ternary arrays, all prefix widths.
    sequences = queries = 0
    for n in range(1, 8):
        for costs in itertools.product(range(3), repeat=n):
            sequences += 1
            masks = mask_offsets(costs)
            for p in range(n):
                for width in range(1, n-p+1):
                    mask = masks[p] & ((1 << width)-1)
                    got = mask.bit_length()-1
                    expect = min(range(width), key=lambda k: (costs[p+k], k))
                    assert got == expect
                    queries += 1
    assert mask_offsets([5, 5])[0] == 1 and mask_offsets([5, 5], strict=True)[0] == 3
    result = dict(
        status='VERIFIED_SOURCE_RECEIPT_AND_FINITE_MODEL_REVIEW_WITH_INFERRED_DECISION',
        generated_utc=datetime.now(timezone.utc).isoformat(),
        source_mapping=dict(normalized_function_sha256=mapping, D_dp_552_equals_R10_parent=d_same,
                            normalization='Only CRLF converted to LF; function starts at pub fn and ends at balanced closing brace.'),
        r10_measured_counts=prefix['totals'],
        r10_time_slowdowns_vs_record_pct=old_slowdowns,
        r18_all=counts_summary(r18['totals']),
        r18_restricted_to_552_active_file_names=counts_summary(subset),
        active_552_files=active,
        current_552_coarse_phases=profile['totals'],
        current_552_full_dp_totals=repeat['totals'],
        current_552_publication_budget=dict(status='INFERRED_FROM_SAME_SOURCE_FULL_AND_COARSE_OBSERVERS',
            full_positions=repeat['totals']['full_dp_positions'], sample_dp_calls=sample_dp_calls,
            fixed_sample_span=4096, inferred_all_dp_positions=inferred_dp_positions,
            max_extra_tail_publications=259 * profile['totals']['a_dp_pass']['calls'],
            scope='Every-position mask publication ledger, not a new performance measurement. Initial tail setup can be special-cased.'),
        historical_paired_weight_models=paired_models,
        counterexamples=counterexamples,
        guard=dict(expression='max-min < 2^23 and ((min+price) mod 2^23) <= ((max+price) mod 2^23)',
                   assumptions=['Nonempty chunk; constant lc+base within chunk; len in3..258; raw extrema correct and finalized.',
                                'Raw argmin breaks equal-cost ties toward shortest length; compare resulting packed keys across chunks.',
                                'All other states use original scalar packed loop. Original record ordering and strict outer update preserved.'],
                   argument='The raw interval width is below one modulus, so translated residues wrap at most once. Endpoint order excludes that wrap; residue order and ties then match raw order. Since2^23 divides2^32, wrapping addition before shifting has exactly this residue.',
                   cost='R10 stores minima only. This guard needs max as well, or a separately proved whole-pass invariant; do not get max by scanning every chunk and claim constant query cost.'),
        finite_model=dict(reduced_domain={'cost_alphabet':list(range(16)),'price_alphabet':list(range(8)),'modulus':8,
                                         'cases':reduced,'accepted_guard_cases':reduced_safe,'failures':failures},
                          u32_random={'seed':260032,'cases':actual,'accepted_guard_cases':accepted,'failures':0},
                          mask_ternary={'lengths':'1..7','sequences':sequences,'prefix_queries':queries,'failures':0},
                          scope='Finite Python checks support the stated arithmetic/recurrence only; no whole-input proof or Rust/Lean acceptance.'),
        decision='NO_GO for direct raw-cost32mask migration or full proof/CI investment now; retain guarded unaligned32mask only as a conditional diagnostic hypothesis.',
        single_missing_observation='One frozen552 guarded32mask shadow trace with unchanged outputs, per-file scalar terms, constant-price chunks by width, safe/fallback counts and publication/pop counts, separated full/sample passes. No new measurement was run by this review.',
        limits=['R18 restricted rows share file names but are not552 trajectory. Neither source identity nor identical corpus implies identical calls/prices.',
                'Inclusive clocks overlap; do not sum a_dp_pass and a_sample_pass. Profile fractions times historical paired weights are planning proxies, not speedup bounds.',
                'Query-operation counts are not instructions, loads or elapsed time. Current source/CPU performance gain, fullgate, admission and rewards remain UNKNOWN.',
                'A packed counterexample is a helper-state counterexample; reachable full parse inputs are not claimed.',
                'No candidate/source modification, Rust/Lean execution, CI, network, Git, wallet or submission action.'],
        input_files=INPUTS,
    )
    result['script_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    (OUT/'review.json').write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'status':result['status'],'output':str(OUT/'review.json'),
                      'models':paired_models,'finite_model':result['finite_model'],
                      'all_stats':result['r18_all'],'subset_stats':result['r18_restricted_to_552_active_file_names']},ensure_ascii=False))


if __name__ == '__main__':
    main()
