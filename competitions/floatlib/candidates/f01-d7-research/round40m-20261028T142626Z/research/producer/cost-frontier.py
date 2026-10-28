"""Reanalyse frozen R22 discovery rows; no benchmark or fitting is performed."""
from pathlib import Path
import hashlib, json
from collections import defaultdict

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
REL = 'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs/40611570030/download-032e40387a464ca39810735e751bed51/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-indexed8-cost1/runtime-cost'
BASE = ROOT / REL
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
source = json.loads((BASE / 'result.json').read_text(encoding='utf-8'))
assert sha(BASE / 'result.json') == '126d3162a4dea70630b307e6d50a35d7d2a15615baa7042b8ab763a5334b2340'
rows, groups = [], []
inputs = {'result.json': sha(BASE / 'result.json')}
for seed in (2220001, 2220003):
    run = next(r for r in source['runs'] if r['seed'] == seed and r['order'] == 4)
    plan = json.loads(run['environment']['BENCH_PLAN'])
    cases = {c['name']: c for c in plan['cases']}
    for block, (ci, vi) in enumerate(((4, 5), (7, 6))):
        cp = BASE / f'{seed}-{ci}-control-rows.json'
        vp = BASE / f'{seed}-{vi}-indexed8-rows.json'
        controls, variants = json.loads(cp.read_text()), json.loads(vp.read_text())
        inputs[cp.name], inputs[vp.name] = sha(cp), sha(vp)
        whole = sum(r['best_ns'] for r in controls.values() if r['timed'])
        variant_whole = sum(r['best_ns'] for r in variants.values() if r['timed'])
        old = next(pair for pair in source['pairs'] if pair['seed'] == seed)[f'indexed8_block_{block}']['whole']
        assert old['control_ns_sum'] == whole and old['variant_ns_sum'] == variant_whole
        stats = defaultdict(lambda: dict(control_ns=0, candidate_ns=0, cases=0))
        for name, ctl in controls.items():
            if not ctl['timed'] or cases[name]['kernel'] != 'bmm':
                continue
            case, variant = cases[name], variants[name]
            assert ctl['checksum'] == variant['checksum']
            eligible = case['n'] > 1 and case['m'] >= 4 and case['p'] >= 2
            category = 'eligible_four_row_shape' if eligible else 'shape_bypass'
            if eligible:
                category += '_with_tail' if case['m'] % 4 else '_no_tail'
            st = stats[category]
            st['control_ns'] += ctl['best_ns']
            st['candidate_ns'] += variant['best_ns']
            st['cases'] += 1
            rows.append(dict(seed=seed, block=block, name=name, shape=[case[k] for k in ('batch','m','n','p')],
                category=category, control_ns=ctl['best_ns'], candidate_ns=variant['best_ns'],
                ratio=variant['best_ns']/ctl['best_ns'], delta_ns=variant['best_ns']-ctl['best_ns']))
        for category, st in stats.items():
            groups.append(dict(seed=seed,block=block,category=category,**st,
                ratio=st['candidate_ns']/st['control_ns'],control_share_of_whole=st['control_ns']/whole))
receipt = BASE.parents[6] / 'original-artifact-hashes.json'
archived = json.loads(receipt.read_text(encoding='utf-8'))['files']
prefix = 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-indexed8-cost1/runtime-cost/'
for name, digest in inputs.items():
    assert archived[prefix + name]['sha256'] == digest
result = dict(scope='Historical two-seed discovery data only; not independent confirmation, admission, current leaderboard, or causal attribution.',
    source_sha256=source['source_sha256'], raw_receipts_sha256=inputs,
    original_artifact_manifest_sha256=sha(receipt), original_hashes_rechecked=True, original_whole_sums_reproduced=True,
    groups=groups, all_bmm_rows=rows,
    actual_guard_taken='UNKNOWN: dimensional eligibility is necessary, not proof of a dynamic path; underflow-zero may bypass.',
    decision='Do not tune new dispatch thresholds to these rows. Preserve full BMM lifecycle and confirm the proved public caller first; if it passes, distinguish preparation/allocation, tail rows, and arithmetic with a separately frozen cost experiment.')
(HERE / 'cost-frontier.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'groups':groups,'largest_slowdowns':sorted(rows,key=lambda r:r['delta_ns'],reverse=True)[:5]}))
