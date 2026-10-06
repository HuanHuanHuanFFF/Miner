"""Collect complete CI logs and independently recompute public screen metrics."""
from __future__ import annotations
import importlib.util
import json
from pathlib import Path
import re
import statistics
import sys

ROOT = Path(__file__).resolve().parents[1]


def load_script(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    spec.loader.exec_module(mod)
    return mod


def analyze(target):
    text = (target / 'ci.log').read_text(encoding='utf-8')
    records, reported, gates = {}, {}, {}
    for line in text.splitlines():
        match = re.search(r'RAW_EVIDENCE (\d+) (\S+) (\{.*\})$', line)
        if match:
            records.setdefault((int(match[1]), match[2]), []).append(json.loads(match[3]))
        match = re.search(r'MEASUREMENT (\{.*\})$', line)
        if match:
            d = json.loads(match[1]); reported[d['round'], d['candidate']] = d
        match = re.search(r'GATE_RESULT (\{.*\})$', line)
        if match:
            d = json.loads(match[1]); gates[d['candidate']] = d['verdict']
            (target / (d['candidate'] + '-gate.json')).write_text(json.dumps(d['verdict'], indent=2) + '\n')
        for label in ('SCREEN_SUMMARY', 'REFINED_SUMMARY', 'ROUND3_SUMMARY'):
            match = re.search(label + r' (\{.*\}|\[.*\])$', line)
            if match:
                (target / (label.lower() + '.json')).write_text(json.dumps(json.loads(match[1]), indent=2) + '\n')
    plain = '\n'.join(re.sub(r'^.*?\t\d{4}-\d{2}-\d{2}T\S+\s?', '', line) for line in text.splitlines())
    for m in re.finditer(r'^GATE_DIAGNOSTIC_BEGIN (\S+) (\S+)\n(.*?)\nGATE_DIAGNOSTIC_END \1 \2$', plain, re.M | re.S):
        assert re.fullmatch(r'[A-Za-z0-9_-]+', m[1]) and re.fullmatch(r'\d{3}-[A-Za-z0-9_.-]+\.log', m[2])
        (target / (m[1] + '-' + m[2])).write_text(m[3].rstrip() + '\n', encoding='utf-8')
    if not records:
        print('No measurements; inspect CI setup logs.'); return
    assert records.keys() == reported.keys()
    metrics = []
    first = {}

    def total(method):
        assert method['deterministic'] and not method['errors']
        reps = [r for r in method['reps'] if r['phase'] == 'measured']
        assert len(reps) == 11 and all(r['total_s'] > 0 for r in reps)
        return statistics.median(r['total_s'] for r in reps)

    for (block, name), raw in sorted(records.items()):
        assert raw[0]['kind'] == 'meta' and raw[0]['corpus'] == 'corpus-stage1'
        assert raw[0]['methods'][name]['source_sha256'] == reported[block, name]['source_sha256']
        rows = [r for r in raw if r['kind'] == 'file']
        assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
        per_file = {r['file']: total(r['methods'][name]) / total(r['methods']['incumbent']) for r in rows if r['raw_bytes']}
        x = statistics.mean(per_file.values())
        y = statistics.mean(100 * r['methods'][name]['output_bytes'] / r['raw_bytes'] for r in rows if r['raw_bytes'])
        assert abs(x - reported[block, name]['time']) < 1e-12
        assert abs(y - reported[block, name]['size_pct']) < 1e-12
        for r in rows:
            old = first.setdefault((name, r['file']), r)
            assert old['sha256'] == r['sha256']
            for method in (name, 'incumbent'):
                for field in ('output_bytes', 'output_sha256', 'tokens_sha256'):
                    assert old['methods'][method][field] == r['methods'][method][field]
        (target / f'round{block}-{name}.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in raw))
        metrics.append({'round': block, 'candidate': name, 'time': x, 'size_pct': y, 'per_file_time': per_file})
    geometry = load_script('round3_geometry', ROOT / 'scripts/round3.py')
    scorer = load_script('round3_scorer', ROOT / 'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    targets = json.loads((ROOT / 'evidence/round3/frontier-targets.json').read_text())
    points = targets['points']
    official = [scorer.Point(p['id'], p['official_time'], p['official_size']) for p in points]
    pages = json.loads((ROOT / 'evidence/round3/pareto-pages.json').read_text())
    weights = scorer.local_global_improvement_space_log_weights(official)
    published = {p['id']: p['score']['pareto_weight'] for page in pages for p in page['items'] if (p.get('score') or {}).get('on_frontier')}
    max_error = max(abs(weights[k] - v) for k, v in published.items())
    assert max_error < 1e-10
    controls = {m['round']: m for m in metrics if m['candidate'] == 'probe3'}
    summaries = []
    for name in sorted({m['candidate'] for m in metrics}):
        ms = [m for m in metrics if m['candidate'] == name]
        if not all(m['round'] in controls for m in ms):
            continue
        x = statistics.mean(m['time'] for m in ms)
        y = ms[0]['size_pct']
        g = geometry.geometry(x, y, points)
        anchor_times = [0.46614327772931885 * m['time'] / controls[m['round']]['time'] for m in ms]
        anchor = geometry.geometry(statistics.mean(anchor_times) / geometry.TIME_FACTOR, y, points)
        scenario_weights = scorer.local_global_improvement_space_log_weights(scorer.pareto_front(official + [scorer.Point('candidate', anchor['calibrated_time'], anchor['calibrated_size'])]))
        per_file = []
        for filename in ms[0]['per_file_time']:
            r = first[name, filename]; c = first['probe3', filename]
            per_file.append({'file': filename, 'byte_delta_vs_probe3': r['methods'][name]['output_bytes'] - c['methods']['probe3']['output_bytes'],
                             'normalized_time_change_vs_probe3': statistics.mean(m['per_file_time'][filename] - controls[m['round']]['per_file_time'][filename] for m in ms)})
        summaries.append({'candidate': name, 'blocks': len(ms), 'public_time_mean': x,
                          'public_time_range': [min(m['time'] for m in ms), max(m['time'] for m in ms)],
                          'public_size_pct': y, 'fixed_factor': g, 'probe3_anchored': anchor,
                          'probe3_anchored_time_range': [min(anchor_times), max(anchor_times)],
                          'time_change_pct_vs_probe3_by_block': [100 * (m['time'] / controls[m['round']]['time'] - 1) for m in ms],
                          'hypothetical_anchor_geometry_share': scenario_weights.get('candidate', 0) if anchor['on_geometric_frontier'] else 0,
                          'fresh_gate': gates.get(name), 'files': per_file})
    summaries.sort(key=lambda r: (-r['probe3_anchored']['on_geometric_frontier'], -r['hypothetical_anchor_geometry_share'], r['probe3_anchored']['size_gap_pp']))
    result = {'scope': 'public stage1 research; all calibration and geometry conditional; private-stage2/admission/payment unknown',
              'snapshot': targets['context'], 'scorer_weight_reproduction_max_error': max_error,
              'summaries': summaries, 'metrics': metrics}
    (target / 'analysis.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps([{k: v for k, v in r.items() if k not in ('files', 'fresh_gate')} for r in summaries], indent=2))


def main():
    mode, run_id = sys.argv[1:3]
    assert mode in ('--status', '--collect', '--analyze') and run_id.isdecimal()
    target = ROOT / 'evidence/round3' / run_id
    if mode != '--analyze':
        helper = load_script('round3_gh', ROOT / 'scripts/collect-round2.py')
        env = helper.gh_env()
        metadata = json.loads(helper.run(['run', 'view', run_id, '--repo', 'HuanHuanHuanFFF/Miner', '--json', 'databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'], env))
        if mode == '--status':
            print(json.dumps(metadata)); return
        assert metadata['status'] == 'completed'
        target.mkdir(parents=True, exist_ok=True)
        (target / 'ci-run.json').write_text(json.dumps(metadata, indent=2) + '\n')
        log = helper.run(['run', 'view', run_id, '--repo', 'HuanHuanHuanFFF/Miner', '--log'], env)
        clean = '\n'.join(re.sub(r'\x1b\[[0-?]*[ -/]*[@-~]', '', line).rstrip() for line in log.splitlines()) + '\n'
        (target / 'ci.log').write_text(clean, encoding='utf-8')
    analyze(target)


if __name__ == '__main__':
    main()
