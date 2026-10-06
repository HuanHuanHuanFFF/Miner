"""Small regression checks at the round2 gate-policy and diagnostic CLI boundaries."""
from __future__ import annotations
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PRIOR = ROOT / 'evidence/round2/37454635334'
REQUIRED = ('probe3', 'probe2-nice16', 'probe2-nice64')


class GatePolicy(unittest.TestCase):
    def call(self, reports, *args):
        return subprocess.run([sys.executable, str(ROOT / 'scripts/check-round2-gates.py'),
                               str(reports), *args], capture_output=True, text=True)

    def test_prior_real_bucket_rejection_is_optional(self):
        self.assertFalse(json.loads((PRIOR / 'bucket2-gate.json').read_text())['accepted'])
        result = self.call(PRIOR)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('bucket2 proof rejected', result.stdout)
        for name in REQUIRED:
            self.assertIn('REQUIRED_GATE_ACCEPTED ' + name, result.stdout)

    def test_strict_bucket_experiment_still_fails(self):
        result = self.call(PRIOR, '--require-bucket2')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('bucket2: gate did not accept', result.stderr)

    def test_required_rejection_missing_or_wrong_scope_cannot_pass(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp)
            for name in REQUIRED:
                shutil.copyfile(PRIOR / (name + '-gate.json'), path / (name + '-gate.json'))
            target = path / 'probe3-gate.json'
            original = json.loads(target.read_text())
            for change in ('missing', 'rejected', 'wrong-scope'):
                with self.subTest(change=change):
                    if change == 'missing':
                        target.unlink()
                    else:
                        updated = dict(original)
                        updated['accepted'] = change != 'rejected'
                        updated['corpora'] = ['corpus-stage2'] if change == 'wrong-scope' else ['corpus-stage1']
                        target.write_text(json.dumps(updated))
                    result = self.call(path)
                    self.assertNotEqual(result.returncode, 0)
                    self.assertIn('probe3:', result.stderr)

    def test_opted_out_bucket_needs_no_report(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp)
            for name in REQUIRED:
                shutil.copyfile(PRIOR / (name + '-gate.json'), path / (name + '-gate.json'))
            result = self.call(path)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertIn('EXPERIMENTAL_GATE_NOT_RUN bucket2', result.stdout)


class FullDiagnostics(unittest.TestCase):
    def test_error_head_survives_more_than_2000_characters(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp)
            upstream = path / 'upstream'
            work = upstream / 'data/verification-workspace/verify-test'
            (work / 'logs').mkdir(parents=True)
            reports = path / 'deflate-reports'
            reports.mkdir()
            (reports / 'bucket2-gate.log').write_text('workspace: ' + str(work) + '\n')
            log = 'Proof/Parse.lean:1:1: error: ORIGINAL_ERROR_HEAD\n' + 'context line\n' * 400
            (work / 'logs/003-lake.log').write_bytes(log.encode())
            env = os.environ | {'GITHUB_ACTIONS': 'true', 'DEFLATE_ROOT': str(upstream),
                                'RUNNER_TEMP': str(path)}
            result = subprocess.run([sys.executable, str(ROOT / 'scripts/round2-gate-diagnostics.py'),
                                     'bucket2'], env=env, capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertIn('ORIGINAL_ERROR_HEAD', result.stdout)
            self.assertIn(log, result.stdout)
            manifest = json.loads((reports / 'bucket2-diagnostics.json').read_text())
            self.assertEqual(manifest['logs']['003-lake.log']['bytes'], len(log.encode()))


if __name__ == '__main__':
    unittest.main()
