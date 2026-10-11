"""Freshly cross-check every delivered coordinate grid against captured scorer."""
from datetime import datetime, timezone
import ast
import csv
import importlib
import json
import math

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT
OUT = ROOT / 'evidence/round26/score-verification'


def main():
    replay = M.Replay(ROOT / 'evidence/round26/official-start-live', ROOT / 'evidence/round26/official-rules-start-live')
    from round3 import load_scorer
    scorer = load_scorer(replay.rules / 'validator--scoring--pareto.py')
    bounds = scorer.Boundaries(replay.policy['max_balanced_time_ratio'], replay.policy['max_mean_file_compression_pct'])
    base = [scorer.Point(*p) for p in replay.base]

    def official(points):
        additions = [scorer.Point(*p) for p in points if 0 < p[1] <= bounds.time_s and 0 < p[2] <= bounds.ratio_pct
                     and not any(q.time_s <= p[1] and q.ratio_pct <= p[2] for q in base)]
        fs = scorer.pareto_front(base + additions)
        return scorer.local_global_improvement_space_log_weights(fs, bounds)

    errors, cases = [], 0
    for file in ['fast-grid-29785.csv', 'compression-grid-29785.csv', 'middle-grid-29785.csv']:
        with (OUT / file).open(encoding='utf-8', newline='') as handle:
            for row in csv.DictReader(handle):
                name, x, y = row['route'], float(row['x']), float(row['y_pct'])
                value = 100 * official([(name, x, y)]).get(name, 0)
                errors.append(abs(value - float(row['share_pct'])))
                cases += 1
    focused = json.loads((OUT / 'focused-map-29785.json').read_bytes())
    for row in focused['joint_scenarios']:
        w = official([('A', row['A_x'], row['A_y_pct']), ('B', row['B_x'], row['B_y_pct'])])
        errors.extend([abs(100 * w.get('A', 0) - row['A_joint_pct']), abs(100 * w.get('B', 0) - row['B_joint_pct'])])
        cases += 1
    # Check the most sensitive endpoint sides as well as ordinary grid points.
    sensitive = []
    for name, x, y in [('fast', replay.byid['632']['metrics']['balanced_time_ratio'], 36.35),
                       ('fast', replay.byid['612']['metrics']['balanced_time_ratio'], 36.2),
                       ('compression', replay.byid['628']['metrics']['balanced_time_ratio'], replay.byid['636']['metrics']['mean_file_compression_pct'])]:
        variants = [(name, math.nextafter(x, 0), y), (name, x, y), (name, math.nextafter(x, math.inf), y)] if name == 'fast' else [(name, x, math.nextafter(y, 0)), (name, x, y), (name, x, math.nextafter(y, math.inf))]
        for point in variants:
            mine = replay.score([point]).get(name, {}).get('share_pct', 0)
            value = 100 * official([point]).get(name, 0)
            errors.append(abs(mine - value))
            cases += 1
            sensitive.append({'point': point, 'independent_pct': mine, 'official_pct': value})
    assert max(errors) < 1e-10
    ref_paths = [ROOT / ('references/' + path) for path in ['round25-public-628', 'round26-public-629']]
    source_hashes = {}
    for file in ['parse.rs', 'Parse.lean']:
        assert ref_paths[0].joinpath(file).read_bytes() == ref_paths[1].joinpath(file).read_bytes()
        source_hashes[file] = M.digest(ref_paths[0] / file)
    x628 = replay.byid['628']['metrics']['balanced_time_ratio']
    x629 = replay.byid['629']['metrics']['balanced_time_ratio']
    y628 = replay.byid['628']['metrics']['mean_file_compression_pct']
    y629 = replay.byid['629']['metrics']['mean_file_compression_pct']
    assert y628 == y629
    files = list((ROOT / 'scripts').glob('r26-score-*.py'))
    for file in files:
        ast.parse(file.read_text(encoding='utf-8'), filename=str(file))
    result = {'status': 'VERIFIED_ALL_DELIVERED_GRIDS_AND_JOINTS_AGAINST_CAPTURED_SCORER',
              'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': replay.context,
              'scenario_count': cases, 'comparison_values': len(errors), 'max_error_pp': max(errors),
              'sensitive_endpoint_sides': sensitive,
              'same_source_formal_628_629': {'rust_lean_bytes_identical': True, 'files_sha256': source_hashes,
                                            '628_x': x628, '629_x': x629, '628_y_pct': y628, '629_y_pct': y629,
                                            'same_source_formal_time_change_pct': 100 * (x629 / x628 - 1),
                                            'meaning': 'One extra formal same-source observation; not an independent implementation, stability bound, or additional candidate.'},
              'scripts_ast_parse': 'PASS',
              'scripts_sha256': {p.relative_to(ROOT).as_posix(): M.digest(p) for p in files},
              'deliverable_hashes': {p.relative_to(ROOT).as_posix(): M.digest(p) for p in OUT.iterdir() if p.is_file() and p.name != 'verification-29785.json'},
              'limits': ['Agreement validates arithmetic against captured source. Hypothetical coordinates remain nonmeasurement.',
                         'No live refresh, admission, private performance, formal result, or chain payment is inferred.']}
    M.dump(OUT / 'verification-29785.json', result)
    print(json.dumps({k: result[k] for k in ['status', 'scenario_count', 'comparison_values', 'max_error_pp', 'same_source_formal_628_629']}, indent=2))


if __name__ == '__main__':
    main()
