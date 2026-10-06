"""Staged public experiments: early receipts, refinement, then fresh official gates."""
from __future__ import annotations
import dataclasses
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import statistics
import subprocess
import sys

from round3 import load_scorer, diagnostics, TIME_FACTOR, SIZE_FACTOR

ROOT = Path(__file__).resolve().parents[1]


def save(path, value):
    path.write_text(json.dumps(value, indent=2, allow_nan=False) + '\n', encoding='utf-8')


def validate(label):
    assert re.fullmatch(r'[a-z0-9-]{1,48}', label)
    spec = json.loads((ROOT / 'evidence/round4' / (label + '.json')).read_text())
    names = set()
    for e in spec['entries']:
        assert re.fullmatch(r'[A-Za-z0-9_-]+', e['name']) and e['name'] not in names
        names.add(e['name'])
        path = (ROOT / e['path']).resolve()
        assert path.is_relative_to(ROOT.resolve())
        assert set(e['hashes']) == {'parse.rs', 'Parse.lean'}
        for f, h in e['hashes'].items():
            data = (path / f).read_bytes()
            assert 0 < len(data) <= 524288 and hashlib.sha256(data).hexdigest() == h, (e['name'], f)
    assert {'probe3', 'r3-432-fast3', 'public432'} <= names
    assert 1 <= spec['screen_blocks'] <= 4 and 0 <= spec['refine_blocks'] <= 4
    return spec


def summarize(state, pages, scorer):
    from collections import defaultdict
    rows = [r for p in pages for r in p['items']]
    official = {r['id']: r for r in rows}
    frontier = [r for r in rows if (r.get('score') or {}).get('on_frontier')]
    points = [scorer.Point(r['id'], r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in frontier]
    weights = scorer.local_global_improvement_space_log_weights(points)
    assert max(abs(weights[r['id']] - r['score']['pareto_weight']) for r in frontier) < 1e-10
    metrics = state['metrics']
    by = {(m['candidate'], m['round']): m for m in metrics}
    result = []
    for entry in state['spec']['entries']:
        name = entry['name']
        measured = [m for m in metrics if m['candidate'] == name]
        if len(measured) < state['spec']['screen_blocks']:
            continue
        anchor = entry.get('anchor', 'public432')
        anchor_entry = next(e for e in state['spec']['entries'] if e['name'] == anchor)
        formal = official[anchor_entry['formal_id']]['metrics']
        blocks = [m['round'] for m in measured if (anchor, m['round']) in by and ('r3-432-fast3', m['round']) in by]
        if not blocks:
            continue
        x = statistics.mean(by[name, b]['time'] for b in blocks)
        y = by[name, blocks[0]]['size_pct']
        ax = [formal['balanced_time_ratio'] * by[name, b]['time'] / by[anchor, b]['time'] for b in blocks]
        ay = formal['mean_file_compression_pct'] * y / by[anchor, blocks[0]]['size_pct']
        def geometry(tx, sy):
            dominators = [p.name for p in points if p.time_s <= tx and p.ratio_pct <= sy]
            ok = not dominators and tx <= 10 and sy <= 40
            f = scorer.pareto_front(points + [scorer.Point('hypothetical', tx, sy)])
            weight = scorer.local_global_improvement_space_log_weights(f).get('hypothetical', 0) if ok else 0
            closest = min((p.ratio_pct for p in points if p.time_s <= tx), default=40)
            return {'time': tx, 'size_pct': sy, 'on_frontier': ok, 'dominating_ids': dominators,
                    'conditional_geometry_weight': weight, 'size_gap_pp': max(0, sy - closest)}
        own = geometry(statistics.mean(ax), ay)
        fixed = geometry(x * TIME_FACTOR, y * SIZE_FACTOR)
        stress = geometry(max(ax) * 1.01, ay)
        result.append({'candidate': name, 'control': entry.get('control', False), 'blocks': blocks,
                       'time': x, 'size_pct': y, 'own_anchor': own, 'fixed_427': fixed, 'stress_1pct': stress,
                       'time_change_pct_vs_fast3': [100 * (by[name, b]['time'] / by['r3-432-fast3', b]['time'] - 1) for b in blocks],
                       'size_change_pp_vs_fast3': y - by['r3-432-fast3', blocks[0]]['size_pct'],
                       'equivalence': state.get('equivalence', {}).get(name)})
    return sorted(result, key=lambda r: (-int(r['own_anchor']['on_frontier'] and r['fixed_427']['on_frontier']),
                                         -r['stress_1pct']['on_frontier'], -r['own_anchor']['conditional_geometry_weight'],
                                         r['own_anchor']['size_gap_pp'], r['time']))


def cpu_diagnostics(name, measurement, output):
    crate = Path(measurement.meta.methods[name].crate_dir)
    lib = crate / 'target/release/libcandidate.so'
    assert lib.is_file()
    target = output / 'cpu'
    target.mkdir(exist_ok=True)
    meta = {'library_sha256': hashlib.sha256(lib.read_bytes()).hexdigest(),
            'source_sha256': measurement.meta.methods[name].source_sha256,
            'scope': 'code-generation diagnostics, not timing or proof evidence'}
    for label, cmd in [('size', ['size', str(lib)]), ('symbols', ['nm', '-S', '--size-sort', '--demangle', str(lib)]),
                       ('assembly', ['objdump', '-d', '-C', '-Mintel', str(lib)])]:
        r = subprocess.run(cmd, capture_output=True, text=True)
        text = r.stdout
        cap = 2_000_000
        (target / f'{name}-{label}.txt').write_text(text[:cap], encoding='utf-8')
        meta[label] = {'exit_code': r.returncode, 'full_characters': len(text), 'truncated': len(text) > cap}
    save(target / (name + '-metadata.json'), meta)


def main():
    phase = sys.argv[1]
    label = os.environ.get('ROUND4_SPEC', sys.argv[2] if len(sys.argv) > 2 else 'batch-a')
    spec = validate(label)
    if phase == 'preflight':
        print('PREFLIGHT', label, len(spec['entries']), 'hash-bound source/proof pairs'); return
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    assert os.environ.get('GITHUB_REPOSITORY') == 'HuanHuanHuanFFF/Miner'
    from bench import corpora
    from bench.driver import Config, Keep, run
    from bench.results import INCUMBENT
    upstream = Path(os.environ['DEFLATE_ROOT'])
    output = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts'
    output.mkdir(exist_ok=True)
    state_path = output / 'state.json'
    if state_path.exists():
        state = json.loads(state_path.read_text())
        assert state['spec'] == spec
    else:
        state = {'spec': spec, 'batch': label, 'phase': 'initialized', 'metrics': [], 'failures': [], 'gates': {}, 'equivalence': {},
                 'git_sha': os.environ['GITHUB_SHA'], 'run_id': os.environ['GITHUB_RUN_ID']}
    pages = json.loads((ROOT / spec['snapshot_pages']).read_text())
    state['snapshot'] = pages[0]['context']
    scorer = load_scorer(upstream / 'validator/scoring/pareto.py')
    cpu = str(min(os.sched_getaffinity(0)))
    config = dataclasses.replace(Config.from_env(upstream / 'validator'), reps=11, warmup=1, cpus=cpu, keep=Keep.NEVER, bars=False)
    state['cpu_affinity'] = cpu
    corpus = corpora.load(upstream / 'validator').by_name('corpus-stage1')
    entries = {e['name']: e for e in spec['entries']}
    controls = [n for n, e in entries.items() if e.get('control')]
    paths = {n: ROOT / e['path'] for n, e in entries.items()}

    def measure(block, names):
        for name in names:
            print(f'MEASURE_BEGIN {block} {name}', flush=True)
            keep = phase == 'screen' and block == 1 and spec.get('cpu_diagnostics', False)
            try:
                observation = run(dataclasses.replace(config, keep=Keep.ALWAYS if keep else Keep.NEVER), {name: paths[name] / 'parse.rs'}, corpus)
                measured = observation.only()
                assert not measured.failures(name) + measured.failures(INCUMBENT)
            except Exception as exc:
                state['failures'].append({'name': name, 'block': block, 'error': str(exc), 'detail': getattr(exc, 'detail', None)})
                save(state_path, state)
                if name in controls:
                    raise
                continue
            raw = list(measured.raw_records)
            rows = [r for r in raw if r['kind'] == 'file']
            assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
            rawpath = output / f'round{block}-{name}.jsonl'
            rawpath.write_text(''.join(json.dumps(r) + '\n' for r in raw), encoding='utf-8')
            if block > 1:
                first = [json.loads(l) for l in (output / f'round1-{name}.jsonl').read_text().splitlines()]
                before = [r for r in first if r['kind'] == 'file']
                for a, b in zip(before, rows, strict=True):
                    assert a['sha256'] == b['sha256']
                    for method in (name, INCUMBENT):
                        for key in ('output_bytes', 'output_sha256', 'tokens_sha256'):
                            assert a['methods'][method][key] == b['methods'][method][key]
            files = [f for f in measured.files if f.raw_bytes]
            metric = {'candidate': name, 'round': block, 'time': statistics.mean(f.methods[name].total_s / f.methods[INCUMBENT].total_s for f in files),
                      'size_pct': statistics.mean(100 * f.methods[name].output_bytes / f.raw_bytes for f in files),
                      'parse_s': measured.totals(name).parse_s, 'total_s': measured.totals(name).total_s,
                      'output_bytes': measured.totals(name).output_bytes, 'source_sha256': hashlib.sha256((paths[name] / 'parse.rs').read_bytes()).hexdigest()}
            state['metrics'].append(metric)
            print('MEASUREMENT ' + json.dumps(metric), flush=True)
            if keep:
                cpu_diagnostics(name, measured, output)
            save(state_path, state)

    def finish():
        for n, e in entries.items():
            ref = e.get('expected_equivalent_to')
            if not ref or not (output / f'round1-{n}.jsonl').exists():
                continue
            a = [json.loads(l) for l in (output / f'round1-{n}.jsonl').read_text().splitlines()]
            b = [json.loads(l) for l in (output / f'round1-{ref}.jsonl').read_text().splitlines()]
            aa = {r['file']: r for r in a if r['kind'] == 'file'}
            bb = {r['file']: r for r in b if r['kind'] == 'file'}
            changed = [f for f in aa if any(aa[f]['methods'][n][key] != bb[f]['methods'][ref][key] for key in ('tokens_sha256', 'output_sha256'))]
            state['equivalence'][n] = {'reference': ref, 'public_token_and_output_equal': not changed, 'changed_files': changed,
                                       'scope': 'finite public corpus only; no all-input equivalence claim'}
        state['summary'] = summarize(state, pages, scorer)
        state['phase'] = phase
        save(state_path, state)
        save(output / (phase + '-summary.json'), state)
        print('ROUND4_PHASE ' + json.dumps({'phase': phase, 'summary': state['summary'], 'gates': state['gates'], 'failures': state['failures']}), flush=True)

    if phase == 'screen':
        perf = subprocess.run(['bash', '-c', 'if command -v perf >/dev/null 2>&1; then perf stat -e cycles,instructions,branches,branch-misses,cache-misses -- true; else echo PERF_NOT_INSTALLED; fi'], capture_output=True, text=True)
        save(output / 'perf-capability.json', {'returncode': perf.returncode, 'stdout': perf.stdout, 'stderr': perf.stderr, 'scope': 'availability probe only, not candidate profile'})
        for block in range(1, spec['screen_blocks'] + 1):
            names = list(entries)
            measure(block, names if block % 2 else list(reversed(names)))
        finish()
    elif phase == 'refine':
        selected = [r['candidate'] for r in state['summary'] if not r['control']][:spec['shortlist']]
        state['selected'] = selected
        for block in range(spec['screen_blocks'] + 1, spec['screen_blocks'] + spec['refine_blocks'] + 1):
            names = controls + selected
            measure(block, names if block % 2 else list(reversed(names)))
        finish()
    elif phase == 'gate':
        names = spec.get('gate_candidates')
        if names is None:
            names = [r['candidate'] for r in state['summary'] if not r['control'] and r['candidate'] in state.get('selected', [])][:spec['gate_limit']]
        for name in names:
            folder = output / ('input-' + name)
            folder.mkdir(exist_ok=True)
            for f in ('parse.rs', 'Parse.lean'):
                shutil.copyfile(paths[name] / f, folder / f)
            target = output / (name + '-gate.json')
            cmd = [str(upstream / '.venv/bin/python'), 'validator/verifier/verify.py', str(folder), '--results', str(target), '--keep', 'always']
            print('GATE_BEGIN ' + name, flush=True)
            proc = subprocess.Popen(cmd, cwd=upstream, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            lines = []
            for line in proc.stdout:
                lines.append(line); print(line, end='', flush=True)
            code = proc.wait()
            log = ''.join(lines)
            (output / (name + '-gate.log')).write_text(log, encoding='utf-8')
            verdict = json.loads(target.read_text()) if target.exists() else {'accepted': False, 'gate_exit': code, 'origin': 'wrapper, official scoring JSON absent'}
            if verdict.get('accepted'):
                expected = next(m['output_bytes'] for m in state['metrics'] if m['candidate'] == name)
                assert verdict['corpora'] == ['corpus-stage1'] and verdict['methods']['submission']['output_bytes'] == expected
            state['gates'][name] = verdict
            save(state_path, state)
            print('GATE_RESULT ' + json.dumps({'candidate': name, 'verdict': verdict}), flush=True)
            if code:
                diagnostics(name, log, upstream)
                match = re.search(r'^workspace: (.+)$', log, re.M)
                if match:
                    work = Path(match[1].strip()).resolve()
                    assert work.parent == (upstream / 'data/verification-workspace').resolve()
                    for p in (work / 'logs').glob('*.log'):
                        shutil.copyfile(p, output / (name + '-' + p.name))
            if code == 2:
                finish(); raise RuntimeError('Official verifier infrastructure error')
        if spec.get('synthetic_validation'):
            from round3_synthetic import run_validation
            selected = [n for n, v in state['gates'].items() if v.get('accepted')]
            if selected:
                state['synthetic_validation'] = run_validation(config, paths, ['r3-432-fast3'] + selected, output)
        finish()
        if any(not v.get('accepted') for v in state['gates'].values()):
            raise SystemExit('A selected experimental gate rejected; evidence retained')
    else:
        raise ValueError(phase)
    subprocess.run(['git', 'diff', '--exit-code'], cwd=upstream, check=True)


if __name__ == '__main__':
    main()
