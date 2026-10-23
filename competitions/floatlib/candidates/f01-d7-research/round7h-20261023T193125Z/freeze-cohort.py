"""Freeze a clean R11 discovery and two unseen confirmation seeds."""
import argparse
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
D7 = HERE.parent


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--candidate', required=True)
    ap.add_argument('--discovery', type=int, required=True)
    ap.add_argument('--seed-a', type=int, required=True)
    ap.add_argument('--seed-b', type=int, required=True)
    ap.add_argument('--diagnostic-only', action='store_true')
    a = ap.parse_args()
    read = lambda p: json.loads(p.read_bytes())
    digest = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
    spec = importlib.util.spec_from_file_location('r11_cohort_guard', D7/'adoption-guard.py')
    g = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(g)
    state = read(ROOT/'competitions/floatlib/coordination/development-status.json')
    g.require(state['research_round']['id'] == 'R11-20261023T193125Z', 'Wrong active round')
    baseline = 'f01-r8-combined-result-guard'
    p = g.load_run(ROOT, D7, a.discovery, (a.candidate, baseline))
    names = [row['candidate'] for row in p['plan']['candidates']]
    g.require(p['run_conclusion'] == p['job_conclusion'] == 'success', 'Successful discovery required')
    g.require(p['kernel_hashes'][baseline] == read(HERE/'selection-policy.json')['baseline']['sha256'], 'Wrong baseline')
    g.require(p['plan']['selection_policy'] == g.SELECTION_POLICY, 'Changed discovery policy')
    g.require(p['plan'].get('sample_role') == 'DISCOVERY', 'A clean discovery role is required')
    g.require(not p['codegen_present'] and not p['plan'].get('profile_parent') and not p['plan'].get('profile_current'), 'Discovery observers present')
    for n in (a.candidate, baseline):
        v = p['verdicts'][n]
        g.require(v.get('passed') is True and v.get('stage') == 'score' and len(v.get('rounds', [])) == 25, 'Full original discovery required')
        g.require(v['seed'] == p['seed'] == p['plan']['seed'], 'Discovery seed mismatch')
        source = ROOT/'competitions/floatlib/candidates'/n/'Kernel.lean'
        g.require(digest(source) == p['kernel_hashes'][n], 'Working source differs from discovery')
    screen_path = HERE/f'result-{p["seed"]}-{a.candidate}-vs-{baseline}.json'
    screen = read(screen_path)
    g.require(screen['run'] == a.discovery and screen['sha256'] == p['kernel_hashes'][a.candidate] and screen['evidence'] == p['evidence'], 'Discovery screen identity differs')
    if not a.diagnostic_only:
        g.require(screen['local_discovery_screen_passed'] is True, 'No qualifying discovery; use diagnostic-only')
    used = set()
    for path in (ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs').glob('dispatch-*/dispatch.json'):
        entry = read(path)
        if entry.get('state') in ('RUN_IDENTIFIED', 'DISPATCH_SENT_NO_AUTOMATIC_RETRY'):
            used.add(int(entry['inputs']['seed']))
    g.require(len({p['seed'], a.seed_a, a.seed_b}) == 3 and min(a.seed_a, a.seed_b) > 0, 'Distinct positive seeds required')
    g.require(not {a.seed_a, a.seed_b}.intersection(used), 'Holdout seed already dispatched')
    for seed in (a.seed_a, a.seed_b):
        g.require(not (HERE/f'plan-{seed}.json').exists(), 'Holdout already prepared')
    binding_spec = importlib.util.spec_from_file_location('r11_freeze_execution', HERE/'execution-binding.py')
    binding = importlib.util.module_from_spec(binding_spec)
    binding_spec.loader.exec_module(binding)
    execution = binding.snapshot(ROOT)
    binding.verify_run({'execution_files': execution}, p, g, ROOT)
    files = binding.required_local_paths(ROOT, HERE) + [ROOT/n for n in binding.EXECUTION_FILES]
    estimator_spec = importlib.util.spec_from_file_location('r11_freeze_estimator', ROOT/'competitions/floatlib/scripts/estimate_champion_time.py')
    estimator = importlib.util.module_from_spec(estimator_spec)
    estimator_spec.loader.exec_module(estimator)
    files += [Path(estimator.DEFAULT_ANCHOR), screen_path]
    for n in names:
        files += [ROOT/'competitions/floatlib/candidates'/n/s for s in ('Kernel.lean', 'manifest.json')]
    v = p['verdicts'][baseline]
    freeze = {'schema_version': 1, 'round': 'R11-20261023T193125Z',
              'candidate': {'name': a.candidate, 'sha256': p['kernel_hashes'][a.candidate]},
              'baseline': {'name': baseline, 'sha256': p['kernel_hashes'][baseline]},
              'groups': {'D': {'seed': p['seed'], 'run': a.discovery, 'job': p['job_id']}, 'A': {'seed': a.seed_a}, 'B': {'seed': a.seed_b}},
              'candidate_orders': {'D': names, 'A': list(reversed(names)), 'B': names[1:]+names[:1]},
              'required_groups': 3, 'selection_policy': g.SELECTION_POLICY,
              'suite_sha256': g.SUITE_SHA, 'generator_sha256': g.GENERATOR_SHA,
              'reference': {k: v[k] for k in ('incumbent_sha256', 'champion_sha256')},
              'frozen_at_utc': datetime.now(timezone.utc).isoformat(),
              'holdouts_unseen_before_freeze': True, 'diagnostic_only': a.diagnostic_only,
              'discovery_evidence': p['evidence'], 'discovery_screen': screen,
              'execution_files': execution,
              'files': {path.relative_to(ROOT).as_posix(): {'sha256': digest(path)} for path in files}}
    destination = HERE/'cohort-freeze.json'
    g.require(not destination.exists() and not (HERE/'cohort-freeze.sha256').exists(), 'Cohort already frozen')
    with destination.open('x', encoding='utf-8', newline='\n') as out:
        out.write(json.dumps(freeze, ensure_ascii=False, indent=2)+'\n')
    with (HERE/'cohort-freeze.sha256').open('x', encoding='ascii') as out:
        out.write(digest(destination)+'\n')
    print(json.dumps({'sha256': digest(destination), 'groups': freeze['groups'], 'diagnostic_only': a.diagnostic_only}))


if __name__ == '__main__':
    main()
