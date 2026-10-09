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


def screen_order(spec, block, names):
    orders = spec.get('screen_orders')
    if orders is None:
        return list(names) if block % 2 else list(reversed(names))
    assert len(orders) == spec['screen_blocks']
    assert all(len(order) == len(names) and len(set(order)) == len(order) and set(order) == set(names)
               for order in orders), 'Every frozen screen order must contain each candidate/control exactly once'
    return list(orders[block - 1])


def save(path, value):
    path.write_text(json.dumps(value, indent=2, allow_nan=False) + '\n', encoding='utf-8')


def specification_path(label):
    assert re.fullmatch(r'[a-z0-9-]{1,48}', label)
    spec_directory = os.environ.get('ROUND4_SPEC_DIR', 'evidence/round4')
    assert spec_directory in ('evidence/round4', 'evidence/round5', 'evidence/round6', 'evidence/round7', 'evidence/round8', 'evidence/round9', 'evidence/round10', 'evidence/round11', 'evidence/round12', 'evidence/round13', 'evidence/round14', 'evidence/round15', 'evidence/round16', 'evidence/round17', 'evidence/round18')
    return ROOT / spec_directory / (label + '.json')


def validate(label):
    spec = json.loads(specification_path(label).read_text())
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
    by_name = {e['name']: e for e in spec['entries']}
    for e in spec['entries']:
        ref = e.get('expected_equivalent_to')
        if ref:
            assert ref in by_name and ref != e['name']
            assert (ROOT/e['path']/'parse.rs').resolve() != (ROOT/by_name[ref]['path']/'parse.rs').resolve(), \
                f"{e['name']}: finite equivalence rejects identical source paths; inspect shared-source shadows through measurement output"
    assert 1 <= spec['screen_blocks'] <= 4 and 0 <= spec['refine_blocks'] <= 4
    if 'screen_orders' in spec:
        screen_order(spec, 1, list(by_name))
    if spec.get('native_encoder'):
        assert 'public514' in names, 'Native exact-encoder calibration requires the frozen public514 reference'
        assert set(spec.get('native_encoder_references', [])) <= names
    synthetic_refs = spec.get('synthetic_reference_candidates', [])
    assert len(synthetic_refs) == len(set(synthetic_refs)) <= 3 and set(synthetic_refs) <= names
    used = set()
    for group in spec.get('gate_groups', []):
        assert isinstance(group, list) and group and set(group) <= names
        assert not used.intersection(group) and len(group) == len(set(group))
        assert all(not e.get('control') for e in spec['entries'] if e['name'] in group)
        used.update(group)
    return spec


def grouped_gates(state):
    """Pick one smallest-output candidate per declared family, inside time caps.

    This only allocates expensive research gates; neither calibration establishes
    private-corpus eligibility or admission.
    """
    by = {r['candidate']: r for r in state['summary']}
    names, decisions = [], []
    for group in state['spec']['gate_groups']:
        eligible = [by[n] for n in group if n in by and
                    by[n]['fixed_427']['time'] <= 10 and by[n]['own_anchor']['time'] <= 10]
        chosen = min(eligible, key=lambda r: (r['size_pct'], r['time']))['candidate'] if eligible else None
        decisions.append({'group': group, 'chosen': chosen, 'eligible': [r['candidate'] for r in eligible],
                          'policy': 'minimum public size, then time; both declared time-transfer hypotheses <= 10'})
        if chosen:
            names.append(chosen)
    return names, decisions


def confirmation_gates(state, names):
    """Opt-in R12 allocation: use only this fresh frozen confirmation's feedback.

    This screen controls proof spending. It does not certify bootstrap admission,
    private transfer or reward, even when it permits an exact public gate.
    """
    policy = state['spec'].get('confirmation_gate_policy')
    if not policy:
        return names, []
    entries = {e['name']: e for e in state['spec']['entries']}
    parent, shadow = policy['parent'], policy['shadow']
    assert entries[parent]['hashes'] == entries[shadow]['hashes']
    assert entries[parent]['control'] and entries[shadow]['control']
    blocks = list(range(1, state['spec']['screen_blocks'] + 1))
    assert len(blocks) == 4 and policy['min_improved_blocks'] == 3
    by = {(m['candidate'], m['round']): m for m in state['metrics']}
    summaries = {r['candidate']: r for r in state['summary']}
    selected, decisions = [], []
    for name in names:
        assert entries[name]['anchor'] == parent and not entries[name]['control']
        assert summaries[name]['control'] is False
        rel_parent = [by[name,b]['time']/by[parent,b]['time'] for b in blocks]
        rel_shadow = [by[name,b]['time']/by[shadow,b]['time'] for b in blocks]
        frontier = bool(summaries[name]['own_anchor']['on_frontier'])
        checks = {'fresh_mean_improves_parent': statistics.mean(rel_parent) < 1,
                  'fresh_mean_improves_shadow': statistics.mean(rel_shadow) < 1,
                  'at_least_three_blocks_improve_parent': sum(v < 1 for v in rel_parent) >= 3,
                  'at_least_three_blocks_improve_shadow': sum(v < 1 for v in rel_shadow) >= 3,
                  'current_declared_family_projection_on_frontier': frontier}
        permit = all(checks.values())
        if permit:
            selected.append(name)
        decisions.append({'candidate': name, 'run_id': state['run_id'], 'checks': checks,
                          'relative_to_parent': rel_parent, 'relative_to_shadow': rel_shadow,
                          'full_gate_allocated': permit,
                          'scope': 'Fresh four-block confirmation only. Discovery timings are excluded. Family projection is conditional; no private/admission/payment guarantee.'})
    return selected, decisions


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
            if any(f['name'] == name for f in state['failures']):
                continue
            print(f'MEASURE_BEGIN {block} {name}', flush=True)
            keep = (phase == 'screen' and block == 1 and spec.get('cpu_diagnostics', False)
                    and name in spec.get('cpu_diagnostic_candidates', entries))
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
            measure(block, screen_order(spec, block, list(entries)))
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
        if names is None and spec.get('gate_groups'):
            names, state['gate_selection'] = grouped_gates(state)
            save(state_path, state)
            print('GATE_SELECTION ' + json.dumps(state['gate_selection']), flush=True)
        if names is None:
            names = [r['candidate'] for r in state['summary'] if not r['control'] and r['candidate'] in state.get('selected', [])][:spec['gate_limit']]
        names, decisions = confirmation_gates(state, names)
        if decisions:
            state['gate_confirmation_decisions'] = decisions
            save(state_path, state)
            print('GATE_CONFIRMATION ' + json.dumps(decisions), flush=True)
        if spec.get('confirmation_share_gate_policy'):
            from round15_gate import share_confirmation_gates
            names, share_decisions = share_confirmation_gates(state, names, pages, scorer)
            state['gate_share_confirmation_decisions'] = share_decisions
            save(state_path, state)
            print('SHARE_GATE_CONFIRMATION ' + json.dumps(share_decisions), flush=True)
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
            if spec.get('retain_extracted_lean'):
                match = re.search(r'^workspace: (.+)$', log, re.M)
                if match:
                    work = Path(match[1].strip()).resolve()
                    assert work.parent == (upstream / 'data/verification-workspace').resolve()
                    extracted = output / ('extracted-' + name)
                    extracted.mkdir(exist_ok=True)
                    manifest = {}
                    for filename in ('Types.lean', 'Constants.lean', 'Funs.lean'):
                        path = work / 'lean/Slot' / filename
                        if path.is_file():
                            data = path.read_bytes()
                            assert len(data) <= 10_000_000
                            (extracted / filename).write_bytes(data)
                            manifest[filename] = {'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
                    save(extracted / 'manifest.json', {'scope': 'Actual official re-extraction text; not a proof verdict', 'files': manifest})
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
                synthetic_names = list(dict.fromkeys(['r3-432-fast3'] + spec.get('synthetic_reference_candidates', []) + selected))
                state['synthetic_validation'] = run_validation(config, paths, synthetic_names, output)
        research_inputs = spec.get('research_synthetic_candidates', [])
        if research_inputs:
            assert len(research_inputs) == len(set(research_inputs)) <= 3
            assert set(research_inputs) <= set(entries) and 'r3-432-fast3' not in research_inputs
            from round3_synthetic import run_validation
            synthetic_names = list(dict.fromkeys(['r3-432-fast3'] + spec.get('synthetic_reference_candidates', []) + research_inputs))
            research_reports = output / 'research-synthetic'
            research_reports.mkdir(exist_ok=True)
            state['research_synthetic_validation'] = run_validation(config, paths, synthetic_names, research_reports)
            state['research_synthetic_validation']['proof_status'] = 'NO_FULL_GATE_IMPLIED; finite data checks only'
        finish()
        if any(not v.get('accepted') for v in state['gates'].values()):
            raise SystemExit('A selected experimental gate rejected; evidence retained')
    else:
        raise ValueError(phase)
    subprocess.run(['git', 'diff', '--exit-code'], cwd=upstream, check=True)


if __name__ == '__main__':
    main()
