"""Independently reparse all eight retained old logs; no old driver/parser import."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
RUN = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40432634558'
RAW = RUN / 'download-884dd1b31e484d1cb852942081f1d275'
COST = RAW / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-runtime-cost1/runtime-cost'
PLAN = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-runtime-cost'


def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def rows(log, plan):
    expected = {c['name']: c for c in plan['cases']}
    assert len(expected) == 156
    found = {}
    for line in log.splitlines():
        m = re.fullmatch(r'(\S+) (true|false) (\d+) (\d+)', line)
        if not m:
            continue
        name, timed, ns, checksum = m.groups()
        timed, ns, checksum = timed == 'true', int(ns), int(checksum)
        assert name in expected and name not in found
        assert timed == expected[name]['timed']
        assert ns > 0 if timed else ns == 0
        found[name] = {'timed': timed, 'ns': ns, 'checksum': checksum}
    assert set(found) == set(expected) and sum(c['timed'] for c in found.values()) == 152
    return found


def totals(data, plan):
    out = {op: sum(data[c['name']]['ns'] for c in plan['cases'] if c['timed'] and c['kernel'] == op)
           for op in ('add', 'mul', 'sum', 'bmm')}
    out['whole'] = sum(out.values())
    assert out['whole'] == sum(c['ns'] for c in data.values())
    return out


def main():
    inventory = json.loads((RUN / 'original-artifact-hashes.json').read_bytes())
    assert inventory['artifact']['workflow_run']['head_sha'] == '93fe24bf105ed11fd5e56f262adef82be9129b44'
    expected = inventory['files']
    source_relative = next(k for k in expected if '/inputs/f01-r19-dev-runtime-cost1/Kernel.lean' in k)
    source = RAW / source_relative
    assert sha(source) == expected[source_relative]['sha256'] == '74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
    assert source.stat().st_size == expected[source_relative]['bytes'] == 228187
    samples, blocks, bindings = [], [], []
    for seed in (1927003, 1927005):
        pp = PLAN / f'plan-{seed}.json'
        original_plan = str((COST / pp.name).relative_to(RAW)).replace('\\', '/')
        item = expected[original_plan]
        assert sha(pp) == item['sha256'] and pp.stat().st_size == item['bytes']
        plan = json.loads(pp.read_bytes())
        subset = []
        for i, variant in enumerate(('control', 'guarded', 'guarded', 'control')):
            p = COST / f'{seed}-{i}-{variant}.log'
            relative = p.relative_to(RAW).as_posix()
            item = expected[relative]
            assert sha(p) == item['sha256'] and p.stat().st_size == item['bytes']
            data = rows(p.read_text(), plan)
            subset.append(data)
            samples.append({'seed': seed, 'order': i, 'variant': variant, 'ns': totals(data, plan),
                            'log_sha256': sha(p), 'plan_sha256': sha(pp)})
            bindings.append({'path': str(p), **item})
        assert all(all(c['checksum'] == subset[0][name]['checksum'] for name, c in data.items()) for data in subset)
        for block, (ci, gi) in enumerate(((0, 1), (3, 2))):
            control, guarded = totals(subset[ci], plan), totals(subset[gi], plan)
            blocks.append({'seed': seed, 'block': block, 'control': control, 'guarded': guarded,
                           'ratios': {op: guarded[op] / control[op] for op in control},
                           'all156_checksums_match': True})
    result = {'run': 40432634558, 'source_sha256': '74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc',
              'scope': 'Independent parse of all eight original source-bound old logs. Same-run diagnostics, not formal gate or current candidate performance.',
              'logs_and_plans_against_original_archive_hashes': True, 'samples': samples, 'blocks': blocks,
              'exact_compiled_source_rehashed': {'path': str(source), **expected[source_relative]},
              'log_bindings': bindings, 'new_outlined_candidate': 'NOT_RUN'}
    (HERE / 'historical-old-cost-recheck.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps([{'seed': b['seed'], 'block': b['block'], 'mul': b['ratios']['mul'], 'whole': b['ratios']['whole']}
                      for b in blocks]))


if __name__ == '__main__':
    main()
