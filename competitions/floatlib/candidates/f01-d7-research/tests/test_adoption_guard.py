"""Public adoption-decision seam; complete gates are not a performance admission."""
import copy
import importlib.util
from pathlib import Path
import unittest

P = Path(__file__).resolve().parents[1] / 'adoption-guard.py'
spec = importlib.util.spec_from_file_location('adoption_guard', P)
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


def packets(ratio=0.8):
    out = []
    for rid, seed in [(816, 816), (817, 817)]:
        plan = {'seed': seed, 'selection_policy': copy.deepcopy(g.SELECTION_POLICY),
                'comparison_baseline': 'previous', 'profile_parent': False,
                'profile_current': False, 'candidates': [
                    {'candidate': 'new', 'sha256': 'a'*64, 'capture_codegen': False},
                    {'candidate': 'previous', 'sha256': 'b'*64, 'capture_codegen': False}]}
        if rid == 817:
            plan['confirmation_candidates'] = [{'candidate': 'new', 'sha256': 'a'*64,
                                                 'prior_discovery_run': 816}]
        verdicts = {}
        for name, r in [('new', ratio), ('previous', 1.0)]:
            verdicts[name] = {'passed': True, 'mode': 'gate', 'stage': 'score',
                'seed': seed, 'ratio': r, 'rounds': [[1000, int(1000*r)]]*25,
                'verifier_fingerprint': 'fixed', 'verifier_fingerprint_end': 'fixed',
                'suite': {'sha256': g.SUITE_SHA}}
        out.append({'run_id': rid, 'job_id': rid+1000, 'hosted_ubuntu24': True,
                    'plan': plan, 'seed': seed, 'verdicts': verdicts,
                    'kernel_hashes': {'new': 'a'*64, 'previous': 'b'*64},
                    'codegen_present': False})
    return out


class AdoptionGuardTests(unittest.TestCase):
    def validate(self, values):
        return g.validate_packets(values, 'new', 'previous', 'a'*64, 'b'*64)

    def test_two_passed_gates_ten_percent_slower_are_rejected(self):
        with self.assertRaises(ValueError):
            self.validate(packets(1.10))

    def test_changed_baseline_hash_is_rejected(self):
        values = packets(); values[1]['kernel_hashes']['previous'] = 'c'*64
        with self.assertRaises(ValueError): self.validate(values)

    def test_changed_verdict_seed_is_rejected(self):
        values = packets(); values[1]['verdicts']['new']['seed'] = 999
        with self.assertRaises(ValueError): self.validate(values)

    def test_any_observer_is_rejected(self):
        values = packets(); values[1]['plan']['profile_current'] = True
        with self.assertRaises(ValueError): self.validate(values)

    def test_missing_prefrozen_policy_is_rejected(self):
        values = packets(); del values[0]['plan']['selection_policy']
        with self.assertRaises(ValueError): self.validate(values)

    def test_headline_pass_but_adverse_bootstrap_is_rejected(self):
        values = packets()
        values[0]['verdicts']['new']['rounds'] = [[1000, 1100]]*25
        with self.assertRaisesRegex(ValueError, 'p05'): self.validate(values)

    def test_duplicate_actual_job_is_rejected(self):
        values = packets(); values[1]['job_id'] = values[0]['job_id']
        with self.assertRaises(ValueError): self.validate(values)

    def test_failed_statement_seed_zero_is_not_misdiagnosed_as_seed_tampering(self):
        values = packets(); values[0]['verdicts']['new'].update(passed=False, stage='statement', seed=0)
        with self.assertRaisesRegex(ValueError, 'complete passed gate'): self.validate(values)

    def test_boundary_headline_three_percent_and_flat_gain(self):
        values = packets(.97)
        result = self.validate(values)
        self.assertAlmostEqual(result['samples'][0]['gain_p05'], .03)

    def test_changed_plan_baseline_and_capture_are_rejected(self):
        for field in ('baseline', 'capture', 'actual_codegen'):
            values = packets()
            if field == 'baseline': values[1]['plan']['candidates'][1]['sha256'] = 'c'*64
            elif field == 'capture': values[1]['plan']['candidates'][0]['capture_codegen'] = True
            else: values[1]['codegen_present'] = True
            with self.subTest(field=field):
                with self.assertRaises(ValueError): self.validate(values)

    def test_resampling_preserves_reference_submission_pairs(self):
        values = packets()
        for p in values:
            for name, scale in [('new', .8), ('previous', 1.)]:
                p['verdicts'][name]['rounds'] = [[1000*(i+1), int(1000*(i+1)*scale)] for i in range(25)]
        result = self.validate(values)
        for sample in result['samples']: self.assertAlmostEqual(sample['gain_p05'], .2)

    def test_real_adopter_rejects_before_any_persistent_write(self):
        import subprocess
        root = P.parents[4]
        targets = [root/'dashboard.md', root/'competitions/floatlib/coordination/development-status.json',
                   P.parent/'multiplier-comparison.json', P.parent/'public-suite-results.json']
        before = [g.digest(p) for p in targets]
        run = subprocess.run([__import__('sys').executable, '-B', str(P.parent/'adopt-confirmed.py'),
            '--candidate', 'f01-d7-direct-singlepass', '--previous', 'f01-d7-direct-nonnan',
            '--discovery', '39903049887', '--confirmation', '39903049887'],
            cwd=root, capture_output=True, text=True)
        self.assertNotEqual(run.returncode, 0)
        self.assertIn('Not a complete passed gate: f01-d7-direct-singlepass', run.stderr)
        self.assertEqual(before, [g.digest(p) for p in targets])

    def test_actual_811_raw_identity_and_failed_cc06(self):
        root = P.parents[4]
        p = g.load_run(root, P.parent, 39903049887, ('f01-d7-direct-nonnan',))
        self.assertEqual((p['run_id'], p['job_id'], p['seed']), (39903049887, 120248703399, 811))
        self.assertTrue(p['hosted_ubuntu24'])
        self.assertIsNone(p['evidence']['run_attempt'])
        self.assertNotIn('selection_policy', p['plan'])
        with self.assertRaisesRegex(ValueError, 'complete passed gate'):
            g.load_run(root, P.parent, 39903049887, ('f01-d7-direct-singlepass', 'f01-d7-direct-nonnan'))

    def test_actual_plan_must_match_original_commit_tree(self):
        from unittest import mock
        root = P.parents[4]
        # Only the original-tree reader is mocked; the real811 indexed gate is intact.
        with mock.patch.object(g, 'read_tree_blob', create=True, return_value=b'{}'):
            with self.assertRaisesRegex(ValueError, 'commit-tree plan'):
                g.load_run(root, P.parent, 39903049887, ('f01-d7-direct-nonnan',))

    def test_verifier_rejects_failed_run_or_job_but_loader_preserves_control(self):
        from unittest import mock
        root = P.parents[4]
        control = g.load_run(root, P.parent, 39903049887, ('f01-d7-direct-nonnan',))
        self.assertEqual(control['run_conclusion'], 'failure')
        self.assertEqual(control['job_conclusion'], 'failure')
        for failed in ('run_conclusion', 'job_conclusion'):
            sample = copy.deepcopy(control)
            sample.update(run_conclusion='success', job_conclusion='success')
            sample[failed] = 'failure'
            with self.subTest(failed=failed), mock.patch.object(g, 'load_run', return_value=sample):
                with self.assertRaisesRegex(ValueError, 'run/job conclusions'):
                    g.verify_adoption(root, P.parent, 'f01-d7-direct-singlepass',
                        39903049887, 39903049888, 'f01-d7-direct-nonnan')

    def test_valid_frozen_improvement_has_positive_local_p05(self):
        result = self.validate(packets())
        self.assertTrue(result['accepted'])
        self.assertEqual(len(result['samples']), 2)
        self.assertAlmostEqual(result['samples'][1]['gain_p05'], .2)


if __name__ == '__main__': unittest.main()
