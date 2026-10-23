"""Exercise the actual renderer with frozen real models in a disposable workspace."""
from pathlib import Path
from hashlib import sha256
import importlib.util
import json
import tempfile
import unittest
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
REL = Path('competitions/floatlib/candidates/f01-d7-research')
spec = importlib.util.spec_from_file_location('frozen_dashboard_renderer', ROOT/'competitions/floatlib/scripts/render_dashboard.py')
renderer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(renderer)


class FrozenResearchDashboardTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='.dashboard-test-', dir=HERE)
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.data = self.root/REL
        # Fixed historical models keep this test valid after a future adoption
        # changes the live state/view or the current official snapshot.
        old = ROOT/REL/'round2h-20261023T170031Z'
        anchor = json.loads((old/'freeze-anchor.json').read_bytes())
        original = anchor['original_model']
        measured = json.loads((old/'best-research-champion-estimate.json').read_bytes())
        self.model = (old/'best-research-champion-estimate.json').read_bytes()
        retained_kernel = 'competitions/floatlib/candidates/f01-r8-combined-result-guard/Kernel.lean'
        self.research = {'candidate': measured['candidate'], 'kernel_sha256': measured['kernel_sha256'],
                         'full_gate_runs': measured['full_gate_runs'], 'bmm_label': '按行寻址',
                         'kernel': 'competitions/floatlib/candidates/f01-d10-bmm-direct-rows/Kernel.lean',
                         'evidence': (REL/'fixture-research-model.json').as_posix(),
                         'evidence_sha256': sha256(self.model).hexdigest()}
        retained_bytes = (json.dumps(original)+'\n').encode()
        retained_evidence = (REL/'fixture-retained-model.json').as_posix()
        self.view = {'kernel_sha256': original['kernel_sha256'],
                     'champion': {'submission': 285, 'digest': original['champion_digest'],
                                  'official_normalized_self_time': 1.0, 'receipts': 'fixture-receipts.json',
                                  'candidate_over_champion_time_by_operation': {op:'UNKNOWN' for op in ('add','mul','sum','bmm')}},
                     'dashboard_policy': {'baseline':'current_champion','layout':'legacy_four_operations',
                                          'candidate_labels_by_operation':{op:op for op in ('add','mul','sum','bmm')},
                                          'use_estimates_when_direct_unknown':True},
                     'full_gate_runs':[s['run'] for s in original['samples']],
                     'public_results':(REL/'fixture-index.json').as_posix(),
                     'champion_time_estimate':dict(original,evidence=retained_evidence,evidence_sha256=sha256(retained_bytes).hexdigest()),
                     'dashboard_research_candidate':self.research}
        self.state = {'kernel':retained_kernel,'kernel_sha256':original['kernel_sha256']}
        for relative in [self.state['kernel'], self.research['kernel']]:
            target = self.root/relative
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes((ROOT/relative).read_bytes())
        self.data.mkdir(parents=True, exist_ok=True)
        (self.root/retained_evidence).write_bytes(retained_bytes)
        (self.root/self.research['evidence']).write_bytes(self.model)
        self.save(self.data/'multiplier-comparison.json', self.view)
        self.save(self.root/'competitions/floatlib/coordination/development-status.json', self.state)
        self.save(self.data/'current-official-snapshot.json', {'champion':285,'queried_at_utc':'2026-10-23T18:48:04Z'})
        self.records = [{'run': run, 'full_gate': True, 'kernel_sha256': self.research['kernel_sha256']}
                        for run in self.research['full_gate_runs']]
        self.index = self.root/self.view['public_results']
        self.save(self.index, {'records': self.records})

    def save(self, path, data):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(data), encoding='utf-8')

    def render(self):
        with patch.object(renderer, 'ROOT', self.root), patch.object(renderer, 'DATA', self.data):
            renderer.main()
        return (self.root/'dashboard.md').read_bytes()

    def test_extra_same_source_control_does_not_recalibrate_or_break_frozen_model(self):
        before = self.render()
        self.records.append({'run': 99999999999, 'full_gate': True,
                             'kernel_sha256': self.research['kernel_sha256']})
        self.save(self.index, {'records': self.records})
        self.assertEqual(self.render(), before)
        self.assertEqual((self.root/self.research['evidence']).read_bytes(), self.model)

    def test_missing_frozen_validation_group_still_rejected(self):
        self.save(self.index, {'records': self.records[1:]})
        with self.assertRaises(AssertionError):
            self.render()


if __name__ == '__main__':
    unittest.main()
