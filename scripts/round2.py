"""Four order blocks through the unchanged official paired measurement engine."""
from __future__ import annotations
import dataclasses
import hashlib
import json
import os
import statistics
from pathlib import Path
from bench import corpora
from bench.driver import Config, Keep, run
from bench.results import INCUMBENT


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true'
    assert os.environ.get('RUNNER_OS') == 'Linux'
    assert os.environ.get('GITHUB_REPOSITORY') == 'HuanHuanHuanFFF/Miner'
    upstream = Path(os.environ['DEFLATE_ROOT'])
    workspace = Path(os.environ['GITHUB_WORKSPACE'])
    reports = Path(os.environ['RUNNER_TEMP']) / 'deflate-reports'
    corpus = corpora.load(upstream / 'validator').by_name('corpus-stage1')
    assert corpus.public
    cpu = str(min(os.sched_getaffinity(0)))
    config = dataclasses.replace(Config.from_env(upstream / 'validator'), reps=11, warmup=1, cpus=cpu, keep=Keep.NEVER, bars=False)
    sources = {
        'template': upstream / 'miner/template/parse.rs',
        'submission-261': workspace / 'references/submission-261/parse.rs',
        'probe2': workspace / 'candidates/probe2/parse.rs',
    }
    gates = {}
    for name in ('bucket2', 'probe3', 'probe2-nice16', 'probe2-nice64'):
        report = reports / (name + '-gate.json')
        gates[name] = report.exists() and json.loads(report.read_text())['accepted']
        if gates[name]:
            sources[name] = workspace / 'candidates' / name / 'parse.rs'
    names = list(sources)
    middle = len(names) // 2
    orders = [names, list(reversed(names)), names[middle:] + names[:middle], list(reversed(names[middle:] + names[:middle]))]
    results = []
    evidence = {}
    for block, order in enumerate(orders, 1):
        for name in order:
            print(f'MEASURE_BEGIN round={block} candidate={name}', flush=True)
            measured = run(config, {name: sources[name]}, corpus).only()
            assert not measured.failures(name) + measured.failures(INCUMBENT)
            files = [f for f in measured.files if f.raw_bytes > 0]
            result = {
                'round': block, 'candidate': name,
                'balanced_time_ratio_public': statistics.mean(f.methods[name].total_s / f.methods[INCUMBENT].total_s for f in files),
                'mean_file_compression_pct_public': statistics.mean(100 * f.methods[name].output_bytes / f.raw_bytes for f in files),
                'raw_bytes': measured.totals(name).raw_bytes,
                'output_bytes': measured.totals(name).output_bytes,
                'parse_s': measured.totals(name).parse_s, 'total_s': measured.totals(name).total_s,
                'incumbent_total_s': measured.totals(INCUMBENT).total_s,
                'worst_spread': measured.worst_spread(), 'files': len(files),
                'source_sha256': hashlib.sha256(sources[name].read_bytes()).hexdigest(),
            }
            results.append(result)
            evidence[block, name] = measured
            print('MEASUREMENT ' + json.dumps(result, allow_nan=False), flush=True)
            for record in measured.raw_records:
                print(f'RAW_EVIDENCE {block} {name} ' + json.dumps(record, allow_nan=False), flush=True)
            print(f'MEASURE_END round={block} candidate={name}', flush=True)
    for block in range(1, 5):
        for name in sources:
            control = evidence[1, name]
            tested = evidence[block, name]
            for a, b in zip(control.files, tested.files, strict=True):
                assert a.sha256 == b.sha256
                for method in (name, INCUMBENT):
                    assert a.methods[method].output_sha256 == b.methods[method].output_sha256
                    assert a.methods[method].tokens_sha256 == b.methods[method].tokens_sha256
        if 'bucket2' in sources:
            for a, b in zip(evidence[block, 'probe2'].files, evidence[block, 'bucket2'].files, strict=True):
                assert a.sha256 == b.sha256
                assert a.methods['probe2'].output_sha256 == b.methods['bucket2'].output_sha256
                assert a.methods['probe2'].tokens_sha256 == b.methods['bucket2'].tokens_sha256
    output = {
        'status': 'measured accepted candidates only',
        'scope': 'public stage1; no stage2, ranking, admission or reward prediction',
        'gates': gates, 'cpu_affinity': cpu, 'warmup_rounds': 1, 'measured_rounds': 11,
        'experiment_rounds': 4, 'orders': orders,
        'metrics': 'equal-file mean of ratios of median parser+encoder times; equal-file mean size percentages',
        'results': results,
    }
    (reports / 'comparison.json').write_text(json.dumps(output, indent=2, allow_nan=False) + '\n')
    print('COMPARISON ' + json.dumps(output, allow_nan=False), flush=True)


if __name__ == '__main__':
    main()
