"""Download staged text receipts and recompute official public axes from raw reps."""
from __future__ import annotations
import argparse
import importlib.util
import json
import re
from pathlib import Path
import statistics
import subprocess
import sys
import uuid

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
    ap.add_argument('phase', nargs='?', choices=['screen', 'refine', 'gate', 'extraction'], default='screen')
    ap.add_argument('--snapshot')
    ap.add_argument('--round', choices=['4', '5', '6', '7'], default='4', help='Receipt namespace; original round4 remains the default')
    ap.add_argument('--batch', help='Matrix batch label; omit for legacy single-job artifacts')
    args = ap.parse_args()
    assert args.batch is None or re.fullmatch(r'[a-z0-9-]{1,48}', args.batch)
    assert args.run_id.isdecimal()
    target = ROOT / 'evidence' / ('round' + args.round) / args.run_id
    if args.batch:
        target = target / args.batch
    target = target / args.phase
    if args.mode == 'analyze':
        if args.phase == 'extraction':
            raise ValueError('Extraction diagnostics have no performance or proof verdict to analyze')
        analyze(target, args.snapshot); return
    helper = module('round4_gh', ROOT / 'scripts/collect-round2.py')
    env = helper.gh_env()
    meta = json.loads(helper.run(['run', 'view', args.run_id, '--repo', 'HuanHuanHuanFFF/Miner', '--json', 'databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'], env))
    artifacts = json.loads(helper.run(['api', f'repos/HuanHuanHuanFFF/Miner/actions/runs/{args.run_id}/artifacts'], env))['artifacts']
    print('STATUS', args.run_id, meta['status'], meta['conclusion'], 'artifacts', [(a['name'], a['size_in_bytes']) for a in artifacts if not a['expired']], flush=True)
    if args.mode == 'status':
        print('ACTIVE_STEPS', [s['name'] for j in meta['jobs'] for s in j['steps'] if s['status'] == 'in_progress']); return
    batch_suffix = '-' + args.batch if args.batch else ''
    name = f'r{args.round}-{args.run_id}{batch_suffix}-{args.phase}'
    artifact = next((a for a in artifacts if a['name'] == name and not a['expired']), None)
    if artifact is None:
        print('Requested phase receipt is not available yet.'); return
    target.parent.mkdir(parents=True, exist_ok=True)
    marker = 'research.json' if args.phase == 'extraction' else 'state.json'
    if not (target / marker).exists():
        # Download into a new folder: an interrupted transfer must not masquerade
        # as a complete receipt merely because state.json arrived first.
        stage = target.parent / ('.' + args.phase + '-download-' + uuid.uuid4().hex)
        # Path.mkdir uses inherited workspace permissions on Windows; Python's
        # secure tempfile mode 0700 excludes the restricted worker's read ACL.
        stage.mkdir()
        subprocess.run(['gh', 'run', 'download', args.run_id, '--repo', 'HuanHuanHuanFFF/Miner',
                        '--name', name, '--dir', str(stage)], env=env, check=True,
                       capture_output=True, text=True, encoding='utf-8', timeout=180)
        state = json.loads((stage / marker).read_text())
        assert state['run_id'] == args.run_id and state['git_sha'] == meta['headSha']
        assert not args.batch or state['batch'] == args.batch
        for metric in state.get('metrics', []):
            assert (stage / f"round{metric['round']}-{metric['candidate']}.jsonl").is_file()
        evidence_root = (ROOT / 'evidence' / ('round' + args.round)).resolve()
        assert stage.resolve().is_relative_to(evidence_root)
        assert target.resolve().is_relative_to(evidence_root) and not target.is_symlink()
        if target.exists():
            backup = target.with_name(target.name + '-incomplete-' + uuid.uuid4().hex[:8])
            assert backup.resolve().is_relative_to(evidence_root)
            target.rename(backup)
            print('Preserved earlier incomplete receipt:', backup.relative_to(ROOT), flush=True)
        stage.rename(target)
    (target / 'ci-run.json').write_text(json.dumps(meta, indent=2) + '\n')
    (target / 'artifact-receipt.json').write_text(json.dumps(artifact, indent=2) + '\n')
    if meta['status'] == 'completed' and args.phase == 'gate':
        log = helper.run(['run', 'view', args.run_id, '--repo', 'HuanHuanHuanFFF/Miner', '--log'], env)
        (target / 'ci.log').write_text(log, encoding='utf-8')
    if args.phase == 'extraction':
        report = json.loads((target / marker).read_text())
        print('RESEARCH_ONLY', {name: item['extraction_accepted'] for name, item in report['extractions'].items()},
              'cost', report.get('cost_differential'), 'PROOF_NOT_RUN')
    else:
        analyze(target, args.snapshot)


if __name__ == '__main__':
    main()
