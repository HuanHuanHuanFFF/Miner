from __future__ import annotations
import hashlib
import importlib.util
import json
import subprocess
import sys
import tempfile
from pathlib import Path
from unittest import mock

OWNER = Path(__file__).resolve().parent
REPO = OWNER.parents[6]
SOURCE = REPO / 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
CANDIDATES = REPO / 'competitions/floatlib/candidates'
KERNEL = CANDIDATES / 'f01-r24-dev-dot-cost1/Kernel.lean'
MANIFEST = CANDIDATES / 'f01-r24-dev-dot-cost1/manifest.json'
AUDIT_STAGE = REPO / 'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-dot-cost/audit-stage.py'
OUT = OWNER / 'test-results.json'

def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()

def check(condition: bool, message: str) -> None:
    if not condition:
        raise AssertionError(message)

def load_module_without_subprocess():
    spec = importlib.util.spec_from_file_location('timeout_review_ci_diagnostics', SOURCE)
    module = importlib.util.module_from_spec(spec)
    with mock.patch('subprocess.Popen', side_effect=AssertionError('import launched a subprocess')) as patched:
        spec.loader.exec_module(module)
    check(patched.call_count == 0, 'module import invoked subprocess.Popen')
    check(module.__name__ != '__main__', 'module unexpectedly imported as __main__')
    return module

class FakeProcess:
    instances = []
    def __init__(self, argv, **kwargs):
        self.argv = argv
        self.kwargs = kwargs
        self.wait_timeout = None
        type(self).instances.append(self)
    def wait(self, timeout=None):
        self.wait_timeout = timeout
        return 0

def run_main(module, temp_root: Path, label: str, name: str, compile_only: bool, verdict_seed=None):
    run_root = temp_root / label
    run_root.mkdir(parents=True, exist_ok=True)
    verdict = run_root / 'verdict.json'
    if verdict_seed is not None:
        verdict.write_text(json.dumps(verdict_seed), encoding='utf-8')
    argv = [str(SOURCE), '--upstream', str(run_root / 'upstream'), '--kernel', str(KERNEL),
            '--reports', str(run_root / 'reports'), '--name', name, '--verdict', str(verdict)]
    if compile_only:
        argv.append('--compile-only')
    with mock.patch.object(sys, 'argv', argv), mock.patch.object(module.subprocess, 'Popen', FakeProcess):
        rc = module.main()
    report = json.loads((run_root / 'reports/diagnostics' / name / 'index.json').read_text(encoding='utf-8'))
    return rc, FakeProcess.instances[-1].wait_timeout, report

def main():
    repo_resolved = REPO.resolve()
    owner_resolved = OWNER.resolve()
    check(owner_resolved.is_relative_to(repo_resolved), 'review directory resolves outside repository')
    module = load_module_without_subprocess()
    manifest = json.loads(MANIFEST.read_text(encoding='utf-8'))
    kernel_sha = sha(KERNEL)
    manifest_sha = sha(MANIFEST)
    check(manifest['candidate'] == 'f01-r24-dev-dot-cost1', 'unexpected candidate id')
    check(manifest['candidate_sha256'] == kernel_sha == '5bf2a8893b01a5ed44393e80065fbd91e9b3686133e9ddd5d4dfb633379d4d2a', 'candidate Kernel hash mismatch')
    check(manifest['diagnostic_only'] is True and manifest['validation_mode'] == 'statement-only' and manifest['diagnostic_timeout_seconds'] == 600, 'manifest gate fields changed')
    result = {'status': 'PASS', 'source': str(SOURCE), 'kernel': str(KERNEL), 'manifest': str(MANIFEST),
              'hashes': {'ci_diagnostics_sha256': sha(SOURCE), 'kernel_sha256': kernel_sha, 'manifest_sha256': manifest_sha},
              'checks': [], 'rejections': []}

    actual_timeout = module.r24_statement_replay_timeout('f01-r24-dev-dot-cost1', True, KERNEL, CANDIDATES)
    check(actual_timeout == 590, f'positive guard returned {actual_timeout!r}, expected 590')
    result['checks'].append({'name': 'actual_positive_manifest', 'pass': True, 'returned_seconds': actual_timeout})

    temp_holder = tempfile.TemporaryDirectory(prefix='r24-timeout-review-', dir=OWNER)
    temp = Path(temp_holder.name).resolve()
    check(temp.is_relative_to(owner_resolved), 'temporary fixture root resolves outside review directory')
    fixture_kernel = temp / 'fixture-kernel.lean'
    fixture_kernel.write_bytes(KERNEL.read_bytes())
    base = json.loads(json.dumps(manifest))
    negative_cases = {
        'wrong_kernel_sha': lambda m: m.update(candidate_sha256='0' * 64),
        'timeout_180': lambda m: m.update(diagnostic_timeout_seconds=180),
        'fullgate_mode': lambda m: m.update(validation_mode='fullgate'),
        'diagnostic_false': lambda m: m.update(diagnostic_only=False),
        'wrong_candidate_id': lambda m: m.update(candidate='f01-r24-other'),
    }
    for label, mutate in negative_cases.items():
        case_root = temp / label / 'candidates'
        candidate_dir = case_root / 'f01-r24-dev-dot-cost1'
        candidate_dir.mkdir(parents=True)
        request = json.loads(json.dumps(base))
        mutate(request)
        (candidate_dir / 'manifest.json').write_text(json.dumps(request), encoding='utf-8')
        returned = module.r24_statement_replay_timeout('f01-r24-dev-dot-cost1', True, fixture_kernel, case_root)
        check(returned is None, f'{label} unexpectedly authorized timeout {returned!r}')
        result['rejections'].append({'name': label, 'pass': True, 'returned': returned})

    missing_root = temp / 'missing' / 'candidates'
    (missing_root / 'f01-r24-dev-dot-cost1').mkdir(parents=True)
    check(module.r24_statement_replay_timeout('f01-r24-dev-dot-cost1', True, fixture_kernel, missing_root) is None, 'missing manifest accepted')
    result['rejections'].append({'name': 'missing_manifest', 'pass': True, 'returned': None})
    check(module.r24_statement_replay_timeout('f01-r24-dev-dot-cost1', False, KERNEL, CANDIDATES) is None, 'compile_only=False accepted')
    result['rejections'].append({'name': 'compile_only_false', 'pass': True, 'returned': None})
    check(module.r24_statement_replay_timeout('f01-r23-dev-dot-cost1', True, KERNEL, CANDIDATES) is None, 'non-R24 name accepted')
    result['rejections'].append({'name': 'non_r24_name', 'pass': True, 'returned': None})

    FakeProcess.instances.clear()
    r24_rc, r24_wait, r24_report = run_main(module, temp, 'actual-main-r24', 'f01-r24-dev-dot-cost1', True)
    check(r24_wait == 590, f'actual main passed timeout {r24_wait!r} to p.wait, expected 590')
    check(r24_report.get('r24_statement_timeout', {}).get('seconds') == 590, 'actual main report did not record the bounded R24 timeout')
    check(r24_rc == 1, f'mocked compile-only main returned {r24_rc}; expected diagnostic-missing failure because no child was run')
    result['checks'].append({'name': 'actual_main_wait_site_r24', 'pass': True, 'p_wait_timeout_seconds': r24_wait, 'mocked_main_return': r24_rc})

    old_rc, old_wait, _ = run_main(module, temp, 'actual-main-old-580', 'f01-r22-dev-runtime-cost1', True)
    check(old_wait == 580, f'older fixed stage wait changed: {old_wait!r}')
    check(old_rc == 1, 'mocked old compile-only path should retain missing-child diagnostic failure')
    result['checks'].append({'name': 'legacy_stage_timeout_unchanged', 'pass': True, 'p_wait_timeout_seconds': old_wait})

    suite_verdict = {'stage': 'statement'}
    suite_rc, suite_wait, suite_report = run_main(module, temp, 'actual-main-public-suite', 'f01-d7-public-suite', False, suite_verdict)
    check(suite_wait == 2400, f'public suite wait unexpectedly changed to {suite_wait!r}')
    check('r24_statement_timeout' not in suite_report, 'R24 timeout metadata leaked into suite run')
    check(suite_rc == 0, 'mocked public suite main failed unexpectedly')
    result['checks'].append({'name': 'public_suite_timeout_unchanged', 'pass': True, 'p_wait_timeout_seconds': suite_wait})

    audit_text = AUDIT_STAGE.read_text(encoding='utf-8')
    check(manifest['runtime_cost']['absolute_stage_seconds'] == 580, 'manifest stage budget is no longer 580')
    check("manifest['runtime_cost']['absolute_stage_seconds']==580" in audit_text and 'began+580' in audit_text, 'stage audit no longer pins the 580-second cap')
    check(590 < manifest['diagnostic_timeout_seconds'] == 600, 'outer monitor must remain strictly below the reviewed 600 seconds')
    result['checks'].append({'name': 'stage_and_outer_budget_fixed', 'pass': True, 'stage_seconds': 580, 'p_wait_seconds': 590, 'reviewed_outer_seconds': 600})
    result['checks'].append({'name': 'import_has_no_subprocess', 'pass': True})
    result['artifacts'] = {'repro_python': str(Path(__file__).resolve()), 'result_json': str(OUT)}
    result['summary'] = {'positive_checks': len(result['checks']), 'negative_controls': len(result['rejections']), 'all_passed': True}
    OUT.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    temp_holder.cleanup()
    print(json.dumps(result, indent=2))

if __name__ == '__main__':
    main()