"""Recompute four-block stage1 results from raw CI records; no toolchain needed.

Usage: python scripts/analyze-round2.py evidence/round2/ci.log
The bootstrap describes these public files on this runner; it is not official
admission, a random-runner confidence interval, or a private-stage2 prediction.
"""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import random
import re
import statistics
import sys


def total(method):
    assert method['deterministic'] and not method['errors']
    reps = [r for r in method['reps'] if r['phase'] == 'measured']
    assert len(reps) == 11 and all(r['total_s'] > 0 for r in reps)
    return statistics.median(r['total_s'] for r in reps)


def analyze(log):
    records, reported, gates = {}, {}, {}
    research = comparison = None
    for line in log.read_text(encoding='utf-8-sig').splitlines():
        match = re.search(r'RAW_EVIDENCE (\d+) (\S+) (\{.*\})$', line)
        if match:
            records.setdefault((int(match[1]), match[2]), []).append(json.loads(match[3]))
        match = re.search(r'MEASUREMENT (\{.*\})$', line)
        if match:
            value = json.loads(match[1]); reported[value['round'], value['candidate']] = value
        match = re.search(r'RESEARCH (\{.*\})$', line)
        if match:
            research = json.loads(match[1])
        match = re.search(r'COMPARISON (\{.*\})$', line)
        if match:
            comparison = json.loads(match[1])
    assert comparison and records.keys() == reported.keys()
    names = list(comparison['orders'][0])
    assert len(records) == 4 * len(names)
    metrics, files = {}, {}
    for key, raw in sorted(records.items()):
        block, name = key
        assert raw[0]['kind'] == 'meta' and raw[0]['corpus'] == 'corpus-stage1'
        rows = [r for r in raw if r['kind'] == 'file']
        assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
        files[key] = {r['file']: r for r in rows if r['raw_bytes'] > 0}
        ratios = {r['file']: total(r['methods'][name]) / total(r['methods']['incumbent']) for r in rows if r['raw_bytes'] > 0}
        time = statistics.mean(ratios.values())
        size = statistics.mean(100*r['methods'][name]['output_bytes']/r['raw_bytes'] for r in rows if r['raw_bytes'] > 0)
        assert abs(time - reported[key]['balanced_time_ratio_public']) < 1e-12
        assert abs(size - reported[key]['mean_file_compression_pct_public']) < 1e-12
        assert raw[0]['methods'][name]['source_sha256'] == reported[key]['source_sha256']
        metrics[key] = {'round': block, 'candidate': name, 'time': time, 'size_pct': size, 'per_file_time': ratios}
        (log.parent / f'round{block}-{name}.jsonl').write_text(''.join(json.dumps(r,allow_nan=False)+'\n' for r in raw), encoding='utf-8')
        for filename, r in files[key].items():
            baseline = files[1,name][filename]
            assert baseline['sha256'] == r['sha256']
            for method in (name, 'incumbent'):
                for field in ('output_bytes', 'output_sha256', 'tokens', 'tokens_sha256'):
                    assert baseline['methods'][method][field] == r['methods'][method][field]
    comparisons = []
    for name in names:
        if name in ('template', 'submission-261', 'probe2'):
            continue
        changes = []
        per_file_delta = []
        per_file = []
        for block in range(1,5):
            value, reference = metrics[block,name], metrics[block,'probe2']
            changes.append(100*(value['time']/reference['time']-1))
        for filename in files[1,name]:
            tested, reference = files[1,name][filename], files[1,'probe2'][filename]
            assert tested['sha256'] == reference['sha256']
            byte_delta = tested['methods'][name]['output_bytes'] - reference['methods']['probe2']['output_bytes']
            if name == 'bucket2':
                for field in ('output_bytes','output_sha256','tokens','tokens_sha256'):
                    assert tested['methods'][name][field] == reference['methods']['probe2'][field]
            deltas = [metrics[b,'probe2']['per_file_time'][filename] - metrics[b,name]['per_file_time'][filename] for b in range(1,5)]
            per_file_delta.append(statistics.mean(deltas))
            per_file.append({'file':filename,'output_byte_delta':byte_delta,'normalized_time_improvements_by_block':deltas})
        rng = random.Random(20261006)
        draws = sorted(statistics.mean(rng.choices(per_file_delta,k=len(per_file_delta))) for _ in range(2000))
        comparisons.append({
            'candidate':name,
            'time_change_pct_vs_probe2_by_block':changes,
            'size_change_pp_vs_probe2':metrics[1,name]['size_pct']-metrics[1,'probe2']['size_pct'],
            'files_smaller':sum(p['output_byte_delta']<0 for p in per_file),
            'files_larger':sum(p['output_byte_delta']>0 for p in per_file),
            'files_same':sum(p['output_byte_delta']==0 for p in per_file),
            'all_blocks_faster':all(c<0 for c in changes),
            'descriptive_file_bootstrap_95pct_improvement_interval':[draws[49],draws[1949]],
            'bootstrap_scope':'2000 file-resample draws of four-block mean normalized deltas; excludes runner/order uncertainty; not official admission',
            'files':per_file,
        })
    averages = {name:{'time':statistics.mean(metrics[b,name]['time'] for b in range(1,5)), 'size_pct':metrics[1,name]['size_pct']} for name in names}
    frontier = [name for name,a in averages.items() if not any(name!=other and b['time']<=a['time'] and b['size_pct']<=a['size_pct'] and (b['time']<a['time'] or b['size_pct']<a['size_pct']) for other,b in averages.items())]
    output = {
        'scope':'public stage1 only; empirical four-block local tradeoffs; no official rank/admission/reward claim',
        'metrics':[dict(v,per_file_time=v['per_file_time']) for v in metrics.values()],
        'averages':averages,'comparisons':comparisons,
        'observed_frontier_among_tested_versions':frontier,
        'bootstrap_caveat':'descriptive file bootstrap does not remove process drift or establish speed admission',
        'ci_log_sha256':hashlib.sha256(log.read_bytes()).hexdigest(),
    }
    (log.parent/'analysis.json').write_text(json.dumps(output,indent=2,allow_nan=False)+'\n',encoding='utf-8')
    (log.parent/'comparison.json').write_text(json.dumps(comparison,indent=2,allow_nan=False)+'\n',encoding='utf-8')
    if research:
        (log.parent/'research.json').write_text(json.dumps(research,indent=2,allow_nan=False)+'\n',encoding='utf-8')
    print(json.dumps({'averages':averages,'comparisons':[{k:v for k,v in c.items() if k!='files'} for c in comparisons], 'observed_frontier':frontier},indent=2))


if __name__ == '__main__':
    analyze(Path(sys.argv[1]))
