"""Bind the already proved exact source to the completed independent CI6 group.

Read-only validation of original evidence; writes a separate derived receipt.
It neither reruns the original gate nor grants a proof to the second source.
"""
from pathlib import Path
import datetime
import hashlib
import importlib.util
import json

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'AGENTS.md').is_file())
ROUND = ROOT / 'competitions/torchlean/candidates/r28-3h-20261030T171558Z'


def read(path, sha=None):
    data = path.read_bytes()
    if sha is not None:
        assert hashlib.sha256(data).hexdigest() == sha, path
    return json.loads(data)


def main():
    run = ROUND / 'evidence/41119180001'
    manifest = read(run / 'original-artifact-hashes.json')
    artifact = run / manifest['directory']
    plan = read(artifact / 'plan.json', '68c6633d07b021d4de3399cd1be3a5555101250292b3faf62b929d2e5559884d')
    meta = read(run / 'ci-run.json')
    summary = read(artifact / 'summary.json')
    audit = read(run / 'root-fixed-audit.json')
    terminal_spec = importlib.util.spec_from_file_location('retained_terminal_evidence', Path(__file__).with_name('terminal-evidence.py'))
    terminal = importlib.util.module_from_spec(terminal_spec)
    terminal_spec.loader.exec_module(terminal)
    assert (meta['status'] == 'completed' or terminal.verified(run, meta['headSha'])) and summary.get('finished_at_utc')
    assert int(meta['databaseId']) == int(audit['run']) == 41119180001
    assert audit['ci_metadata_status'] == meta['status'] and audit['ci_conclusion'] == meta['conclusion']
    assert summary['source_commit'] == meta['headSha'] == audit['source_commit'] == 'c68fb4c752cff8d937ef5960dcced2a0a64e3108'
    assert audit['outer_hashes']['status'] == audit['inner_hashes']['status'] == 'PASS'
    candidate = plan['candidates'][0]
    assert candidate['name'] == 'norm26-standard-confirmation'
    assert candidate['sample_role'] == 'FROZEN_INDEPENDENT_STANDARD_CONFIRMATION'
    prior = candidate['exact_prior_original_gate']
    old_summary = read(ROOT / prior['summary_path'], prior['summary_sha256'])
    verdict = read(ROOT / prior['verdict_path'], prior['verdict_sha256'])
    assert old_summary['source_commit'] == prior['source_commit']
    assert int(old_summary['run_id']) == prior['run']
    gate = next(g for g in old_summary['full_gates'] if g['source_sha256'] == candidate['sha256'])
    measured = next(g for g in summary['results'] if g['name'] == candidate['name'])
    assert candidate['sha256'] == prior['source_sha256'] == measured['source_sha256']
    assert candidate['declares_correct'] is True and candidate['full_gate'] is False
    assert measured['proof_state'] == 'DECLARED_CORRECT_TYPECHECKED_NO_FULL_ORIGINAL_REPLAY'
    assert measured['measurement_state'] == 'COMPLETE_NATIVE_ONLY_EXPLORATION'
    assert gate['exit_code'] == 0 and gate['verdict'] == verdict
    assert gate['name'] == verdict['submission'] == 'public36-norm26'
    assert verdict['passed'] and verdict['stage'] == 'axioms' and not verdict['exhausted']
    assert verdict['verifier_fingerprint'] == verdict['verifier_fingerprint_end'] == prior['verifier_fingerprint'] == summary['proof_identity'] == old_summary['proof_identity']
    assert summary['originals_unchanged'] is True
    assert summary['benchmark_identity'] == old_summary['benchmark_identity']
    assert plan['measurement_mode'] == 'standard'
    result = next(g for g in audit['results'] if g['candidate_sha256'] == candidate['sha256'])
    assert len(result['counts']) == len(plan['seeds']) == 2
    assert {c['seed'] for c in result['counts']} == set(plan['seeds'])
    assert all(c['paired_rows'] == c['checksum_pairs'] == 396 and c['ns_values'] == 792 for c in result['counts'])
    second = plan['candidates'][1]
    assert second['sha256'] == '29e71174da3a86aa6607cca050618256bf38b3aafadf4a617cd4c62497653eae'
    assert second['full_gate'] is False and second['declares_correct'] is False
    second_result = next(g for g in audit['results'] if g['candidate'] == second['name'])
    if 'candidate_proof' in second_result:
        assert second_result['candidate_proof'] == 'NOT_PROVED_NATIVE_ONLY'
    else:
        assert second_result['status'] in {'BUILD_FAILED_OR_NOT_RUN', 'MEASUREMENT_INCOMPLETE'}
    receipt = {
        'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'run': 41119180001,
        'source_commit': summary['source_commit'],
        'candidate_sha256': candidate['sha256'],
        'proof': 'VERIFIED_EXACT_SOURCE_PRIOR_ORIGINAL_ALL12_AXIOMS_GATE',
        'prior_gate': prior,
        'new_run_scope': 'Independent standard native confirmation; original gate not replayed in CI6',
        'whole_batch_complete_flag': summary['complete'],
        'whole_batch_error': summary.get('error'),
        'platform_status_preserved': meta['status'],
        'execution_reconciliation': read(run / 'execution-reconciliation.json') if meta['status'] != 'completed' else None,
        'acceptance_scope': 'Norm26 exact source and both full standard roots only; a terminal failure of the separate experiment does not transfer to or invalidate completed Norm26 samples',
        'fixed_audit_sha256': hashlib.sha256((run / 'root-fixed-audit.json').read_bytes()).hexdigest(),
        'standard_result': result,
        'second_source': {'sha256': plan['candidates'][1]['sha256'], 'proof': 'NOT_PROVED_NATIVE_ONLY_NO_TRANSFER'},
        'official_promotion': False,
        'comparison': 'INFERRED candidate time/current champion; current source private; no ARM measurement',
    }
    target = run / 'exact-source-proof-confirmation-binding.json'
    assert not target.exists(), 'Keep derived receipts immutable; choose a new output for a changed audit'
    target.write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(json.dumps({'receipt': str(target.relative_to(ROOT)), 'proof': receipt['proof'], 'ratio': result['candidate_time_over_current_champion_estimate']}))


if __name__ == '__main__':
    main()
