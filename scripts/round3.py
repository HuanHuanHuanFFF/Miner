"""Public exploratory screen, interleaved refinement, then selected official gates.

Unverified screen candidates are explicitly labelled as such. The official
benchmark does round trips; only a later full gate can certify a candidate.
"""
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

TIME_FACTOR = 1.014402891250616
SIZE_FACTOR = 1.0070277985275755


def geometry(x, y, points):
    """Conditional coordinates, not an admission or payout prediction."""
    x *= TIME_FACTOR
    y *= SIZE_FACTOR
    dominates = [p for p in points if p['official_time'] <= x and p['official_size'] <= y]
    at_time = [p['official_size'] for p in points if p['official_time'] <= x]
    at_size = [p['official_time'] for p in points if p['official_size'] <= y]
    return {'calibrated_time': x, 'calibrated_size': y,
            'on_geometric_frontier': not dominates and x <= 10 and y <= 40,
            'dominating_ids': [p['id'] for p in dominates],
            'size_gap_pp': max(0, y - min(at_time)) if at_time else 0,
            'time_gap_pct': max(0, 100 * (x / min(at_size) - 1)) if at_size else 0}


def diagnostics(name, log, upstream):
    match = re.search(r'^workspace: (.+)$', log, re.M)
    if not match:
        return
    work = Path(match[1].strip()).resolve()
    assert work.parent == (upstream / 'data/verification-workspace').resolve()
    for path in sorted((work / 'logs').glob('*.log')):
        data = path.read_bytes()
        if b'error:' in data or b'timed out' in data:
            print(f'GATE_DIAGNOSTIC_BEGIN {name} {path.name}', flush=True)
            print(data.decode('utf-8', errors='replace'), flush=True)
            print(f'GATE_DIAGNOSTIC_END {name} {path.name}', flush=True)


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true'
    assert os.environ.get('RUNNER_OS') == 'Linux'
    assert os.environ.get('GITHUB_REPOSITORY') == 'HuanHuanHuanFFF/Miner'
    from bench import corpora
    from bench.driver import Config, Keep, run
    from bench.results import INCUMBENT
    from scoring.pareto import Point, pareto_front, local_global_improvement_space_log_weights

    workspace = Path(os.environ['GITHUB_WORKSPACE'])
    upstream = Path(os.environ['DEFLATE_ROOT'])
    reports = Path(os.environ['RUNNER_TEMP']) / 'deflate-reports'
    batch_name = os.environ['ROUND3_BATCH']
    assert batch_name in ('batch-a', 'batch-b', 'batch-c')
    batch = json.loads((workspace / 'evidence/round3' / (batch_name + '.json')).read_text())
    targets = json.loads((workspace / 'evidence/round3/frontier-targets.json').read_text())
    points = targets['points']
    corpus = corpora.load(upstream / 'validator').by_name('corpus-stage1')
    assert corpus.public
    cpu = str(min(os.sched_getaffinity(0)))
    config = dataclasses.replace(Config.from_env(upstream / 'validator'), reps=11, warmup=1, cpus=cpu, keep=Keep.NEVER, bars=False)
    paths = {n: workspace / 'candidates' / n for n in batch['controls']}
    for entry in batch['candidates']:
        p = (workspace / entry['path']).resolve()
        assert p.is_relative_to(workspace.resolve()) and entry['name'] not in paths
        for filename, expected in entry['hashes'].items():
            assert hashlib.sha256((p / filename).read_bytes()).hexdigest() == expected
        paths[entry['name']] = p
    candidates = [e['name'] for e in batch['candidates']]
    metrics, evidence, failures = [], {}, []

    def measure(block, order):
        for name in order:
            print(f'MEASURE_BEGIN round={block} candidate={name}', flush=True)
            try:
                measured = run(config, {name: paths[name] / 'parse.rs'}, corpus).only()
                errors = measured.failures(name) + measured.failures(INCUMBENT)
                assert not errors, errors
            except Exception as exc:
                failures.append({'candidate': name, 'round': block, 'error': str(exc)})
                print('SCREEN_FAILURE ' + json.dumps(failures[-1]), flush=True)
                if name in batch['controls']:
                    raise
                continue
            files = [f for f in measured.files if f.raw_bytes > 0]
            result = {'round': block, 'candidate': name,
                      'time': statistics.mean(f.methods[name].total_s / f.methods[INCUMBENT].total_s for f in files),
                      'size_pct': statistics.mean(100 * f.methods[name].output_bytes / f.raw_bytes for f in files),
                      'output_bytes': measured.totals(name).output_bytes,
                      'parse_s': measured.totals(name).parse_s, 'total_s': measured.totals(name).total_s,
                      'incumbent_total_s': measured.totals(INCUMBENT).total_s,
                      'worst_spread': measured.worst_spread(), 'files': len(files),
                      'source_sha256': hashlib.sha256((paths[name] / 'parse.rs').read_bytes()).hexdigest()}
            if name in evidence:
                for a, b in zip(evidence[name].files, measured.files, strict=True):
                    assert a.sha256 == b.sha256
                    for method in (name, INCUMBENT):
                        assert a.methods[method].output_sha256 == b.methods[method].output_sha256
                        assert a.methods[method].tokens_sha256 == b.methods[method].tokens_sha256
            evidence[name] = measured
            metrics.append(result)
            print('MEASUREMENT ' + json.dumps(result), flush=True)
            for raw in measured.raw_records:
                print(f'RAW_EVIDENCE {block} {name} ' + json.dumps(raw), flush=True)
            print(f'MEASURE_END round={block} candidate={name}', flush=True)

    def summarize(names):
        result = []
        for name in names:
            ms = [m for m in metrics if m['candidate'] == name]
            if len(ms) < batch['screen_blocks']:
                continue
            x = statistics.mean(m['time'] for m in ms)
            y = ms[0]['size_pct']
            g = geometry(x, y, points)
            pessimistic = geometry(max(m['time'] for m in ms) * 1.01, y, points)
            front = pareto_front([Point(p['id'], p['official_time'], p['official_size']) for p in points] + [Point('candidate', g['calibrated_time'], g['calibrated_size'])])
            weights = local_global_improvement_space_log_weights(front)
            result.append({'candidate': name, 'public_time_mean': x, 'public_time_range': [min(m['time'] for m in ms), max(m['time'] for m in ms)],
                           'public_size_pct': y, 'blocks': len(ms), **g,
                           'pessimistic_time_frontier': pessimistic['on_geometric_frontier'],
                           'hypothetical_geometry_weight': weights.get('candidate', 0) if g['on_geometric_frontier'] else 0})
        return sorted(result, key=lambda r: (-r['pessimistic_time_frontier'], -r['on_geometric_frontier'], -r['hypothetical_geometry_weight'], r['size_gap_pp'], r['time_gap_pct']))

    names = list(paths)
    for block in range(1, batch['screen_blocks'] + 1):
        measure(block, names if block % 2 else list(reversed(names)))
    screen = summarize(candidates)
    print('SCREEN_SUMMARY ' + json.dumps(screen), flush=True)
    shortlist = [r['candidate'] for r in screen[:batch['shortlist']]]
    for block in range(batch['screen_blocks'] + 1, batch['screen_blocks'] + batch['refine_blocks'] + 1):
        order = batch['controls'] + shortlist
        measure(block, order if block % 2 else list(reversed(order)))
    ranked = summarize(shortlist)
    gates = {}
    gate_names = batch.get('gate_candidates', [r['candidate'] for r in ranked[:batch['gate_limit']]])
    for name in gate_names:
        assert name in paths
        print(f'CANDIDATE_GATE_BEGIN {name}', flush=True)
        report = reports / (name + '-gate.json')
        # The official intake accepts exactly two files. Research manifests stay
        # outside the copied submission directory, and bytes must match the screen.
        gate_input = reports / ('input-' + name)
        gate_input.mkdir()
        for filename in ('parse.rs', 'Parse.lean'):
            shutil.copyfile(paths[name] / filename, gate_input / filename)
            assert (paths[name] / filename).read_bytes() == (gate_input / filename).read_bytes()
        cmd = [str(upstream / '.venv/bin/python'), 'validator/verifier/verify.py', str(gate_input), '--results', str(report), '--keep', 'always']
        process = subprocess.Popen(cmd, cwd=upstream, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        lines = []
        for line in process.stdout:
            lines.append(line)
            print(line, end='', flush=True)
        code = process.wait()
        log = ''.join(lines)
        (reports / (name + '-gate.log')).write_text(log)
        if report.exists():
            verdict = json.loads(report.read_text())
        else:
            verdict = {'accepted': False, 'origin': 'wrapper; official scoring report absent', 'gate_exit_code': code}
        gates[name] = verdict
        print('GATE_RESULT ' + json.dumps({'candidate': name, 'verdict': verdict}), flush=True)
        if code:
            diagnostics(name, log, upstream)
        print(f'CANDIDATE_GATE_END {name}', flush=True)
        if code == 2:
            raise RuntimeError('Official verifier infrastructure error')
    summary = {'scope': 'public stage1; speculative calibration; no stage2, admission or payout evidence',
               'batch': batch_name, 'snapshot': targets['context'], 'cpu_affinity': cpu,
               'screen': screen, 'refined': ranked, 'controls': summarize(batch['controls']),
               'gates': gates, 'failures': failures, 'metrics': metrics}
    (reports / 'round3-summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print('ROUND3_SUMMARY ' + json.dumps(summary), flush=True)
    subprocess.run(['git', 'diff', '--exit-code'], cwd=upstream, check=True)
    if any(not v.get('accepted') for v in gates.values()):
        raise SystemExit('Selected candidate gate rejected; inspect evidence')


if __name__ == '__main__':
    main()
