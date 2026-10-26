"""Freeze a clean R16 discovery and two unseen confirmation seeds."""
import argparse
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
D7 = HERE.parent
CONTROL = 'f01-r8-combined-result-guard'
CONTROL_SHA = '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'


def first_dispatched_clean_seed(candidate, source_sha):
    """A later favorable input cannot replace this source's first clean D."""
    seeds = {}
    for path in (ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs').glob('dispatch-*/dispatch.json'):
        row=json.loads(path.read_bytes())
        if row.get('state') in ('RUN_IDENTIFIED','DISPATCH_SENT_NO_AUTOMATIC_RETRY'):
            seeds[int(row['inputs']['seed'])]=row
    possible=[]
    for path in HERE.glob('plan-*.json'):
        plan=json.loads(path.read_bytes());seed=plan['seed']
        if seed not in seeds or plan.get('sample_role')!='DISCOVERY':continue
        if plan.get('profile_current') or plan.get('profile_parent') or any(x.get('capture_codegen') for x in plan['candidates']):continue
        if not any(x['candidate']==candidate and x['sha256']==source_sha for x in plan['candidates']):continue
        frozen=json.loads((HERE/f'freeze-{seed}.json').read_bytes())
        possible.append((frozen['recorded_at_utc'],seed,seeds[seed].get('run',{}).get('databaseId')))
    if not possible:raise ValueError('No dispatched clean source discovery')
    return min(possible)[1:]


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
    spec = importlib.util.spec_from_file_location('r19_cohort_guard', HERE/'adoption-guard.py')
    g = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(g)
    state = read(ROOT/'competitions/floatlib/coordination/development-status.json')
    g.require(state['research_round']['id'] == 'R19-20261026T194639Z', 'Wrong active round')
    baseline = 'f01-r15-dev-packed-b2-1'
    p = g.load_run(ROOT, D7, a.discovery, (a.candidate, baseline))
    if not a.diagnostic_only:
        first_seed, first_run=first_dispatched_clean_seed(a.candidate,p['kernel_hashes'][a.candidate])
        g.require((p['seed'],a.discovery)==(first_seed,first_run),'Use the exact source first clean D; do not replace it with a later favorable input')
    control=g.load_run(ROOT,D7,a.discovery,(a.candidate,baseline,CONTROL))
    g.require(control['kernel_hashes'][CONTROL]==CONTROL_SHA,'Wrong frozen estimator control41')
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
    binding_spec = importlib.util.spec_from_file_location('r19_freeze_execution', HERE/'execution-binding.py')
    binding = importlib.util.module_from_spec(binding_spec)
    binding_spec.loader.exec_module(binding)
    execution = binding.snapshot(ROOT)
    binding.verify_run({'execution_files': execution}, p, g, ROOT)
    files = binding.required_local_paths(ROOT, HERE) + [ROOT/n for n in binding.EXECUTION_FILES]
    estimator_spec = importlib.util.spec_from_file_location('r19_freeze_estimator', ROOT/'competitions/floatlib/scripts/estimate_champion_time.py')
    estimator = importlib.util.module_from_spec(estimator_spec)
    estimator_spec.loader.exec_module(estimator)
    files += [Path(estimator.DEFAULT_ANCHOR), screen_path]
    vs=importlib.util.spec_from_file_location('r19_model_binding',HERE/'verify-three-groups.py')
    verifier=importlib.util.module_from_spec(vs);vs.loader.exec_module(verifier)
    retained_model=verifier.retained_model_identity(ROOT)
    g.require(digest(ROOT/retained_model['model_path'])==retained_model['sha256'], 'Retained numeric model changed before cohort freeze')
    for n in names:
        files += [ROOT/'competitions/floatlib/candidates'/n/s for s in ('Kernel.lean', 'manifest.json')]
    v = p['verdicts'][baseline]
    freeze = {'schema_version': 1, 'round': 'R19-20261026T194639Z',
              'candidate': {'name': a.candidate, 'sha256': p['kernel_hashes'][a.candidate]},
              'baseline': {'name': baseline, 'sha256': p['kernel_hashes'][baseline]},
              'estimator_control': {'name': CONTROL, 'sha256': CONTROL_SHA},
              'retained_model': retained_model,
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
