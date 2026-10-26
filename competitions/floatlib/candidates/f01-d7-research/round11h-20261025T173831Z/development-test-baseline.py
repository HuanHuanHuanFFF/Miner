"""Baseline migration regression using immutable real receipts; no Lean or CI."""
from pathlib import Path
import hashlib,importlib.util,json,subprocess,sys,unittest

HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
BASE='f01-r15-dev-packed-b2-1'
SHA='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
OLD='f01-d12-scalar-combined'
def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path);result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result
v=module('r18_test_verify',HERE/'verify-three-groups.py')
ad=module('r18_test_adopt',HERE/'adopt-three-confirmed.py')
est=module('r18_test_estimate',ROOT/'competitions/floatlib/scripts/estimate_champion_time.py')
records=json.loads((HERE.parent/'public-suite-results.json').read_bytes())['records']
historical=[r for r in records if r['run']==40168687803 and r.get('full_gate')]
candidate=est.checked_record(next(r for r in historical if r['candidate']==OLD),ROOT)
control=est.checked_record(next(r for r in historical if r['candidate']=='f01-r8-combined-result-guard'),ROOT)

class BaselineMigration(unittest.TestCase):
    def test_current_model_and_source_identity(self):
        identity=v.retained_model_identity()
        self.assertEqual(identity['source_sha256'],SHA)
        self.assertEqual(identity['sha256'],'9222bdf6edec6efe75c009203405357155045f75028727a2e1fc237b9a343e53')
        self.assertEqual(v.BASELINE_SHA,ad.BASELINE)
        self.assertEqual(ad.BASELINE,SHA)
    def test_score_pair_uses_B2_even_when_historical_plan_used_DF(self):
        pairs=ad.scoring_pairs(historical,[(candidate,control)],est,ROOT)
        self.assertEqual(pairs[0][1]['kernel_sha256'],SHA)
        self.assertEqual(pairs[0][1]['candidate'],BASE)
    def test_missing_B2_cannot_fall_back_to_DF_or41(self):
        with self.assertRaisesRegex(ValueError,'retainedB2'):
            ad.scoring_pairs([r for r in historical if r['candidate']!=BASE],[(candidate,control)],est,ROOT)
    def test_wrong_planning_baseline_refused_without_writing(self):
        live=ROOT/'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'
        before=live.read_bytes()
        probe=subprocess.run([sys.executable,'-B',str(HERE/'prepare-plan.py'),'--seed','1626000','--candidates',OLD,'f01-r8-combined-result-guard'],cwd=ROOT,capture_output=True)
        self.assertNotEqual(probe.returncode,0)
        self.assertIn(b'retainedB2',probe.stderr)
        self.assertEqual(live.read_bytes(),before)
        self.assertFalse((HERE/'plan-1626000.json').exists())
    def test_selection_threshold_and_confirmation_count_unchanged(self):
        policy=json.loads((HERE/'selection-policy.json').read_bytes())
        original=json.loads((HERE.parent/'round3h-20261025T043928Z/selection-policy.json').read_bytes())
        self.assertEqual(policy['selection_policy'],original['selection_policy'])
        self.assertEqual(policy['additional_inputs']['groups_total_target'],3)
        self.assertEqual(policy['baseline'],dict(candidate=BASE,sha256=SHA))
    def test_frozen_numeric_source_not_reestimated(self):
        path=ROOT/'competitions/floatlib/candidates/f01-d7-research/champion-time-estimate.json'
        self.assertEqual(hashlib.sha256(path.read_bytes()).hexdigest(),'9222bdf6edec6efe75c009203405357155045f75028727a2e1fc237b9a343e53')

if __name__=='__main__':unittest.main()
