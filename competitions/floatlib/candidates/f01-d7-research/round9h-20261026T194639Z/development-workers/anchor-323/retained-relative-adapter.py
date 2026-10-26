"""R19 retained-B2 relative estimator adapter; standalone CLI is read-only."""
import argparse
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
ADAPTER = Path(__file__).resolve()
ROOT = next(p for p in ADAPTER.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
R19 = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z'
WORKER = R19 / 'development-workers/anchor-323'
ORIGINAL = ROOT / 'competitions/floatlib/scripts/estimate_champion_time.py'
CORE = WORKER / 'retained-relative-draft.py'
RETAINED = WORKER / 'retained-b2-model-ab3b.json'
CONTROL = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/freeze-anchor.json'
DEFAULT_ANCHOR = WORKER / 'reviewed323-anchor.json'
POLICY = R19 / 'selection-policy.json'
METHOD = 'FROZEN_RETAINED_B2_NORMALIZED_PAIRED_DELTAS'
PINNED = {
    ORIGINAL: '60476400919dff41f190c1779948f8eeca300753eb920c71ae659438f5bc3eb5',
    CORE: '916bf5b18b6c1a799ded2b1420e7bea49ac34ecbca18e99a45207ccc204d5524',
    RETAINED: 'ab3be355546023e1e8c88a98830018cf3a72f5b238de6b86dd7c0603b296bfda',
    CONTROL: '4a833683649369da031ebdbc8b3c2d37a8bee9d50b6fb5aaf734982faef064d7',
    DEFAULT_ANCHOR: 'da251287655b84f502434fb6da4f2d3ffaa53fb08ae01e0124bc9a4765afa965',
}
EXTRA_FROZEN_FILES = [ADAPTER, ORIGINAL, CORE, RETAINED, CONTROL, DEFAULT_ANCHOR, POLICY]


def _module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


def load_estimator():
    """Return the actual original module, with save/checked_record/validator intact.

    The adopter must call bind_frozen_cohort AFTER original verifier acceptance.
    This binding is an estimator boundary, not a substitute for selection proof.
    """
    for path, expected in PINNED.items():
        if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            raise ValueError('Pinned estimator input changed: ' + str(path))
    e = _module(ORIGINAL, 'r19_retained_relative_original')
    core = _module(CORE, 'r19_retained_relative_core')
    e.DEFAULT_ANCHOR = DEFAULT_ANCHOR
    e.EXTRA_FROZEN_FILES = list(EXTRA_FROZEN_FILES)
    retained, control, reviewed = e.load(RETAINED), e.load(CONTROL), e.load(DEFAULT_ANCHOR)
    e.validate_anchor(control); e.validate_anchor(reviewed)
    core.derive_retained_cells(retained, control)
    context = {}

    def rel(path):
        return Path(path).resolve().relative_to(ROOT).as_posix()

    def dependency_check():
        for path, expected in PINNED.items():
            e.require(e.sha(path) == expected, 'Pinned estimator input changed: ' + rel(path))
        policy = e.load(POLICY)
        declaration = policy.get('new_source_estimate_policy', {})
        e.require(declaration.get('method') == METHOD and declaration.get('base_model_sha256') == PINNED[RETAINED] and declaration.get('status') == 'DECLARED_BEFORE_FIRST_R19_FULL_DISCOVERY', 'Relative estimation policy not declared')
        e.require(policy['selection_policy']['headline_normalized_ratio_max'] == 0.97 and policy['selection_policy']['gain_p05_min_exclusive'] == 0.0 and policy['additional_inputs']['groups_total_target'] == 3, 'Selection thresholds changed')
        for item in reviewed['provenance'].get('frozen_files', []):
            e.require(e.sha(ROOT / item['path']) == item['sha256'], 'Historical anchor input changed')
        return policy

    def bound_check():
        e.require(context, 'bind_frozen_cohort required after successful original verifier')
        dependency_check()
        for path in e.EXTRA_FROZEN_FILES:
            key = rel(path)
            e.require(key in context['freeze']['files'] and e.sha(path) == context['freeze']['files'][key]['sha256'], 'Missing/changed extra estimator freeze: ' + key)

    def bind_frozen_cohort(freeze, runs):
        dependency_check()
        e.require(freeze.get('round') == 'R19-20261026T194639Z' and not freeze.get('diagnostic_only'), 'Wrong/diagnostic cohort')
        e.require(set(runs) == {'D', 'A', 'B'} and len(set(runs.values())) == 3 and all(type(v) is int and v > 0 for v in runs.values()), 'Exactly3 real D/A/B runs required')
        e.require(freeze['baseline']['sha256'] == core.B2 and freeze['retained_model']['source_sha256'] == core.B2 and freeze['retained_model']['sha256'] == PINNED[RETAINED], 'Wrong frozen retained source/model')
        e.require(freeze['candidate']['sha256'] != core.B2 and core.digest(freeze['candidate']['sha256']), 'New source cohort required')
        e.require(set(freeze['groups']) == {'D', 'A', 'B'} and len({g['seed'] for g in freeze['groups'].values()}) == 3, 'Missing/duplicate frozen seeds')
        for role, run in runs.items():
            group = freeze['groups'][role]
            e.require(type(group['seed']) is int and group['seed'] > 0 and ('run' not in group or group['run'] == run), 'Frozen run/seed mismatch')
        proposed = {'freeze': deepcopy(freeze), 'runs': dict(runs), 'roles': {run: role for role, run in runs.items()}}
        e.require(not context or context == proposed, 'Estimator cannot rebind to a different cohort')
        if not context:
            context.update(proposed)
        bound_check()
        return {'bound': True, 'runs': dict(runs), 'source_sha256': freeze['candidate']['sha256']}

    def authenticated(row, root):
        result = e.checked_record(row, root)
        role = context['roles'].get(result['run'])
        e.require(role is not None and result['seed'] == context['freeze']['groups'][role]['seed'], 'Gate outside bound cohort/seed')
        plan = e.load(Path(root) / result['runner_execution'] / 'requested-plan.json')
        e.require(not plan.get('profile_parent') and not plan.get('profile_current') and not any(c.get('capture_codegen') for c in plan['candidates']), 'Observer requested in gate plan')
        result.update(cohort_role=role, observer_free=True)
        return result

    def select_pairs(records, runs, candidate_sha256, anchor, root=ROOT):
        e.require(Path(root).resolve() == ROOT, 'Adapter is bound to its R19 repository root')
        bound_check(); e.validate_anchor(anchor)
        e.require(anchor == reviewed, 'Different reviewed323 anchor')
        e.require(candidate_sha256 == context['freeze']['candidate']['sha256'], 'Source differs from bound cohort')
        expected_runs = set(context['runs'].values())
        e.require(len(runs) == len(set(runs)) == 3 and set(runs) == expected_runs, 'Declared runs must be exact bound D/A/B')
        target = [r for r in records if r['kernel_sha256'] == candidate_sha256 and r.get('full_gate')]
        e.require(len(target) == 3 and {r['run'] for r in target} == expected_runs, 'Declared source gates omitted/duplicated/extra')
        pairs = []
        for run in runs:
            rows = [r for r in target if r['run'] == run]
            e.require(len(rows) == 1, 'Ambiguous source gate')
            c = authenticated(rows[0], root)
            e.require(c['candidate'] == context['freeze']['candidate']['name'], 'Bound candidate name changed')
            rows = [r for r in records if r.get('full_gate') and r['run'] == run and r['kernel_sha256'] == core.B2 and (Path(root) / r['verdict']).parent == (Path(root) / c['verdict']).parent]
            e.require(len(rows) == 1, 'Missing/ambiguous same-artifact B2 gate')
            b = authenticated(rows[0], root)
            core.normalized_relative_pair(c, b, candidate_sha256, control)
            pairs.append((c, b))
        return pairs

    def estimate_from_anchor(anchor, candidate_sha256, champion_digest, champion_suite, pairs=()):
        dependency_check(); e.validate_anchor(anchor)
        e.require(anchor == reviewed, 'Different reviewed323 anchor')
        if candidate_sha256 == core.B2:
            return core.estimate_relative_to_retained(retained, control, candidate_sha256, champion_digest, champion_suite, pairs)
        bound_check()
        e.require(candidate_sha256 == context['freeze']['candidate']['sha256'] and len(pairs) == 3 and {c['run'] for c, _ in pairs} == set(context['runs'].values()), 'Pairs differ from bound source/cohort')
        # Authenticate again: callers cannot edit selected class values in memory.
        checked = [(authenticated(c, ROOT), authenticated(b, ROOT)) for c, b in pairs]
        for c, b in checked:
            e.require(c['candidate'] == context['freeze']['candidate']['name'], 'Pair candidate name differs from freeze')
            e.require(Path(c['verdict']).parent == Path(b['verdict']).parent, 'Different pair artifact directories')
        model = core.estimate_relative_to_retained(retained, control, candidate_sha256, champion_digest, champion_suite, checked)
        model.update(relative_core_method=model['method'], method=METHOD)
        return model

    def official_identity():
        snapshot_path = e.DATA / 'current-official-snapshot.json'
        snapshot = e.load(snapshot_path)
        official = e.DATA / snapshot['directory']
        receipt = e.load(official / 'receipts.json')
        e.require(receipt['status'] == 'VERIFIED_SNAPSHOT' and receipt['compatible_frozen_protocol'], 'Invalid official snapshot')
        for name in ('champions', 'competition', 'champion-detail', 'champion-report'):
            item = receipt['responses'][name]; path = official / item['file']
            e.require(item['status'] == 200 and path.stat().st_size == item['bytes'] and e.sha(path) == item['sha256'], 'Official raw receipt mismatch')
        detail = e.load(official / 'champion-detail.raw')
        report = e.load(official / 'champion-report.raw')['report']
        report = json.loads(report) if isinstance(report, str) else report
        champion = next(c for c in e.load(official / 'champions.raw') if c['current'])
        e.require(detail['id'] == snapshot['champion'] == champion['submission'] == int(report['submission']) == retained['champion_submission'] == 323, 'Champion ID changed')
        e.require(report['mode'] == 'gate' and report['slot'] == 'full' and report['stage'] == 'score', 'Wrong official report boundary')
        e.require(detail['verification_current'] and detail['state'] == 'accepted' and detail['classes'] == report['classes'] and report['passed'] and report['reference_complete'] and not report['incumbent_failed'] and not report['exhausted'] and len(report['rounds']) == 25, 'Incomplete official champion')
        e.require(detail['digest'] == reviewed['champion_digest'] == retained['champion_digest'] and report['suite'] == reviewed['champion_suite'] == retained['champion_suite'], 'Champion digest/suite changed')
        e.require(report['champion_sha256'] == retained['champion_successor_chain']['from_digest'] and report['verifier_fingerprint'] == report['verifier_fingerprint_end'] == retained['champion_successor_chain']['verifier_fingerprint'], 'Official successor/verifier chain changed')
        return snapshot, official, receipt, detail, report, champion, e.load(official / 'competition.raw')

    def main(argv=None):
        parser = argparse.ArgumentParser(description=__doc__)
        parser.add_argument('--anchor', type=Path, default=DEFAULT_ANCHOR)
        parser.add_argument('--dry-run', action='store_true')
        args = parser.parse_args(argv)
        e.require(args.anchor.resolve() == DEFAULT_ANCHOR.resolve(), 'Only reviewed323 anchor accepted')
        policy = dependency_check()
        view_path, state_path = e.DATA / 'multiplier-comparison.json', ROOT / 'competitions/floatlib/coordination/development-status.json'
        view, state = e.load(view_path), e.load(state_path)
        e.require(e.sha(ROOT / state['kernel']) == view['kernel_sha256'] == state['kernel_sha256'], 'Current source mismatch')
        snapshot, official, receipt, detail, report, champion, competition = official_identity()
        if view['kernel_sha256'] == core.B2:
            e.require(view['candidate'] == Path(state['candidate']).name == retained['candidate'], 'Retained candidate name differs')
            e.require(e.sha(e.DATA / 'champion-time-estimate.json') == PINNED[RETAINED], 'Global retained model differs from frozen ab3b')
            model = estimate_from_anchor(reviewed, core.B2, detail['digest'], report['suite'])
            print(json.dumps({'identity_read_only': True, 'champion': 323, 'whole': model['whole'], 'method': model['method']}))
            return model
        bound_check()
        e.require(view['candidate'] == Path(state['candidate']).name == context['freeze']['candidate']['name'], 'Current candidate name differs from cohort')
        records_path = ROOT / view['public_results']
        monitored = [view_path, state_path, records_path, e.DATA / 'current-official-snapshot.json']
        before = {p: e.sha(p) for p in monitored}
        pairs = select_pairs(e.load(records_path)['records'], view['full_gate_runs'], view['kernel_sha256'], reviewed)
        model = estimate_from_anchor(reviewed, view['kernel_sha256'], detail['digest'], report['suite'], pairs)
        now = datetime.now(timezone.utc).isoformat()
        model.update(as_of_utc=now, candidate=view['candidate'], estimator_sha256=e.sha(ADAPTER),
            estimator_adapter=rel(ADAPTER), estimator_original_sha256=PINNED[ORIGINAL], estimator_core_sha256=PINNED[CORE],
            estimator_source_files=[{'path': rel(p), 'sha256': e.sha(p)} for p in e.EXTRA_FROZEN_FILES],
            anchor=rel(DEFAULT_ANCHOR), anchor_sha256=PINNED[DEFAULT_ANCHOR], anchor_payload_sha256=reviewed['payload_sha256'],
            retained_model=rel(RETAINED), retained_model_sha256=PINNED[RETAINED],
            retained_model_anchor_payload_sha256=retained['anchor_payload_sha256'],
            control_anchor=rel(CONTROL), control_anchor_sha256=PINNED[CONTROL], control_anchor_payload_sha256=control['payload_sha256'],
            frozen_control_public_results_sha256=retained['public_results_sha256'],
            public_results_sha256=e.sha(records_path), current_public_results_sha256=e.sha(records_path), champion_submission=323,
            champion_report=rel(official / 'champion-report.raw'), champion_report_sha256=e.sha(official / 'champion-report.raw'),
            current_champion_report=rel(official / 'champion-report.raw'), current_champion_report_sha256=e.sha(official / 'champion-report.raw'),
            official_receipts=rel(official / 'receipts.json'), official_receipts_sha256=e.sha(official / 'receipts.json'),
            estimate_policy=deepcopy(policy['new_source_estimate_policy']),
            frozen_cohort_runs=deepcopy(context['runs']), frozen_cohort_canonical_sha256=e.canonical_sha(context['freeze']))
        bound_check()
        e.require(all(e.sha(p) == h for p, h in before.items()) and e.sha(ROOT / state['kernel']) == model['kernel_sha256'], 'Inputs changed during estimation')
        output = {'champion': 323, 'method': model['method'], 'operations': model['operations'], 'whole': model['whole'], 'dry_run': args.dry_run}
        if args.dry_run:
            print(json.dumps(output)); return model
        model_path = e.DATA / 'champion-time-estimate.json'
        e.save(model_path, model)
        summary = {k: model[k] for k in ('status', 'method', 'candidate', 'kernel_sha256', 'champion_submission', 'champion_digest', 'operations', 'whole')}
        summary.update(evidence=rel(model_path), evidence_sha256=e.sha(model_path))
        view['champion'].update(submission=323, digest=detail['digest'], snapshot=competition['current_snapshot_id'],
            official_cumulative_speedup_vs_shipped=champion['speedup_vs_shipped'], official_speedup_basis=champion['speedup_basis'], receipts=rel(official / 'receipts.json'))
        view['champion_time_estimate'] = summary
        dashboard_policy = view['dashboard_policy']
        dashboard_policy.update(use_estimates_when_direct_unknown=True, allow_cross_suite_conversion=True,
            cross_suite_scope='INFERRED_FROZEN_RETAINED_B2_RELATIVE_DELTAS', estimator=rel(ADAPTER), updated_at_utc=now)
        view['as_of_utc'] = now
        e.save(view_path, view)
        state['current_multiplier_view'].update(official_champion=323, snapshot=competition['current_snapshot_id'],
            champion_time_estimate=summary, dashboard_policy=deepcopy(dashboard_policy),
            champion_official_historical_speedup_vs_shipped=champion['speedup_vs_shipped'], champion_official_speedup_basis=champion['speedup_basis'])
        state['current_champion_comparison'].update(submission=323, source_digest=detail['digest'], policy_snapshot=competition['current_snapshot_id'], queried_at_utc=snapshot['queried_at_utc'], method=METHOD, evidence=rel(model_path))
        state['updated_at_utc'] = now
        e.save(state_path, state)
        print(json.dumps(output))
        return model

    e.bind_frozen_cohort = bind_frozen_cohort
    e.select_pairs = select_pairs
    e.estimate_from_anchor = estimate_from_anchor
    e.main = main
    return e


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dry-run', action='store_true', required=True)
    parser.parse_args(argv)
    return load_estimator().main(['--dry-run'])


if __name__ == '__main__':
    main()
