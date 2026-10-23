"""Read only five completed public plans; never draw inputs or inspect new runs.

Default writes only the sibling review-wide-opportunity.json; --stdout is read-only.
MAC coverage is not time coverage. A timing bound includes whole affected cells.
"""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
RUNS = {901: 40013486988, 902: 40014284237, 904: 40018666234,
        914: 40030638967, 916: 40032766690}
BASE = 'f01-d10-bmm-direct-rows'
BASE_SHA = 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
DIRECT = 'f01-d11-bmm-direct-continuous'
CATEGORIES = ('wide', 'wide_p_ge10', 'wide_p_lt10', 'cross_p2',
              'cross_p2_short_n', 'cross_p2_long_n', 'short_direct')


def require(ok, why):
    if not ok:
        raise ValueError(why)


def read(path):
    return json.loads(Path(path).read_bytes())


def identity(path):
    raw = Path(path).read_bytes()
    return {'path': Path(path).relative_to(ROOT).as_posix(), 'bytes': len(raw),
            'sha256': hashlib.sha256(raw).hexdigest()}


def describe(c):
    b, m, n, p = (c[k] for k in ('batch', 'm', 'n', 'p'))
    require(all(type(x) is int and x >= 0 for x in (b, m, n, p)), 'Bad dimensions')
    rows = b * m
    mac = rows * n * p
    wide = b > 0 and m >= 4 and p > 2 and n > 4
    # Actual existing Cross guards; USize is 64-bit in these hosted x86_64 runs.
    cross = (p == 2 and rows >= 4 and 0 < n < 2**64 and
             b*m*n < 2**64 and b*n*p < 2**64 and rows*p < 2**64)
    direct = rows > 0 and n <= 4 and p > 2
    covered_rows = b * (m // 4) * 4 if wide else 0
    wide_mac = covered_rows * n * p
    # Existing Cross uses ceil(rows/4), including a padded final row tile.
    cross_mac = mac if cross else 0
    masks = {'wide': wide, 'wide_p_ge10': wide and p >= 10,
             'wide_p_lt10': wide and p < 10, 'cross_p2': cross,
             'cross_p2_short_n': cross and n <= 4,
             'cross_p2_long_n': cross and n > 4, 'short_direct': direct}
    amounts = {k: (wide_mac if k.startswith('wide') else
                    mac if k == 'short_direct' else cross_mac) if v else 0
               for k, v in masks.items()}
    full_cols = covered_rows * n * (p // 10 * 10)
    tail_cols = covered_rows * n * (p % 10)
    scheduled = covered_rows * n * ((p + 9) // 10 * 10) if wide else 0
    require(wide_mac == full_cols + tail_cols, 'Column partition mismatch')
    require(amounts['wide_p_ge10'] + amounts['wide_p_lt10'] == wide_mac,
            'Wide p partition mismatch')
    require(not (wide and cross) and not (wide and direct) and not (cross and direct),
            'Unexpected existing-route intersection')
    if wide:
        require(c['work'] == mac, 'Guarded case work differs from true matrix MAC')
        require(wide_mac + b * (m % 4) * n * p == mac, 'Row tail mismatch')
    return {**{k: c[k] for k in ('name', 'timed', 'batch', 'm', 'n', 'p', 'work')},
            'cell': c['name'].rsplit(':', 1)[0], 'true_mac': mac,
            'masks': masks, 'covered_mac': amounts,
            'wide_four_row_groups': b * (m // 4) if wide else 0,
            'wide_covered_rows': covered_rows,
            'wide_uncovered_tail_rows': b * (m % 4) if wide else 0,
            'wide_full10_valid_mac': full_cols, 'wide_column_tail_valid_mac': tail_cols,
            'wide_scheduled10_mac_lanes': scheduled,
            'wide_padding_mac_lanes': scheduled - wide_mac,
            'cross_complete4_mac': (rows // 4) * 4 * n * p if cross else 0,
            'cross_tail_valid_mac': (rows % 4) * n * p if cross else 0,
            'cross_scheduled4_mac_lanes': ((rows + 3) // 4) * 4 * n * p if cross else 0,
            'case_time_ns': 'UNKNOWN'}


def coverage(rows, denominator):
    result = {}
    for key in CATEGORIES:
        selected = [x for x in rows if x['masks'][key]]
        covered = sum(x['covered_mac'][key] for x in selected)
        result[key] = {'cases': len(selected), 'names': [x['name'] for x in selected],
                       'whole_selected_shape_mac': sum(x['true_mac'] for x in selected),
                       'covered_mac': covered,
                       'share_of_timed_bmm_true_mac': covered / denominator if denominator else None,
                       'selected_official_work': sum(x['work'] for x in selected),
                       'affected_cells': sorted({x['cell'] for x in selected})}
        if key.startswith('wide'):
            result[key]['layout'] = {k: sum(x[k] for x in selected) for k in
                                     ('wide_four_row_groups', 'wide_covered_rows',
                                      'wide_uncovered_tail_rows', 'wide_full10_valid_mac',
                                      'wide_column_tail_valid_mac', 'wide_scheduled10_mac_lanes',
                                      'wide_padding_mac_lanes')}
            result[key]['logical_padded10_to_valid_mac_ratio'] = (
                result[key]['layout']['wide_scheduled10_mac_lanes'] / covered if covered else None)
        elif key.startswith('cross'):
            result[key]['layout'] = {k: sum(x[k] for x in selected) for k in
                                     ('cross_complete4_mac', 'cross_tail_valid_mac',
                                      'cross_scheduled4_mac_lanes')}
    return result


def timing_bounds(entry, work, stats):
    cells = {k: v['submission_ns'] * work[k] for k, v in entry['classes'].items()}
    whole = sum(cells.values())
    bmm = sum(v for k, v in cells.items() if k.startswith('bmm:'))
    require(math.isclose(whole, entry['scored_submission_total_ns'], rel_tol=1e-12,
                         abs_tol=.5), 'Summary whole/cell mismatch')
    bounds = {}
    for key, value in stats.items():
        affected = {k: cells[k] for k in value['affected_cells']}
        upper = sum(affected.values())
        bounds[key] = {'affected_whole_cells_ns': affected, 'upper_ns': upper,
                       'upper_fraction_of_whole': upper / whole,
                       'upper_fraction_of_bmm': upper / bmm,
                       'fraction_of_this_loose_bound_needed_to_save_3pct_whole':
                           .03 * whole / upper if upper else None,
                       'case_or_row_group_time_ns': 'UNKNOWN', 'expected_gain': 'UNKNOWN'}
    return {'kernel_sha256': entry['kernel_sha256'], 'whole_sub_ns': whole,
            'bmm_sub_ns': bmm, 'bounds': bounds,
            'scope': 'Hypothetical removal of entire touched cells; includes untouched cases, row tails, preparation and replay. Categories can overlap in time and must not be added.'}


def load(seed, rid):
    folder = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs' / str(rid)
    ci = read(folder / 'ci-run.json')
    require(ci['databaseId'] == rid and ci['status'] == 'completed', 'Run not completed')
    index = read(folder / 'original-artifact-hashes.json')
    artifact = (folder / index['directory']).resolve()
    require(artifact.is_relative_to(folder.resolve()), 'Artifact leaves run directory')
    require(index['artifact']['workflow_run']['head_sha'] == ci['headSha'], 'HEAD mismatch')
    for relative, expected in index['files'].items():
        path = (artifact / relative).resolve()
        require(path.is_relative_to(artifact), 'Indexed path leaves artifact')
        actual = identity(path)
        require(actual['bytes'] == expected['bytes'] and actual['sha256'] == expected['sha256'],
                'Original artifact differs: ' + relative)
    prefix = 'diagnostics/f01-d7-public-suite/public-suite/'
    def checked(name):
        require(prefix + name in index['files'], 'Unindexed input: ' + name)
        return artifact / prefix / name
    summary = read(checked('summary.json'))
    require(summary['seed'] == seed and summary['rounds'] == 25 and summary['pairs'] == 500000,
            'Wrong public protocol/seed')
    require(summary['source_commit'] == ci['headSha'] and
            summary['official_commit'] == '4b7e83841cc0c32c6529f533923c73d33b5ecf97', 'Wrong source')
    require(summary['suite_sha256'] == 'a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a' and
            summary['official_generator_sha256'] == '7198464dfc08f4bb2a3a5e31ce5a105964d1d73ad6b11ee49e682a30c04daf69',
            'Wrong public suite/generator')
    plan = read(checked('public-drawn-plan.json'))
    require(len(plan['cases']) == 156 and sum(x['timed'] for x in plan['cases']) == 152,
            'Wrong complete public case coverage')
    work = read(checked('public-cell-work.json'))
    expected_work = {k: 0 for k in work}
    for case in plan['cases']:
        if case['timed']:
            expected_work[case['name'].rsplit(':', 1)[0]] += case['work']
    require(work == expected_work, 'Drawn cases/cell work mismatch')
    bmm_rows = [describe(c) for c in plan['cases'] if c['kernel'] == 'bmm']
    timed = [x for x in bmm_rows if x['timed']]
    total_mac = sum(x['true_mac'] for x in timed)
    stats = coverage(timed, total_mac)
    entries = [x for x in summary['results'] if x['candidate'] == BASE or
               (seed == 916 and x['candidate'] == DIRECT)]
    require(any(x['candidate'] == BASE and x['kernel_sha256'] == BASE_SHA for x in entries),
            'Missing exact common a066 baseline')
    times = {}
    for entry in entries:
        v = read(checked(entry['verdict']))
        require(v['passed'] is True and v['stage'] == 'score' and len(v['rounds']) == 25 and
                v['seed'] == seed and entry['full_gate'] is True and entry['exit_code'] == 0,
                'Not a full passed original gate')
        require(v['classes'] == entry['classes'] and entry['verdict_sha256'] == identity(checked(entry['verdict']))['sha256'],
                'Summary/verdict binding mismatch')
        require(identity(checked('inputs/' + entry['candidate'] + '/Kernel.lean'))['sha256'] == entry['kernel_sha256'],
                'Copied source mismatch')
        times[entry['candidate']] = timing_bounds(entry, work, stats)
        times[entry['candidate']].update(verdict=identity(checked(entry['verdict'])),
                                        codegen_present_for_entry=entry.get('codegen') is not None)
    wide = [x for x in timed if x['masks']['wide']]
    return {'seed': seed, 'run': rid, 'source_commit': ci['headSha'],
            'evidence': {k: identity(checked(k)) for k in
                         ('public-drawn-plan.json', 'public-cell-work.json', 'summary.json')},
            'original_index': identity(folder / 'original-artifact-hashes.json'),
            'ci_run': identity(folder / 'ci-run.json'),
            'all_indexed_members_verified': len(index['files']),
            'timed_bmm_cases': len(timed), 'raw_bmm_cases': len(bmm_rows) - len(timed),
            'timed_bmm_true_mac': total_mac,
            'timed_bmm_official_work': sum(x['work'] for x in timed),
            'coverage': stats,
            'wide_layout': {k: sum(x[k] for x in wide) for k in
                            ('wide_four_row_groups', 'wide_covered_rows', 'wide_uncovered_tail_rows',
                             'wide_full10_valid_mac', 'wide_column_tail_valid_mac',
                             'wide_scheduled10_mac_lanes', 'wide_padding_mac_lanes')},
            'intersections': {k: {'cases': 0, 'mac': 0} for k in
                              ('wide_and_cross_p2', 'wide_and_short_direct', 'cross_p2_and_short_direct')},
            'time_upper_bounds': times, 'cases': bmm_rows}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--stdout', action='store_true', help='Print without writing the report JSON')
    args = parser.parse_args()
    guard_sources = []
    for name, expected in (
            ('f01-r11-crossrow-p2-pack12-proof2', '5c5e7071927400ecd75d02d69b0ce62236a50a615912d99e7f8470a9ccf19c6b'),
            ('f01-r11-crossrow-short-shared', '7cad7df494da6004b9e4b202f4d09b838ef8d4b79ba6fe934eea7287784fea28'),
            (DIRECT, '2aaa5d9e84c758a23a8c6dc1f77d800950fbaa5769aec7a38d299741c17a5f56')):
        item = identity(ROOT / 'competitions/floatlib/candidates' / name / 'Kernel.lean')
        require(item['sha256'] == expected, 'Existing route source changed: ' + name)
        guard_sources.append(item)
    results = [load(seed, rid) for seed, rid in RUNS.items()]
    data = {'schema_version': 1, 'generated_at_utc': datetime.now(timezone.utc).isoformat(),
            'script': identity(Path(__file__)), 'completed_run_allowlist': RUNS,
            'future_runs_read_or_inputs_generated': False,
            'existing_guard_sources': guard_sources,
            'wide_guard': 'batch>0, m>=4, p>2, n>4; only complete4-row groups within each batch',
            'mac_definition': 'wide=batch*4*floor(m/4)*n*p; existing Cross covers all valid rows via ceil(batch*m/4) tiles; logical padding reported separately',
            'time_rule': 'Only full touched-cell costs are bounds. No allocation of time by MAC fraction.',
            'register_layout_hypothesis': {'column_major': '10 SSE accumulators +1 A +1 B =12',
                                           'row_major': '12 SSE accumulators +3 B +1 A =16',
                                           'actual_SIMD_spill_or_speedup': 'UNKNOWN_NOT_COMPILED_HERE'},
            'runs': results}
    raw = json.dumps(data, indent=2) + '\n'
    if args.stdout:
        print(raw, end='')
    else:
        path = HERE / 'review-wide-opportunity.json'
        path.write_text(raw, encoding='utf-8')
        print(json.dumps({'report': str(path), 'sha256': identity(path)['sha256']}))


if __name__ == '__main__':
    main()
