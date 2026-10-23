"""Synthetic I/O with the real unchanged statistical validator; no Git or CI."""
from copy import deepcopy
import hashlib
import importlib.util
import contextlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location("three_groups", HERE / "verify-three-groups.py")
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)
guard = mod.import_guard()  # Import has no Git/process or artifact access.
CANDIDATE = "synthetic-candidate"
BASELINE = "f01-r8-combined-result-guard"
SOURCE = "a" * 64
REFERENCE = {"incumbent_sha256": "b" * 64, "champion_sha256": "c" * 64}


def freeze_fixture():
    binding = mod.import_binding()
    paths = binding.required_local_paths(mod.ROOT, HERE) + [mod.ROOT/n for n in binding.EXECUTION_FILES]
    return {"schema_version": 1, "required_groups": 3, "frozen_at_utc": "2026-10-23T00:00:00Z",
            "holdouts_unseen_before_freeze": True,
            "candidate": {"name": CANDIDATE, "sha256": SOURCE},
            "baseline": {"name": BASELINE, "sha256": mod.BASELINE_SHA},
            "groups": {"D": {"run": 101, "seed": 11}, "A": {"seed": 22}, "B": {"seed": 33}},
            "candidate_orders": {r: [CANDIDATE, BASELINE] for r in ('D','A','B')},
            "selection_policy": deepcopy(guard.SELECTION_POLICY), "suite_sha256": guard.SUITE_SHA,
            "generator_sha256": guard.GENERATOR_SHA, "reference": REFERENCE,
            "execution_files": binding.snapshot(mod.ROOT),
            "files": {p.relative_to(mod.ROOT).as_posix(): {"sha256": mod.digest(p)} for p in paths}}


def packet_fixture(run, seed, factor=0.8):
    plan = {"seed": seed, "selection_policy": deepcopy(guard.SELECTION_POLICY),
            "sample_role": "DISCOVERY",
            "comparison_baseline": BASELINE, "profile_parent": False, "profile_current": False,
            "candidates": [{"candidate": CANDIDATE, "sha256": SOURCE, "capture_codegen": False},
                           {"candidate": BASELINE, "sha256": mod.BASELINE_SHA, "capture_codegen": False}]}
    if run != 101:
        plan["confirmation_candidates"] = [{"candidate": CANDIDATE, "sha256": SOURCE, "prior_discovery_run": 101}]
        plan['sample_role'] = 'FROZEN_INDEPENDENT_CONFIRMATION'
        plan['cohort'] = {'role': 'A' if run == 102 else 'B', 'sha256': hashlib.sha256(
            (json.dumps(freeze_fixture(),ensure_ascii=False,indent=2)+'\n').encode()).hexdigest()}
    def verdict(ratio):
        return {"passed": True, "mode": "gate", "stage": "score", "seed": seed,
                "suite": {"sha256": guard.SUITE_SHA}, "verifier_fingerprint": "fixed", "verifier_fingerprint_end": "fixed",
                "ratio": ratio, "rounds": [[100, 100 * ratio] for _ in range(25)], **REFERENCE}
    return {"run_id": run, "job_id": run + 1000, "seed": seed, "plan": plan,
            "hosted_ubuntu24": True, "codegen_present": False,
            "run_conclusion": "success", "job_conclusion": "success", "job_name": "floatlib",
            "kernel_hashes": {CANDIDATE: SOURCE, BASELINE: mod.BASELINE_SHA},
            "verdicts": {CANDIDATE: verdict(factor), BASELINE: verdict(1)},
            "evidence": {"suite_sha256": guard.SUITE_SHA, "generator_sha256": guard.GENERATOR_SHA,
                         "source_commit": f'{run:040x}',
                         "drawn_plan_sha256": hashlib.sha256(str(run).encode()).hexdigest()}}


class SyntheticIO:
    def __init__(self):
        self.packets = {r: packet_fixture(r, s) for r, s in ((101, 11), (102, 22), (103, 33))}
        self.calls = []
        self.execution = {f'{r:040x}': {name: (mod.ROOT/name).read_bytes()
                          for name in mod.import_binding().EXECUTION_FILES} for r in self.packets}

    def read_tree_blob(self, root, source_commit, relative):
        return self.execution[source_commit][relative]

    def load_run(self, root, own, run, names):
        if run not in self.packets:
            raise FileNotFoundError("missing third original artifact")
        return deepcopy(self.packets[run])

    def verify_adoption(self, root, own, candidate, discovery, confirmation, baseline):
        self.calls.append((discovery, confirmation))
        packets = [self.load_run(root, own, r, (candidate, baseline)) for r in (discovery, confirmation)]
        # The actual policy, thresholds, bootstrap and random stream are unchanged.
        result = guard.validate_packets(packets, candidate, baseline, SOURCE, mod.BASELINE_SHA)
        result["identity"] = {"candidate": CANDIDATE, "candidate_sha256": SOURCE,
                              "baseline": BASELINE, "baseline_sha256": mod.BASELINE_SHA}
        return result, packets

    def shapes(self, root, helper, packet):
        cases = [{"name": "bmm:dense:0", "kernel": "bmm", "timed": True, "length": 1,
                  "batch": 1, "m": 2, "n": 3, "p": 4, "work": 24, "seed": packet["seed"], "mag": 0}]
        result = mod.shape_evidence({"cases": cases})
        result["raw_sha256"] = packet["evidence"]["drawn_plan_sha256"]
        return result


class ThreeGroupTests(unittest.TestCase):
    def setUp(self):
        self.freeze = freeze_fixture()
        self.io = SyntheticIO()
        self.runs = {"D": 101, "A": 102, "B": 103}
        no_git = patch.object(guard.subprocess, "check_output", side_effect=AssertionError("Git forbidden in tests"))
        no_git.start()
        self.addCleanup(no_git.stop)

    def run_verify(self):
        return mod.verify_three_groups(self.freeze, self.runs, self.io, shape_loader=self.io.shapes)

    def test_three_groups_pass_both_real_policy_calls_discovery_counted_once(self):
        result = self.run_verify()
        self.assertTrue(result["accepted"], result["failures"])
        self.assertEqual(result["group_count"], 3)
        self.assertEqual(self.io.calls, [(101, 102), (101, 103)])
        self.assertFalse(result["adoption_performed"])
        self.assertEqual(set(result["groups"]), {"D", "A", "B"})
        self.assertEqual(set(result['groups']['B']['execution_binding']['files']),
                         set(mod.import_binding().EXECUTION_FILES))

    def test_third_actual_outer_helper_change_rejected_with_all_original_groups_kept(self):
        key = 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
        self.io.execution[f'{103:040x}'][key] += b'changed'
        result = self.run_verify()
        self.assertFalse(result['accepted'])
        self.assertEqual(result['group_count'], 3)
        self.assertTrue(any(f['stage'] == 'execution:B' and key in f['reason'] for f in result['failures']))

    def test_discovery_actual_workflow_change_rejected(self):
        key = '.github/workflows/deflate-baseline.yml'
        self.io.execution[f'{101:040x}'][key] += b'changed'
        result = self.run_verify()
        self.assertFalse(result['accepted'])
        self.assertTrue(any(f['stage'] == 'execution:D' and key in f['reason'] for f in result['failures']))

    def test_missing_actual_commit_cannot_skip_execution_check(self):
        del self.io.packets[102]['evidence']['source_commit']
        self.assertFalse(self.run_verify()['accepted'])

    def test_freeze_cannot_omit_outer_helper_from_execution_manifest(self):
        del self.freeze['execution_files']['competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py']
        with patch.object(mod, 'digest', return_value='expected'):
            with self.assertRaisesRegex(ValueError, 'execution files'):
                mod.verify_freeze(self.freeze, 'expected', Path('fake-freeze'), guard)

    def test_freeze_cannot_omit_renderer(self):
        del self.freeze['files']['competitions/floatlib/scripts/render_dashboard.py']
        with patch.object(mod, 'digest', return_value='expected'):
            with self.assertRaisesRegex(ValueError, 'Missing frozen helper'):
                mod.verify_freeze(self.freeze, 'expected', Path('fake-freeze'), guard)

    def test_execution_table_cannot_disagree_with_local_frozen_file(self):
        self.freeze['execution_files']['.github/workflows/deflate-baseline.yml']['sha256'] = '0'*64
        with patch.object(mod, 'digest', return_value='expected'):
            with self.assertRaisesRegex(ValueError, 'binding differs'):
                mod.verify_freeze(self.freeze, 'expected', Path('fake-freeze'), guard)

    def test_reusing_confirmation_a_as_b_is_rejected(self):
        self.runs["B"] = 102
        result = self.run_verify()
        self.assertFalse(result["accepted"])
        self.assertTrue(any("distinct" in f["reason"] for f in result["failures"]))

    def test_wrong_source_rejected(self):
        self.io.packets[103]["kernel_hashes"][CANDIDATE] = "d" * 64
        result = self.run_verify()
        self.assertFalse(result["accepted"])
        self.assertIn("B", result["groups"])

    def test_confirmation_order_cannot_be_relabelled_after_measurement(self):
        self.io.packets[103]['plan']['candidates'].reverse()
        result = self.run_verify()
        self.assertFalse(result['accepted'])
        self.assertTrue(any('order' in x['reason'] for x in result['failures']))

    def test_confirmation_must_bind_the_exact_cohort_digest(self):
        self.io.packets[102]['plan']['cohort']['sha256'] = '0'*64
        result = self.run_verify()
        self.assertFalse(result['accepted'])
        self.assertTrue(any('digest' in x['reason'] for x in result['failures']))

    def test_confirmation_cannot_claim_the_other_frozen_role(self):
        self.io.packets[103]['plan']['cohort']['role'] = 'A'
        result = self.run_verify()
        self.assertFalse(result['accepted'])
        self.assertTrue(any('role' in x['reason'] for x in result['failures']))

    def test_missing_third_group_is_preserved_as_failure(self):
        del self.io.packets[103]
        result = self.run_verify()
        self.assertFalse(result["accepted"])
        self.assertTrue(any(x["stage"] == "raw:B" for x in result["failures"]))
        self.assertIn("D+A", result["pairs"])

    def test_slow_third_group_does_not_disappear_or_average_into_pass(self):
        self.io.packets[103] = packet_fixture(103, 33, 1.04)
        result = self.run_verify()
        self.assertFalse(result["accepted"])
        self.assertEqual(result["groups"]["B"]["relative_normalized_ratio"], 1.04)
        self.assertEqual(result["group_count"], 3)
        self.assertAlmostEqual(result["groups"]["A"]["gain_p05"], 0.2)
        self.assertEqual(len(result["input_comparisons"]), 3)
        self.assertTrue(any("headline" in x["reason"] for x in result["failures"]))
        self.assertEqual(self.io.calls, [(101, 102), (101, 103)])

    def test_coincident_shapes_are_reported_as_value_generation_only(self):
        result = self.run_verify()
        self.assertTrue(result["accepted"])
        for comparison in result["input_comparisons"].values():
            self.assertEqual(comparison["shape_work_changed_cases"], 0)
            self.assertEqual(comparison["generation_changed_cases"], 1)
            self.assertEqual(comparison["diversity_kind"], "VALUE_GENERATION_ONLY")

    def test_different_json_hashes_with_identical_cases_do_not_prove_new_inputs(self):
        original = self.io.shapes
        def same_values(root, helper, packet):
            p = deepcopy(packet)
            p["seed"] = 11
            return original(root, helper, p)
        self.io.shapes = same_values
        result = self.run_verify()
        self.assertFalse(result["accepted"])
        self.assertTrue(any("actual cases" in f["reason"] for f in result["failures"]))

    def test_third_reference_or_generator_change_is_rejected_globally(self):
        self.io.packets[103]["verdicts"][CANDIDATE]["incumbent_sha256"] = "d" * 64
        self.assertFalse(self.run_verify()["accepted"])
        self.io = SyntheticIO()
        self.io.packets[103]["evidence"]["generator_sha256"] = "d" * 64
        self.assertFalse(self.run_verify()["accepted"])

    def test_same_actual_job_different_runs_is_rejected(self):
        self.io.packets[103]["job_id"] = self.io.packets[102]["job_id"]
        self.assertFalse(self.run_verify()["accepted"])

    def test_missing_or_reused_drawn_plan_hash_is_rejected(self):
        self.io.packets[103]["evidence"]["drawn_plan_sha256"] = self.io.packets[102]["evidence"]["drawn_plan_sha256"]
        self.assertFalse(self.run_verify()["accepted"])
        self.io.packets[103]["evidence"]["drawn_plan_sha256"] = ""
        self.assertFalse(self.run_verify()["accepted"])

    def test_changed_freeze_external_digest_is_rejected_before_artifact_access(self):
        with tempfile.TemporaryDirectory(prefix=".three-group-test-", dir=HERE) as directory:
            self.assertEqual(Path(directory).resolve().parent, HERE.resolve())
            path = Path(directory) / "freeze.json"
            path.write_text(json.dumps(self.freeze), encoding="utf-8")
            expected = mod.digest(path)
            path.write_text(json.dumps({**self.freeze, "holdouts_unseen_before_freeze": False}), encoding="utf-8")
            with self.assertRaisesRegex(ValueError, "external SHA"):
                mod.verify_freeze(mod.read(path), expected, path, guard)

    def test_changed_frozen_helper_is_rejected(self):
        freeze = deepcopy(self.freeze)
        path = (HERE.parent / "adoption-guard.py").relative_to(mod.ROOT).as_posix()
        freeze["files"][path]["sha256"] = "changed"
        actual_digest = mod.digest
        def fake_digest(path):
            return "expected" if str(path) == "fake-freeze" else actual_digest(path)
        with patch.object(mod, "digest", side_effect=fake_digest):
            with self.assertRaisesRegex(ValueError, "Frozen file changed"):
                mod.verify_freeze(freeze, "expected", Path("fake-freeze"), guard)

    def test_changed_policy_cannot_relax_threshold(self):
        self.freeze["selection_policy"]["headline_normalized_ratio_max"] = 1.1
        with patch.object(mod, "digest", return_value="expected"):
            with self.assertRaisesRegex(ValueError, "policy"):
                mod.verify_freeze(self.freeze, "expected", Path("fake-freeze"), guard)

    def test_complete_freeze_schema_and_all_real_helper_hashes_pass(self):
        actual_digest = mod.digest
        candidate_path = mod.ROOT / "competitions/floatlib/candidates" / CANDIDATE / "Kernel.lean"
        with tempfile.TemporaryDirectory(prefix=".three-group-test-", dir=HERE) as directory:
            self.assertEqual(Path(directory).resolve().parent, HERE.resolve())
            path = Path(directory) / "freeze.json"
            path.write_text(json.dumps(self.freeze), encoding="utf-8")
            expected = actual_digest(path)
            def candidate_digest(p):
                return SOURCE if Path(p) == candidate_path else actual_digest(p)
            with patch.object(mod, "digest", side_effect=candidate_digest):
                mod.verify_freeze(self.freeze, expected, path, guard)

    def test_actual_shape_and_work_change_count_is_reported(self):
        packet = self.io.packets[101]
        left = self.io.shapes(None, None, packet)
        right = deepcopy(left)
        right["shape_vector"][0]["m"] = 9
        right["shape_vector"][0]["work"] = 108
        result = mod.compare_inputs(left, right)
        self.assertEqual(result["shape_work_changed_cases"], 1)
        self.assertEqual(result["bmm_shape_work_changed_cases"], 1)
        self.assertEqual(result["generation_changed_cases"], 0)
        self.assertEqual(result["diversity_kind"], "SHAPE_WORK_ONLY")

    def test_already_executed_old_drawn_plans_reproduce_review_shape_counts(self):
        review = mod.read(HERE.parent / "round2h-20261023T170031Z" / "multi-input-review.json")
        shapes = []
        for example in review["already_executed_examples"]:
            packet = {"run_id": example["run"], "evidence": {"drawn_plan_sha256": example["drawn_plan"]["sha256"]}}
            actual = mod.load_shapes(mod.ROOT, guard, packet)
            self.assertEqual(actual["cases"], 156)
            self.assertEqual(actual["timed_cases"], 152)
            shapes.append(actual)
        comparison = mod.compare_inputs(*shapes)
        self.assertEqual(comparison["shape_work_changed_cases"], 81)
        self.assertEqual(comparison["bmm_shape_work_changed_cases"], 35)

    def test_cli_rechecks_freeze_after_guards_before_writing_accepted_receipt(self):
        with tempfile.TemporaryDirectory(prefix=".three-group-test-", dir=HERE) as directory:
            self.assertEqual(Path(directory).resolve().parent, HERE.resolve())
            path = Path(directory) / "freeze.json"
            output = Path(directory) / "receipt.json"
            path.write_text(json.dumps(self.freeze), encoding="utf-8")
            args = ["--freeze", str(path), "--freeze-sha256", mod.digest(path),
                    "--discovery", "101", "--confirmation-a", "102", "--confirmation-b", "103", "--output", str(output)]
            result = self.run_verify()
            self.assertTrue(result["accepted"])
            with patch.object(mod, "verify_freeze", side_effect=[None, ValueError("freeze changed during validation")]) as check:
                with patch.object(mod, "verify_three_groups", return_value=result):
                    with contextlib.redirect_stdout(io.StringIO()):
                        self.assertEqual(mod.main(args), 2)
            self.assertEqual(check.call_count, 2)
            receipt = mod.read(output)
            self.assertFalse(receipt["accepted"])
            self.assertEqual(len(receipt["pairs"]), 2)
            self.assertTrue(any("during" in x["reason"] for x in receipt["failures"]))

    def test_cli_freeze_rejection_writes_receipt_only_and_refuses_overwrite(self):
        with tempfile.TemporaryDirectory(prefix=".three-group-test-", dir=HERE) as directory:
            self.assertEqual(Path(directory).resolve().parent, HERE.resolve())
            path = Path(directory) / "freeze.json"
            output = Path(directory) / "receipt.json"
            path.write_text(json.dumps(self.freeze), encoding="utf-8")
            args = ["--freeze", str(path), "--freeze-sha256", "0" * 64,
                    "--discovery", "101", "--confirmation-a", "102", "--confirmation-b", "103", "--output", str(output)]
            with patch.object(mod, "verify_three_groups", side_effect=AssertionError("Artifacts must not be accessed")):
                with contextlib.redirect_stdout(io.StringIO()):
                    self.assertEqual(mod.main(args), 2)
                self.assertFalse(mod.read(output)["accepted"])
                before = output.read_bytes()
                with self.assertRaises(FileExistsError):
                    mod.main(args)
                self.assertEqual(output.read_bytes(), before)


if __name__ == "__main__":
    unittest.main(verbosity=2)
