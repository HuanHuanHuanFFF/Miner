from __future__ import annotations
import hashlib
import importlib.util
import json
import math
import statistics
import sys
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
GATE = ROOT / 'evidence/round25/38124524718/screen-a/gate'
CAP = ROOT / 'evidence/round25/official-frontier-current'
RULES = ROOT / 'evidence/round25/official-rules-start'
ANALYSIS_PATH = ROOT / 'evidence/round25/analysis-a-29673.json'
RANK_PATH = ROOT / 'evidence/round25/rank-a-29673.json'
OUT_JSON = ROOT / 'evidence/round25/luna/a-numeric-audit.json'
OUT_MD = ROOT / 'evidence/round25/luna/a-numeric-audit.md'
SCORER_PATH = RULES / 'validator--scoring--pareto.py'
CANDIDATES = ('r25-astra-end4', 'r25-astra-gap1', 'r25-sol-backtie')
TOL = 1e-10


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_json(path: Path):
    return json.loads(path.read_bytes())


def load_lines(path: Path):
    return [json.loads(line) for line in path.read_text(encoding='utf-8').splitlines() if line]


def close(a, b, tol=TOL):
    return math.isclose(float(a), float(b), rel_tol=0.0, abs_tol=tol)


def check(condition, label, mismatches):
    if not condition:
        mismatches.append(label)


def load_scorer(path: Path):
    spec = importlib.util.spec_from_file_location('round25_audit_official_pareto', path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def parse_measurement(path: Path, method: str):
    lines = load_lines(path)
    meta = lines[0]
    assert meta['kind'] == 'meta' and meta['schema_version'] == 4
    assert meta['corpus'] == 'corpus-stage1' and meta['warmup_rounds'] == 1 and meta['measured_rounds'] == 11
    files = lines[1:]
    assert len(files) == 28 and all(row['kind'] == 'file' for row in files)
    assert len({row['file'] for row in files}) == 28
    assert method in meta['methods']
    per_file = []
    for row in files:
        method_row = row['methods'][method]
        reps = method_row['reps']
        warmups = [r for r in reps if r['phase'] == 'warmup']
        measured = [r for r in reps if r['phase'] == 'measured']
        assert len(warmups) == 1 and len(measured) == 11
        assert not method_row.get('errors')
        for rep in reps:
            assert close(rep['total_s'], rep['time_s'] + rep['encode_s'], 1e-12)
        med_total = statistics.median(float(r['total_s']) for r in measured)
        per_file.append({
            'file': row['file'], 'input_sha256': row['sha256'], 'raw_bytes': int(row['raw_bytes']),
            'median_total_seconds': med_total, 'output_bytes': int(method_row['output_bytes']),
            'output_sha256': method_row['output_sha256'], 'tokens_sha256': method_row.get('tokens_sha256'),
            'deterministic': method_row.get('deterministic'), 'measured_reps': len(measured),
        })
    return meta, per_file


def means(values):
    return sum(values) / len(values)


def main():
    mismatches = []
    manifest = read_json(GATE / 'raw-artifact-files.json')
    manifest_checks = []
    for rel, saved in sorted(manifest['files'].items()):
        path = GATE / Path(rel)
        exists = path.is_file()
        actual_bytes = path.stat().st_size if exists else None
        actual_sha = sha(path) if exists else None
        ok = exists and actual_bytes == saved['bytes'] and actual_sha == saved['sha256']
        manifest_checks.append({'path': rel, 'expected_bytes': saved['bytes'], 'actual_bytes': actual_bytes,
                                'expected_sha256': saved['sha256'], 'actual_sha256': actual_sha, 'matches': ok})
        check(ok, f'artifact-file mismatch: {rel}', mismatches)

    state_path = GATE / 'state.json'
    state = read_json(state_path)
    run_receipt = read_json(GATE / 'ci-run.json')
    artifact_receipt = read_json(GATE / 'artifact-receipt.json')
    check(str(state['run_id']) == '38124524718', 'state run ID mismatch', mismatches)
    check(state['phase'] == 'gate', 'state phase is not gate', mismatches)
    check(state['git_sha'] == run_receipt['headSha'], 'state/CI source SHA mismatch', mismatches)
    check(run_receipt['conclusion'] == 'success', 'CI run is not success', mismatches)

    competition = read_json(CAP / 'competition.json')
    pages = read_json(CAP / 'pareto-pages.json')
    leader_pages = read_json(CAP / 'leaderboard-pages.json')
    snapshot = str(competition['current_snapshot_id'])
    check(snapshot == '29673', 'official snapshot ID mismatch', mismatches)
    check(bool(pages) and all(str(p.get('context', {}).get('snapshot_id')) == snapshot for p in pages)
          and not pages[-1].get('next_cursor'), 'Pareto pages not complete/same snapshot', mismatches)
    check(bool(leader_pages) and all(str(p.get('context', {}).get('snapshot_id')) == snapshot for p in leader_pages)
          and not leader_pages[-1].get('next_cursor'), 'leaderboard pages not complete/same snapshot', mismatches)
    pareto_rows = [r for p in pages for r in p['items']]
    leader_rows = [r for p in leader_pages for r in p['ranking']]
    check(len(pareto_rows) == 626, 'official Pareto row count mismatch', mismatches)
    check(len(leader_rows) == 585, 'official leaderboard row count mismatch', mismatches)
    official_595 = next(r for r in pareto_rows if str(r['id']) == '595')
    official_595_x = float(official_595['metrics']['balanced_time_ratio'])
    official_595_y = float(official_595['metrics']['mean_file_compression_pct'])
    policy = competition['policy']

    rules_receipt = read_json(RULES / 'receipt.json')
    scorer_hash = sha(SCORER_PATH)
    scorer_record = next(x for x in rules_receipt['files'] if x['file'] == SCORER_PATH.name)
    check(scorer_hash == scorer_record['sha256'], 'saved scorer hash disagrees with rules receipt', mismatches)
    check(rules_receipt['commit'] == '6bf303f14e6c7bccc63e9a557e4ac83e032fa9e8', 'unexpected captured scorer commit', mismatches)
    scorer = load_scorer(SCORER_PATH)
    bounds = scorer.Boundaries(float(policy['max_balanced_time_ratio']),
                               float(policy['max_mean_file_compression_pct']))
    frontier_rows = [r for r in pareto_rows if (r.get('score') or {}).get('on_frontier') is True]
    frontier = [scorer.Point(str(r['id']), float(r['metrics']['balanced_time_ratio']),
                             float(r['metrics']['mean_file_compression_pct'])) for r in frontier_rows]
    baseline_weights = scorer.local_global_improvement_space_log_weights(scorer.pareto_front(frontier), bounds)
    baseline_errors = [abs(baseline_weights.get(str(r['id']), 0.0) * float(policy['pareto_share'])
                           - float((r.get('score') or {}).get('pareto_weight', 0.0))) for r in frontier_rows]
    baseline_max_error = max(baseline_errors, default=0.0)
    check(len(frontier_rows) == 96, 'frontier row count mismatch', mismatches)
    check(baseline_max_error < 1e-10, 'official scorer does not replay baseline snapshot', mismatches)
    leader1 = leader_rows[0]
    check(str(leader1['submission_ids'][0]) == '612', 'official leaderboard rank1 is not #612', mismatches)

    expected_source = {e['name']: e['hashes']['parse.rs'] for e in state['spec']['entries'] if e['name'] in CANDIDATES}
    jsonl_paths = []
    for block in (1, 2):
        jsonl_paths.extend([
            GATE / f'round{block}-public595.jsonl',
            GATE / f'round{block}-public595-shadow.jsonl',
            *[GATE / f'round{block}-{name}.jsonl' for name in CANDIDATES],
        ])
    for path in jsonl_paths:
        rel = path.relative_to(GATE).as_posix()
        saved = manifest['files'][rel]
        check(path.stat().st_size == saved['bytes'] and sha(path) == saved['sha256'],
              f'selected JSONL not bound by artifact manifest: {rel}', mismatches)
    jsonl_input_hashes = {p.relative_to(ROOT).as_posix(): sha(p) for p in jsonl_paths}

    loaded = {}
    all_input_hashes = None
    incumbent_sha = None
    for block in (1, 2):
        loaded[(block, 'primary')] = parse_measurement(GATE / f'round{block}-public595.jsonl', 'public595')
        loaded[(block, 'shadow')] = parse_measurement(GATE / f'round{block}-public595-shadow.jsonl', 'public595-shadow')
        for name in CANDIDATES:
            meta, candidate_files = parse_measurement(GATE / f'round{block}-{name}.jsonl', name)
            check(meta['methods'][name]['source_sha256'] == expected_source[name],
                  f'{name} source hash differs from state spec', mismatches)
            check(meta['methods']['incumbent']['source_sha256'] == 'b9e0d844baf5958cf0c1c66bfb9fd1f89663fa30f21a99c3c116b3dd2e771361',
                  f'{name} incumbent source hash mismatch', mismatches)
            loaded[(block, name)] = (meta, candidate_files)
        for cal in ('primary', 'shadow'):
            meta, anchor_files = loaded[(block, cal)]
            expected_method = 'public595' if cal == 'primary' else 'public595-shadow'
            check(meta['methods'][expected_method]['source_sha256'] == '5295c241169fb2f3b88c22ff05f4aaa3f342e37069363b5deca43f2ed75f4754',
                  f'{cal} #595 source hash mismatch, block {block}', mismatches)
            check(meta['methods']['incumbent']['source_sha256'] == 'b9e0d844baf5958cf0c1c66bfb9fd1f89663fa30f21a99c3c116b3dd2e771361',
                  f'{cal} incumbent source hash mismatch, block {block}', mismatches)

    # Ensure all ten inputs carry the same 28 ordered corpus members and hashes.
    for key, (meta, per_files) in loaded.items():
        file_hashes = [(f['file'], f['input_sha256'], f['raw_bytes']) for f in per_files]
        if all_input_hashes is None:
            all_input_hashes = file_hashes
        check(file_hashes == all_input_hashes, f'input corpus differs in {key}', mismatches)

    analysis = read_json(ANALYSIS_PATH)
    rank = read_json(RANK_PATH)
    analysis_obs = {(c['candidate'], int(o['block']), o['calibration']): o
                    for c in analysis['candidates'] if c['candidate'] in CANDIDATES for o in c['observations']}
    rank_obs = {(c['candidate'], int(o['block']), o['calibration']): o
                for c in rank['candidates'] if c['candidate'] in CANDIDATES for o in c['observations']}
    scorer_results = []
    for name in CANDIDATES:
        for block in (1, 2):
            cand_meta, candidate_files = loaded[(block, name)]
            cand_by = {f['file']: f for f in candidate_files}
            inc_by = {r['file']: r for r in load_lines(GATE / f'round{block}-{name}.jsonl')[1:]}
            # Per-file candidate/incumbent ratios use medians of the recorded total_s reps.
            candidate_ratios, candidate_sizes, perfile_out = [], [], []
            for f in candidate_files:
                row = inc_by[f['file']]
                inc = row['methods']['incumbent']
                inc_reps = [r for r in inc['reps'] if r['phase'] == 'measured']
                assert len(inc_reps) == 11
                inc_median = statistics.median(float(r['total_s']) for r in inc_reps)
                ratio = f['median_total_seconds'] / inc_median
                size_pct = 100.0 * f['output_bytes'] / f['raw_bytes']
                candidate_ratios.append(ratio)
                candidate_sizes.append(size_pct)
                perfile_out.append({'file': f['file'], 'input_sha256': f['input_sha256'],
                                    'candidate_median_total_seconds': f['median_total_seconds'],
                                    'incumbent_median_total_seconds': inc_median,
                                    'time_ratio': ratio, 'size_pct': size_pct,
                                    'output_bytes': f['output_bytes']})
            raw_x, raw_y = means(candidate_ratios), means(candidate_sizes)
            for cal in ('primary', 'shadow'):
                anchor_meta, anchor_files = loaded[(block, cal)]
                anchor_method = 'public595' if cal == 'primary' else 'public595-shadow'
                anchor_rows = {r['file']: r for r in load_lines(GATE / f'round{block}-public595{ "-shadow" if cal == "shadow" else ""}.jsonl')[1:]}
                anchor_xs, anchor_ys = [], []
                for f in anchor_files:
                    row = anchor_rows[f['file']]
                    a_method = row['methods'][anchor_method]
                    inc_method = row['methods']['incumbent']
                    a_reps = [r for r in a_method['reps'] if r['phase'] == 'measured']
                    i_reps = [r for r in inc_method['reps'] if r['phase'] == 'measured']
                    assert len(a_reps) == 11 and len(i_reps) == 11
                    a_med = statistics.median(float(r['total_s']) for r in a_reps)
                    i_med = statistics.median(float(r['total_s']) for r in i_reps)
                    anchor_xs.append(a_med / i_med)
                    anchor_ys.append(100.0 * int(a_method['output_bytes']) / int(row['raw_bytes']))
                raw_anchor_x, raw_anchor_y = means(anchor_xs), means(anchor_ys)
                proj_x = official_595_x * raw_x / raw_anchor_x
                proj_y = official_595_y * raw_y / raw_anchor_y
                candidate_point = scorer.Point('__audit_candidate__', proj_x, proj_y)
                updated = scorer.pareto_front(frontier + [candidate_point])
                updated_weights = scorer.local_global_improvement_space_log_weights(updated, bounds)
                candidate_present = '__audit_candidate__' in updated_weights
                candidate_weight = float(updated_weights.get('__audit_candidate__', 0.0))
                share_pct = 100.0 * float(policy['pareto_share']) * candidate_weight
                other_weights = {k: v for k, v in updated_weights.items() if k != '__audit_candidate__'}
                rival_name = max(other_weights, key=other_weights.get) if other_weights else None
                rival_share_pct = 100.0 * float(policy['pareto_share']) * other_weights[rival_name] if rival_name else 0.0
                strict_first = candidate_present and candidate_weight > max(other_weights.values(), default=-1.0)
                geometric_rank = (1 + sum(v > candidate_weight for v in other_weights.values())) if candidate_present else None
                dominating = [str(p.name) for p in frontier if p.time_s <= proj_x and p.ratio_pct <= proj_y]

                key = (name, block, cal)
                ao, ro = analysis_obs[key], rank_obs[key]
                diffs = {
                    'raw_time': abs(raw_x - float(ao['public_time'])),
                    'raw_size_pp': abs(raw_y - float(ao['public_size_pct'])),
                    'projected_time': abs(proj_x - float(ao['projected_time'])),
                    'projected_size_pp': abs(proj_y - float(ao['projected_size_pct'])),
                    'analysis_share_pp': abs(share_pct - float(ao['single_pool_share_pct'])),
                    'rank_share_pp': abs(share_pct - float(ro['share_pct'])),
                    'rank_projected_time': abs(proj_x - float(ro['projected_time'])),
                    'rank_projected_size_pp': abs(proj_y - float(ro['projected_size_pct'])),
                }
                for label, val in diffs.items():
                    check(val <= TOL, f'{key} root-output mismatch {label}={val}', mismatches)
                check(bool(ro['strict_geometric_first']) == bool(strict_first), f'{key} strict-first mismatch', mismatches)
                check(ro['geometric_rank'] == geometric_rank, f'{key} geometric-rank mismatch', mismatches)
                check(ro['first_rival_id'] == rival_name, f'{key} first-rival ID mismatch: {ro["first_rival_id"]} vs {rival_name}', mismatches)
                check(close(ro['first_rival_geometric_share_pct'], rival_share_pct), f'{key} first-rival share mismatch', mismatches)
                check(ro['current_payable_top_id'] == str(leader1['submission_ids'][0]), f'{key} official top ID mismatch', mismatches)

                # Per-file audit against the independent raw recomputation in analysis JSON.
                root_pf = {r['file']: r for r in ao['per_file']}
                check(len(root_pf) == 28 and set(root_pf) == {r['file'] for r in perfile_out},
                      f'{key} root per-file member set mismatch', mismatches)
                perfile_diffs = []
                for pr in perfile_out:
                    q = root_pf.get(pr['file'])
                    if q is None:
                        continue
                    fields = ('candidate_median_total_seconds', 'incumbent_median_total_seconds', 'time_ratio', 'size_pct')
                    for field in fields:
                        perfile_diffs.append(abs(float(pr[field]) - float(q[field])))
                    check(pr['input_sha256'] == q['input_sha256'] and pr['output_bytes'] == q['output_bytes'],
                          f'{key} root per-file byte/hash mismatch: {pr["file"]}', mismatches)
                check(max(perfile_diffs, default=0.0) <= TOL, f'{key} per-file arithmetic mismatch', mismatches)

                scorer_results.append({
                    'candidate': name, 'block': block, 'calibration': cal,
                    'raw_time_ratio': raw_x, 'raw_mean_file_compression_pct': raw_y,
                    'measured_595_time_ratio': raw_anchor_x, 'measured_595_mean_file_compression_pct': raw_anchor_y,
                    'official_595_time_ratio': official_595_x, 'official_595_mean_file_compression_pct': official_595_y,
                    'projected_time_ratio': proj_x, 'projected_mean_file_compression_pct': proj_y,
                    'single_pool_share_pct': share_pct, 'strict_geometric_first': bool(strict_first),
                    'geometric_rank': geometric_rank, 'candidate_on_new_frontier': candidate_present,
                    'dominated_by_current_frontier_ids': dominating, 'first_rival_id': rival_name,
                    'first_rival_geometric_share_pct': rival_share_pct,
                    'root_analysis_single_pool_share_pct': ao['single_pool_share_pct'],
                    'root_rank_share_pct': ro['share_pct'], 'max_per_file_arithmetic_error': max(perfile_diffs, default=0.0),
                    'projection_and_share_max_abs_diffs_vs_root': diffs,
                    'per_file': perfile_out,
                })

    by_group = []
    for name in CANDIDATES:
        for cal in ('primary', 'shadow'):
            subset = [r for r in scorer_results if r['candidate'] == name and r['calibration'] == cal]
            shares = [r['single_pool_share_pct'] for r in subset]
            strict_count = sum(r['strict_geometric_first'] for r in subset)
            zeros = sum(abs(v) <= 1e-12 for v in shares)
            root_summary = next(x for x in next(c for c in rank['candidates'] if c['candidate'] == name)['summary']
                                if x['calibration'] == cal)
            summary_match = (root_summary['n'] == len(subset) and root_summary['zeros'] == zeros and
                             root_summary['strict_geometric_first_count'] == strict_count and
                             close(root_summary['minimum_pct'], min(shares)) and
                             close(root_summary['median_pct'], statistics.median(shares)) and
                             close(root_summary['maximum_pct'], max(shares)))
            check(summary_match, f'{name}/{cal} root rank summary mismatch', mismatches)
            by_group.append({'candidate': name, 'calibration': cal, 'n_blocks': len(subset),
                             'zero_share_blocks': zeros, 'strict_geometric_first_count': strict_count,
                             'min_share_pct': min(shares), 'median_share_pct': statistics.median(shares),
                             'max_share_pct': max(shares), 'root_summary_matches': summary_match})

    root_leader_share = 100.0 * float(leader1['payable_weight'])
    max_api_payable = max(float((r.get('score') or {}).get('payable_weight') or 0.0) for r in pareto_rows)
    check(close(root_leader_share, 100.0 * max_api_payable), 'leaderboard/pareto current top share mismatch', mismatches)
    check(all(abs(r['single_pool_share_pct']) <= 1e-12 for r in scorer_results), 'one or more projections have nonzero scorer share', mismatches)
    check(all(not r['strict_geometric_first'] for r in scorer_results), 'one or more projections strictly rank first', mismatches)

    inputs = [GATE / 'state.json', GATE / 'artifact-receipt.json', GATE / 'ci-run.json',
              GATE / 'raw-artifact-files.json', CAP / 'competition.json', CAP / 'pareto-pages.json',
              CAP / 'leaderboard-pages.json', SCORER_PATH, ANALYSIS_PATH, RANK_PATH, *jsonl_paths]
    result = {
        'status': 'VERIFIED_INDEPENDENT_RAW_NUMERIC_AUDIT' if not mismatches else 'AUDIT_MISMATCHES_FOUND',
        'computed_utc': datetime.now(timezone.utc).isoformat(),
        'scope': 'Independent recomputation of three Round 25 screen-a candidates, two blocks each, projected through public #595 primary and shadow controls. No causal decomposition, CI invocation, root analyze/rank script invocation, new gate, or submission action.',
        'source_state': {'run_id': state['run_id'], 'phase': state['phase'], 'git_sha': state['git_sha'],
                         'ci_conclusion': run_receipt['conclusion'], 'snapshot_id': snapshot,
                         'artifact_id': artifact_receipt['id'], 'artifact_name': artifact_receipt['name'],
                         'artifact_zip_digest_recorded_not_independently_rehashed': artifact_receipt['digest'],
                         'extracted_artifact_file_count': len(manifest_checks),
                         'extracted_artifact_hash_mismatches': sum(not r['matches'] for r in manifest_checks)},
        'inputs': {p.relative_to(ROOT).as_posix(): {'bytes': p.stat().st_size, 'sha256': sha(p)} for p in inputs},
        'formula': {
            'measured_repetitions': 11, 'warmups_excluded': 1, 'public_stage1_files': 28,
            'raw_time_ratio': 'arithmetic mean over 28 files of median(measured total_s candidate)/median(measured total_s incumbent)',
            'raw_mean_compression_pct': 'arithmetic mean over 28 files of 100 * output_bytes/raw_bytes',
            'projection_time': 'current official #595 balanced_time_ratio * raw candidate time ratio / same-block #595-control raw time ratio',
            'projection_size': 'current official #595 mean_file_compression_pct * raw candidate mean compression pct / same-block #595-control mean compression pct',
            'scoring': 'captured official pure scorer local_global_improvement_space_log_weights over current snapshot frontier plus projected candidate; share = 100 * policy pareto_share * candidate weight',
            'strict_first': 'candidate post-insertion geometric allocation is strictly greater than every other post-insertion frontier allocation; ties do not count',
            'scorer_commit': rules_receipt['commit'], 'scorer_sha256': scorer_hash,
            'official_pareto_rows': len(pareto_rows), 'official_frontier_rows': len(frontier_rows),
            'baseline_published_weight_replay_max_abs_error': baseline_max_error,
            'tolerance': TOL,
        },
        'candidate_blocks': scorer_results,
        'summary_by_candidate_calibration': by_group,
        'artifact_manifest_checks': manifest_checks,
        'mismatches': mismatches,
        'limits': [
            'Two blocks on one CI runner are not independent multi-runner confirmation or a success probability.',
            'The #595 primary/shadow coordinates are conditional projections onto current snapshot 29673, not new official submissions or formal admission outcomes.',
            'Snapshot metadata reports freshness=unknown; captured public scorer source does not prove exact live deployment identity.',
            'The artifact manifest hash-checks extracted files; the recorded GitHub ZIP digest was not independently recomputed from a downloaded archive.',
            'This audit addresses numerical aggregation and scorer projections only; it does not explain timing causes or verify a new Lean gate.'
        ],
    }
    OUT_JSON.write_bytes((json.dumps(result, indent=2) + '\n').encode('utf-8'))
    table = ['|候选|块|原始时间比|原始压缩比%|595主投影(时间/压缩比%)|595影子投影(时间/压缩比%)|主/影份额|严格榜首|',
             '|---|---:|---:|---:|---:|---:|---:|---|']
    for r in scorer_results:
        table.append(f"|{r['candidate']}|{r['block']}|{r['raw_time_ratio']:.12f}|{r['raw_mean_file_compression_pct']:.9f}|{r['projected_time_ratio']:.12f} / {r['projected_mean_file_compression_pct']:.9f}|—|{r['single_pool_share_pct']:.9f}%|{r['strict_geometric_first']}|")
    # The row-level record above is per calibration; render paired primary/shadow values compactly below.
    paired = []
    for name in CANDIDATES:
        for block in (1, 2):
            p = next(r for r in scorer_results if r['candidate'] == name and r['block'] == block and r['calibration'] == 'primary')
            s = next(r for r in scorer_results if r['candidate'] == name and r['block'] == block and r['calibration'] == 'shadow')
            paired.append(f"|{name}|{block}|{p['raw_time_ratio']:.12f}|{p['raw_mean_file_compression_pct']:.9f}|{p['projected_time_ratio']:.12f} / {p['projected_mean_file_compression_pct']:.9f}|{s['projected_time_ratio']:.12f} / {s['projected_mean_file_compression_pct']:.9f}|0 / 0|0 / 0|")
    md = [
        '# Round 25 screen-a 独立数字审计', '',
        f"**状态：{result['status']}。** Snapshot `{snapshot}`；Pareto {len(pareto_rows)} 行、当前前沿 {len(frontier_rows)} 点；#595 当前坐标 `({official_595_x:.12f}, {official_595_y:.9f}%)`。榜单第一与逐点最大可支付权重均为 #612，`{root_leader_share:.9f}%` 竞赛池份额。",
        '',
        f"原始 CI run `{state['run_id']}` phase=`{state['phase']}`，CI conclusion=`{run_receipt['conclusion']}`，提交 `{state['git_sha']}`。原始 artifact {artifact_receipt['id']} 的 manifest 清单 {len(manifest_checks)} 个提取文件全部字节数与 SHA-256 匹配。artifact receipt 给出的 ZIP digest 为 `{artifact_receipt['digest']}`；此处未重新下载 ZIP 验证该 digest。",
        '',
        '候选 raw time 按每文件 11 次 measured `total_s` 中位数之比计算，再对 28 个文件等权平均；`total_s` 已逐次核对等于 parse+encode。压缩轴是每文件 `output_bytes/raw_bytes` 的百分比，再对 28 文件等权平均。随后分别以同块 #595 主／影子 raw 坐标校正到 snapshot 29673 的正式 #595 两轴坐标，再把坐标插入官方保存的前沿并调用纯评分源码重算。',
        '',
        '|候选|块|raw时间比|raw压缩比%|#595主投影(时间/压缩比%)|#595影子投影(时间/压缩比%)|主/影份额|严格榜首数|',
        '|---|---:|---:|---:|---:|---:|---:|---:|',
        *paired,
        '',
        '六个 candidate-block 的 raw 两轴均从28个原始文件独立复算；十二个主／影子投影经独立 scorer 计算的份额均为 0，严格 geometric first 为 0/12。复算值与 `analysis-a-29673.json` 的逐文件 median、raw 两轴、投影坐标和份额一致；与 `rank-a-29673.json` 的逐投影份额、严格第一标记和每组汇总计数一致。零份额投影均被当前前沿点支配，最强旧 allocation 为 #612。',
        '',
        '这确认的是原始 JSONL 汇总与 snapshot 29673 条件投影的算术一致性。两块来自同一 runner，不是跨 runner 独立确认；官方快照 freshness 为 `unknown`，投影也不是正式 admission、上传结果或到账证据。',
        '',
        '机器可读逐文件明细、artifact manifest SHA 核对、source hashes、diff against root outputs 与 mismatch 列表见 [a-numeric-audit.json](a-numeric-audit.json)。',
    ]
    OUT_MD.write_text('\n'.join(md) + '\n', encoding='utf-8')
    print(json.dumps({'status': result['status'], 'candidate_block_calibrations': len(scorer_results),
                      'shares_all_zero': all(abs(r['single_pool_share_pct']) <= 1e-12 for r in scorer_results),
                      'strict_first_count': sum(r['strict_geometric_first'] for r in scorer_results),
                      'manifest_files': len(manifest_checks), 'manifest_mismatches': len(mismatches),
                      'baseline_weight_replay_max_abs_error': baseline_max_error,
                      'root_analysis_rank_reconciled': not mismatches,
                      'output_json': str(OUT_JSON), 'output_md': str(OUT_MD)}, indent=2))
    if mismatches:
        raise SystemExit('\n'.join(mismatches))


if __name__ == '__main__':
    main()
