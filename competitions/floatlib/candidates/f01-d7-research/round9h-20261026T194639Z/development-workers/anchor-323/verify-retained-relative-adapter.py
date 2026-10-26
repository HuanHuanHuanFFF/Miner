"""Historical raw fixtures plus in-memory model/view/state integration checks."""
from contextlib import redirect_stdout
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import subprocess
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
ADAPTER = HERE / 'retained-relative-adapter.py'
sha = lambda p: hashlib.sha256(Path(p).read_bytes()).hexdigest()
read = lambda p: json.loads(Path(p).read_bytes())
encode = lambda v: (json.dumps(v, ensure_ascii=False, indent=2) + '\n').encode()


def require(ok, text):
    if not ok:
        raise ValueError(text)


def module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


def main():
    adapter = module(ADAPTER, 'r19_adapter_integration')
    e = adapter.load_estimator()
    globals_ = [e.DATA / 'champion-time-estimate.json', e.DATA / 'multiplier-comparison.json',
                ROOT / 'competitions/floatlib/coordination/development-status.json', e.DATA / 'current-official-snapshot.json']
    protected_paths = list(adapter.PINNED) + globals_ + [HERE / 'MANIFEST.json', HERE / 'retained-relative-MANIFEST.json']
    before = {str(p): sha(p) for p in protected_paths}
    require(Path(e.__file__).resolve() == adapter.ORIGINAL and e.checked_record.__globals__ is e.__dict__ and e.validate_anchor.__globals__ is e.__dict__ and e.save.__globals__ is e.__dict__, 'Not actual original module/functions')
    retained = read(adapter.RETAINED)
    reviewed = read(adapter.DEFAULT_ANCHOR)
    b_rows = [r for r in read(HERE / 'retained-b2-pair-records.json')['records'] if r['kernel_sha256'] == retained['kernel_sha256']]
    name = 'f01-d12-scalar-combined'
    source = 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    records = []
    for baseline in b_rows:
        verdict_path = (ROOT / baseline['verdict']).parent / (name + '-verdict.json')
        verdict = read(verdict_path)
        row = {k: deepcopy(baseline[k]) for k in ('run', 'official_commit', 'suite_sha256', 'seed', 'cell_work', 'verifier_fingerprint')}
        row.update(candidate=name, kernel_sha256=source, full_gate=True, verdict=verdict_path.relative_to(ROOT).as_posix(), verdict_sha256=sha(verdict_path), classes=verdict['classes'])
        records.extend((row, deepcopy(baseline)))
    runs = dict(zip(('D', 'A', 'B'), [r['run'] for r in b_rows]))
    seeds = {r['run']: r['seed'] for r in b_rows}

    def freeze_for(estimator):
        return {'schema_version': 1, 'round': 'R19-20261026T194639Z', 'diagnostic_only': False,
            'candidate': {'name': name, 'sha256': source}, 'baseline': {'name': retained['candidate'], 'sha256': retained['kernel_sha256']},
            'retained_model': {'source_sha256': retained['kernel_sha256'], 'sha256': adapter.PINNED[adapter.RETAINED]},
            'groups': {role: {'run': run, 'seed': seeds[run]} for role, run in runs.items()},
            'files': {p.relative_to(ROOT).as_posix(): {'sha256': sha(p)} for p in estimator.EXTRA_FROZEN_FILES}}

    def bound():
        estimator = adapter.load_estimator()
        freeze = freeze_for(estimator)
        estimator.bind_frozen_cohort(freeze, runs)
        return estimator, freeze

    rejections = []
    def expect(label, action):
        try:
            action()
        except (ValueError, KeyError, OSError) as exc:
            rejections.append({'case': label, 'reason': str(exc)})
        else:
            raise ValueError('Expected rejection missing: ' + label)

    expect('unbound_source', lambda: e.select_pairs(records, list(runs.values()), source, reviewed))
    bad_freeze = freeze_for(e); bad_freeze['files'].pop(adapter.CORE.relative_to(ROOT).as_posix())
    expect('missing_extra_freeze', lambda: e.bind_frozen_cohort(bad_freeze, runs))
    e, freeze = bound()
    pairs = e.select_pairs(records, list(runs.values()), source, reviewed)
    predicted = e.estimate_from_anchor(reviewed, source, retained['champion_digest'], retained['champion_suite'], pairs)
    historical = read(HERE / 'retained-relative-historical-model.json')
    for field in ('operations', 'whole', 'samples', 'cell_relative_delta_to_retained_median'):
        require(predicted[field] == historical[field], 'Adapter differs from pure historical result: ' + field)
    require(predicted['method'] == adapter.METHOD and predicted['relative_core_method'] == historical['method'], 'Policy/core method metadata mismatch')
    require({c['cohort_role'] for c, _ in pairs} == {'D', 'A', 'B'} and all(b['kernel_sha256'] == retained['kernel_sha256'] for _, b in pairs), 'Bound roles/baseline mismatch')
    expect('two_declared_groups', lambda: e.select_pairs(records, list(runs.values())[:2], source, reviewed))
    missing = records[2:]
    expect('missing_full_group', lambda: e.select_pairs(missing, list(runs.values()), source, reviewed))
    bad_gate = deepcopy(records); bad_gate[0]['full_gate'] = False
    expect('bad_gate', lambda: e.select_pairs(bad_gate, list(runs.values()), source, reviewed))
    extra = deepcopy(records); fourth = deepcopy(records[0]); fourth['run'] = 999999; extra.append(fourth)
    expect('undeclared_extra_source_gate', lambda: e.select_pairs(extra, list(runs.values()), source, reviewed))
    no_baseline = [r for r in records if not (r['run'] == runs['A'] and r['kernel_sha256'] == retained['kernel_sha256'])]
    expect('missing_same_artifact_B2', lambda: e.select_pairs(no_baseline, list(runs.values()), source, reviewed))
    bad = deepcopy(records); bad[0]['verdict_sha256'] = '0'*64
    expect('bad_raw_gate_hash', lambda: e.select_pairs(bad, list(runs.values()), source, reviewed))
    bad_pairs = deepcopy(pairs); bad_pairs[0][0]['classes']['add:dense']['submission_ns'] *= 2
    expect('edited_selected_classes_reauthenticated', lambda: e.estimate_from_anchor(reviewed, source, retained['champion_digest'], retained['champion_suite'], bad_pairs))
    old_load = e.load
    observer_plan = (ROOT / pairs[0][0]['runner_execution'] / 'requested-plan.json').resolve()
    def observer_load(path):
        value = old_load(path)
        if Path(path).resolve() == observer_plan:
            value['profile_current'] = True
        return value
    e.load = observer_load
    expect('requested_observer', lambda: e.select_pairs(records, list(runs.values()), source, reviewed))
    e.load = old_load
    raw_verdict = (ROOT / pairs[0][0]['verdict']).resolve()
    for case in ('not_passed', 'only24_rounds'):
        def incomplete_load(path, case=case):
            value = old_load(path)
            if Path(path).resolve() == raw_verdict:
                if case == 'not_passed':
                    value['passed'] = False
                else:
                    value['rounds'] = value['rounds'][:24]
            return value
        e.load = incomplete_load
        expect('raw_gate_' + case, lambda: e.select_pairs(records, list(runs.values()), source, reviewed))
    e.load = old_load
    different = deepcopy(freeze); different['groups']['A']['run'] += 1
    changed_runs = dict(runs); changed_runs['A'] += 1
    expect('different_cohort_rebind', lambda: e.bind_frozen_cohort(different, changed_runs))
    # CLI and module B2 paths never call save or read/re-fit the ten controls.
    saved_identity = []
    identity_e = adapter.load_estimator()
    identity_e.save = lambda *args: saved_identity.append(args)
    with redirect_stdout(io.StringIO()):
        identity = identity_e.main([])
    require(identity == retained and encode(identity) == adapter.RETAINED.read_bytes() and not saved_identity, 'B2 main lost strict read-only identity')
    refused = subprocess.run([sys.executable, '-B', str(ADAPTER)], capture_output=True, text=True)
    require(refused.returncode == 2 and '--dry-run' in refused.stderr, 'Standalone write CLI was not refused')

    def virtual_new_source(estimator):
        view_path, state_path = globals_[1], globals_[2]
        base_load, base_sha = estimator.load, estimator.sha
        view, state = base_load(view_path), base_load(state_path)
        kernel = ROOT / pairs[0][0]['runner_execution'] / 'inputs' / name / 'Kernel.lean'
        require(sha(kernel) == source, 'Historical candidate raw source differs')
        view.update(candidate=name, kernel_sha256=source, full_gate_runs=list(runs.values()))
        state.update(candidate='competitions/floatlib/candidates/' + name, kernel=kernel.relative_to(ROOT).as_posix(), kernel_sha256=source)
        index_path = ROOT / view['public_results']
        inputs = {view_path: view, state_path: state, index_path: {'records': records}}
        writes = {}
        def virtual_load(path):
            path = Path(path).resolve()
            return deepcopy(writes[path] if path in writes else inputs[path]) if path in writes or path in inputs else base_load(path)
        def virtual_sha(path):
            path = Path(path).resolve()
            return hashlib.sha256(encode(writes[path] if path in writes else inputs[path])).hexdigest() if path in writes or path in inputs else base_sha(path)
        estimator.load, estimator.sha = virtual_load, virtual_sha
        estimator.save = lambda path, value: writes.__setitem__(Path(path).resolve(), deepcopy(value))
        return inputs, writes

    unbound_e = adapter.load_estimator(); _, not_written = virtual_new_source(unbound_e)
    expect('new_source_main_unbound', lambda: unbound_e.main([]))
    require(not not_written, 'Unbound source attempted a save')
    writer, writer_freeze = bound()
    inputs, writes = virtual_new_source(writer)
    with redirect_stdout(io.StringIO()):
        result = writer.main(['--anchor', str(adapter.DEFAULT_ANCHOR)])
    require(set(writes) == set(globals_[:3]), 'Save interception did not capture exactly model/view/state')
    for field in ('operations', 'whole', 'samples', 'cell_relative_delta_to_retained_median', 'formula', 'method'):
        require(result[field] == predicted[field], 'Main changed relative math/formula/method: '+field)
    require(result['estimator_sha256'] == sha(ADAPTER) and result['estimator_core_sha256'] == adapter.PINNED[adapter.CORE] and result['kernel_sha256'] == source and result['candidate'] == name, 'Wrong code/source provenance')
    require(result['frozen_cohort_runs'] == runs and result['estimate_policy']['method'] == adapter.METHOD and 'cell_relative_delta_median' not in result, 'Stale C/41 metadata inherited')
    require(result['frozen_cohort_canonical_sha256'] == writer.canonical_sha(writer_freeze), 'Wrong canonical frozen cohort identity')
    require(result['anchor_payload_sha256'] == reviewed['payload_sha256'] and result['control_anchor_payload_sha256'] == retained['anchor_payload_sha256'], 'Reviewed/current and old control anchor payload identities confused')
    require(result['public_results_sha256'] == result['current_public_results_sha256'] and result['frozen_control_public_results_sha256'] == retained['public_results_sha256'], 'Current and frozen source index identities confused')
    require(result['as_of_utc'] != retained['as_of_utc'] and result['retained_model_sha256'] == adapter.PINNED[adapter.RETAINED], 'Stale time/base identity')
    for key in ('current_public_results_sha256', 'current_champion_report_sha256', 'official_receipts_sha256'):
        require(len(result[key]) == 64, 'Missing fresh evidence hash')
    for sample, frozen in zip(result['samples'], retained['samples']):
        require(sample['champion_projected_total_ns'] == frozen['champion_projected_total_ns'], 'Main recalibrated champion denominator')
    expected_model_hash = hashlib.sha256(encode(result)).hexdigest()
    for path in globals_[1:3]:
        summary = writes[path]['champion_time_estimate'] if path == globals_[1] else writes[path]['current_multiplier_view']['champion_time_estimate']
        require(summary['evidence_sha256'] == expected_model_hash and summary['method'] == adapter.METHOD and summary['kernel_sha256'] == source and summary['whole'] == result['whole'], 'View/state summary does not bind new exact model')
    # An adopter's failed Tx save must propagate; this emulates rollback in memory.
    failing, _ = bound(); _, partial = virtual_new_source(failing)
    def fail_save(path, value):
        if Path(path).resolve() == globals_[2]:
            raise OSError('SYNTHETIC_TX_STATE_WRITE_FAILURE')
        partial[Path(path).resolve()] = deepcopy(value)
    failing.save = fail_save
    with redirect_stdout(io.StringIO()):
        expect('save_failure_propagates_to_adopter', lambda: failing.main([]))
    require(len(partial) == 2, 'Expected two intercepted virtual writes before Tx failure')
    partial.clear()  # Emulated outer rollback, no physical files were ever written.
    require(before == {path: sha(path) for path in before}, 'Protected/global bytes changed during fixture checks')
    receipt = {'status': 'PASS', 'verified_at_utc': datetime.now(timezone.utc).isoformat(), 'adapter_sha256': sha(ADAPTER),
        'actual_original_module_returned': True, 'checked_record_validate_anchor_unchanged': True,
        'strict_B2_main_dict_and_serialized_identity': True, 'strict_B2_main_save_calls': 0,
        'standalone_without_dry_run_exit': refused.returncode, 'bound_historical_runs': runs,
        'historical_source_sha256': source, 'historical_fixture_contains_fresh_control41': False,
        'adapter_numeric_fields_equal_reviewed_pure_core': True, 'correct_new_method_formula_and_source_fingerprints': True,
        'save_interception_paths': [p.relative_to(ROOT).as_posix() for p in writes],
        'model_view_state_exact_evidence_hash': expected_model_hash,
        'new_method': result['method'], 'whole': result['whole'], 'rejections': rejections,
        'save_failure_propagates': True, 'rollback_scope': 'In-memory outer Tx emulation only; actual adopter integration remains mainD responsibility.',
        'protected_bytes_unchanged': before, 'extra_frozen_files': [p.relative_to(ROOT).as_posix() for p in writer.EXTRA_FROZEN_FILES],
        'scope': 'Historical raw-gate fixture and virtual model/view/state only. No actual new candidate selection or adoption; current R19 D result was not read. Original production verifier still retains its extra41 requirement.'}
    (HERE / 'retained-relative-adapter-fixture-records.json').write_bytes(encode({'scope': receipt['scope'], 'records': records}))
    (HERE / 'retained-relative-adapter-model-fixture.json').write_bytes(encode(result))
    (HERE / 'retained-relative-adapter-integration.json').write_bytes(encode(receipt))
    print(json.dumps({'status': 'PASS', 'adapter_sha256': sha(ADAPTER), 'new_method': result['method'], 'whole': result['whole'], 'strict_B2_identity': True, 'intercepted_saves': len(writes), 'negative_cases': len(rejections), 'global_bytes_unchanged': True}))


if __name__ == '__main__':
    main()
