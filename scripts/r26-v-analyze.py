"""Describe endpoint CPU observations; never score or infer a migration cause."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter, defaultdict
import argparse
import hashlib
import importlib
import json
import statistics

ROOT = Path(__file__).resolve().parents[1]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def dist(values):
    median = statistics.median(values)
    return {'count': len(values), 'minimum_s': min(values), 'median_s': median,
            'maximum_s': max(values), 'range_over_median_pct': 100 * (max(values)-min(values))/median}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('folder', type=Path)
    ap.add_argument('--output', required=True, type=Path)
    args = ap.parse_args()
    folder = args.folder.resolve()
    assert folder.is_relative_to((ROOT/'evidence/round26').resolve())
    assert not args.output.exists()
    receipt = json.loads((folder/'receipt.json').read_bytes())
    assert receipt['status'] == 'measurement_verification' and receipt['completion'] == 'COMPLETE'
    assert receipt['pins_before'] == receipt['pins_after'] and len(receipt['processes']) == 2
    for name, expected in receipt['artifacts'].items():
        assert sha(folder/name) == expected, name
    validator = importlib.import_module('r26-v-call-cpu')
    groups = defaultdict(list)
    processes = []
    cgroups = defaultdict(set)
    for item in receipt['processes']:
        number = item['number']
        trace = json.loads((folder/f'process{number}.call-cpu.json').read_bytes())
        raw = [json.loads(s) for s in (folder/f'process{number}.raw.jsonl').read_text().splitlines()]
        observer = json.loads((folder/f'process{number}.observer.json').read_bytes())
        validator.verify_trace(trace, raw)
        assert item['engine_identity']['exe_sha256_via_proc'] == receipt['scratch_engine_sha256']
        assert {n: raw[0]['methods'][n]['lib_sha256'] for n in trace['methods']} == receipt['dso_sha256']
        pid = item['engine_identity']['process']['pid']
        start = item['engine_identity']['process']['starttime_ticks']
        observed = []
        for sample in observer['samples']:
            for engine in sample['engines']:
                assert (engine['pid'], engine['starttime_ticks']) == (pid, start)
                observed.append(engine)
                for path, value in engine.get('cgroup_ancestor_files', {}).items():
                    cgroups[(number, path)].add(json.dumps(value, sort_keys=True))
        assert observed
        measured = [e for e in trace['events'] if e['context']['phase'] == 'measured']
        endpoint_counts = Counter((e['cpu_before'], e['cpu_after']) for e in measured)
        for event in measured:
            ctx = event['context']
            name = trace['files'][ctx['file']]
            method = trace['methods'][ctx['method']]
            pair = (event['cpu_before'], event['cpu_after'])
            assert event['original_elapsed_s'] > 0
            assert (event['after_mono_ns']-event['before_mono_ns'])/1e9 + 1e-7 >= event['original_elapsed_s']
            groups[(number, name, method, event['stage'], pair)].append(event['original_elapsed_s'])
        processes.append({'number': number, 'engine_pid': pid, 'engine_starttime_ticks': start,
            'cpu_model': raw[0]['cpu_model'], 'measured_stage_calls': len(measured),
            'measured_unknown_cpu_calls': sum(v for pair, v in endpoint_counts.items() if min(pair) < 0),
            'measured_different_endpoint_cpu_calls': sum(v for pair, v in endpoint_counts.items() if min(pair) >= 0 and pair[0] != pair[1]),
            'endpoint_pair_counts': [{'before': a, 'after': b, 'calls': n} for (a, b), n in sorted(endpoint_counts.items())],
            'external_samples': len(observed), 'last_executed_cpu_values': sorted({e['sampled_cpu'] for e in observed}),
            'effective_affinity_observations': [json.loads(s) for s in sorted({json.dumps(e['effective_affinity']) for e in observed})],
            'monitor': {k: v for k, v in observer.items() if k.startswith('monitor_')},
            'raw_jsonl_sha256': sha(folder/f'process{number}.raw.jsonl'),
            'endpoint_trace_sha256': sha(folder/f'process{number}.call-cpu.json'),
            'observer_sha256': sha(folder/f'process{number}.observer.json')})
    grouped = [{'process': p, 'file': f, 'method': m, 'stage': s,
                'endpoint_cpus': list(pair), 'seconds_in_original_timer': values, **dist(values)}
               for (p, f, m, s, pair), values in sorted(groups.items())]
    cross = []
    for (p, f, m, s, pair), a in sorted(groups.items()):
        if p != 1 or min(pair) < 0 or pair[0] != pair[1]:
            continue
        b = groups.get((2, f, m, s, pair))
        if b is None:
            continue
        cross.append({'file': f, 'method': m, 'stage': s, 'matching_endpoint_cpu': pair[0],
            'process1': dist(a), 'process2': dist(b),
            'process2_median_change_pct': 100*(statistics.median(b)/statistics.median(a)-1),
            'observed_ranges_nonoverlapping': max(a) < min(b) or max(b) < min(a),
            'sparse_group': min(len(a), len(b)) < 3})
    result = {'status': 'VERIFIED_ENDPOINT_TELEMETRY_DESCRIPTIVE_DIAGNOSTIC_ONLY',
        'generated_utc': datetime.now(timezone.utc).isoformat(),
        'run_id': receipt['run_id'], 'git_sha': receipt['git_sha'],
        'receipt_sha256': sha(folder/'receipt.json'), 'scratch_engine_sha256': receipt['scratch_engine_sha256'],
        'original_engine_sha256': receipt['original_engine_sha256'], 'dso_sha256': receipt['dso_sha256'],
        'processes': processes, 'stratified_distributions': grouped,
        'same_endpoint_cross_process_comparisons': cross,
        'cgroup_ancestor_observations': [{'process': p, 'path': path, 'values': [json.loads(v) for v in sorted(values)]}
                                         for (p, path), values in sorted(cgroups.items())],
        'summary': {'strata': len(grouped), 'matching_same_endpoint_cross_process_strata': len(cross),
            'nonoverlapping_observed_ranges': sum(x['observed_ranges_nonoverlapping'] for x in cross),
            'nonoverlapping_with_at_least_three_per_process': sum(x['observed_ranges_nonoverlapping'] and not x['sparse_group'] for x in cross)},
        'limits': [
            'Endpoint identity is an observation, not continuous CPU placement. Equal endpoints cannot exclude intermediate migration; different endpoints cannot locate it inside original timers.',
            'Groups retain file/method/stage/process. CPU labels perfectly confounded with process cannot separate CPU and process effects.',
            'Min/max interval separation is descriptive and sample-size-dependent, not a significance test or probability.',
            'Scratch instrumentation and outside-timer observation can affect layout/cache/scheduling; no original timing is corrected.',
            'Controller ancestors and external CPU samples apply only to these new exact processes, not historical A19.',
            'No original-protocol candidate sample, score, gate, formal admission or payout is generated.']}
    args.output.write_bytes((json.dumps(result, indent=2)+'\n').encode())
    print(json.dumps({'run_id': result['run_id'], 'processes': processes, 'summary': result['summary']}, indent=2))


if __name__ == '__main__':
    main()
