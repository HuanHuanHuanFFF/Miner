"""Download staged text receipts and recompute official public axes from raw reps."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import statistics
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def module(name, path):
    s = importlib.util.spec_from_file_location(name, path)
    m = importlib.util.module_from_spec(s)
    sys.modules[name] = m
    s.loader.exec_module(m)
    return m


def analyze(target, snapshot=None):
    import round4
    state = json.loads((target / 'state.json').read_text())
    spec = state['spec']
    all_files = {}
    for metric in state['metrics']:
        name, block = metric['candidate'], metric['round']
        records = [json.loads(line) for line in (target / f'round{block}-{name}.jsonl').read_text().splitlines()]
        meta = records[0]
        assert meta['kind'] == 'meta' and meta['corpus'] == 'corpus-stage1'
        entry = next(e for e in spec['entries'] if e['name'] == name)
        assert meta['methods'][name]['source_sha256'] == entry['hashes']['parse.rs'] == metric['source_sha256']
        files = [r for r in records if r['kind'] == 'file']
        assert len(files) == 28 and sum(r['raw_bytes'] for r in files) == 15930000
        perfile = {}
        for row in files:
            times = {}
            for method in (name, 'incumbent'):
                r = row['methods'][method]
                assert r['deterministic'] and not r['errors']
                reps = [x for x in r['reps'] if x['phase'] == 'measured']
                assert len(reps) == 11 and all(x['total_s'] > 0 for x in reps)
                times[method] = statistics.median(x['total_s'] for x in reps)
            perfile[row['file']] = times[name] / times['incumbent']
            key = name, row['file']
            if key in all_files:
                before = all_files[key]
                assert before['sha256'] == row['sha256']
                for method in (name, 'incumbent'):
                    for f in ('tokens_sha256', 'output_sha256', 'output_bytes'):
                        assert before['methods'][method][f] == row['methods'][method][f]
            else:
                all_files[key] = row
        x = statistics.mean(perfile.values())
        y = statistics.mean(100 * r['methods'][name]['output_bytes'] / r['raw_bytes'] for r in files)
        assert abs(x - metric['time']) < 1e-12 and abs(y - metric['size_pct']) < 1e-12
        metric['per_file_time'] = perfile
    pages_path = Path(snapshot) if snapshot else ROOT / spec['snapshot_pages']
    pages = json.loads(pages_path.read_text())
    scorer = round4.load_scorer(ROOT / 'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    summary = round4.summarize(state, pages, scorer)
    for row in summary:
        name = row['candidate']
        row['gate'] = state['gates'].get(name)
        row['files_vs_fast3'] = []
        for (n, f), data in all_files.items():
            if n != name:
                continue
            base = all_files['r3-432-fast3', f]
            row['files_vs_fast3'].append({'file': f, 'output_byte_delta': data['methods'][name]['output_bytes'] - base['methods']['r3-432-fast3']['output_bytes'],
                                         'tokens_equal': data['methods'][name]['tokens_sha256'] == base['methods']['r3-432-fast3']['tokens_sha256']})
    result = {'scope': 'recomputed public metrics; all frontier coordinates are conditional, not admission or reward',
              'snapshot': pages[0]['context'], 'run_id': state['run_id'], 'git_sha': state['git_sha'], 'phase': state['phase'],
              'failures': state['failures'], 'summary': summary, 'metrics': state['metrics']}
    filename = 'analysis.json' if snapshot is None else 'analysis-snapshot-' + pages[0]['context']['snapshot_id'] + '.json'
    round4.save(target / filename, result)
    print('RECOMPUTED', state['run_id'], state['phase'], len(state['metrics']), 'paired processes; failures', len(state['failures']))
    for r in summary:
        print(r['candidate'], 'x', round(r['time'], 6), 'y', round(r['size_pct'], 6),
              'delta_vs_fast3', round(statistics.mean(r['time_change_pct_vs_fast3']), 3),
              'own_front', r['own_anchor']['on_frontier'], 'stress', r['stress_1pct']['on_frontier'],
              'equiv', r['equivalence'], 'gate', r['gate'].get('accepted') if r['gate'] else None)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('mode', choices=['status', 'pull', 'analyze'])
    ap.add_argument('run_id')
    ap.add_argument('phase', nargs='?', choices=['screen', 'refine', 'gate'], default='screen')
    ap.add_argument('--snapshot')
    args = ap.parse_args()
    assert args.run_id.isdecimal()
    target = ROOT / 'evidence/round4' / args.run_id / args.phase
    if args.mode == 'analyze':
        analyze(target, args.snapshot); return
    helper = module('round4_gh', ROOT / 'scripts/collect-round2.py')
    env = helper.gh_env()
    meta = json.loads(helper.run(['run', 'view', args.run_id, '--repo', 'HuanHuanHuanFFF/Miner', '--json', 'databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'], env))
    artifacts = json.loads(helper.run(['api', f'repos/HuanHuanHuanFFF/Miner/actions/runs/{args.run_id}/artifacts'], env))['artifacts']
    print('STATUS', args.run_id, meta['status'], meta['conclusion'], 'artifacts', [(a['name'], a['size_in_bytes']) for a in artifacts if not a['expired']])
    if args.mode == 'status':
        print('ACTIVE_STEPS', [s['name'] for j in meta['jobs'] for s in j['steps'] if s['status'] == 'in_progress']); return
    name = f'r4-{args.run_id}-{args.phase}'
    artifact = next((a for a in artifacts if a['name'] == name and not a['expired']), None)
    if artifact is None:
        print('Requested phase receipt is not available yet.'); return
    target.mkdir(parents=True, exist_ok=True)
    if not (target / 'state.json').exists():
        helper.run(['run', 'download', args.run_id, '--repo', 'HuanHuanHuanFFF/Miner', '--name', name, '--dir', str(target)], env)
    (target / 'ci-run.json').write_text(json.dumps(meta, indent=2) + '\n')
    (target / 'artifact-receipt.json').write_text(json.dumps(artifact, indent=2) + '\n')
    if meta['status'] == 'completed' and args.phase == 'gate':
        log = helper.run(['run', 'view', args.run_id, '--repo', 'HuanHuanHuanFFF/Miner', '--log'], env)
        (target / 'ci.log').write_text(log, encoding='utf-8')
    analyze(target, args.snapshot)


if __name__ == '__main__':
    main()
