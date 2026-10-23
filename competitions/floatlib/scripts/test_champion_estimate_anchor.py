"""Behavioral checks for frozen estimates, including real archived gate provenance."""
from copy import deepcopy
import importlib.util
from pathlib import Path
import contextlib
import io
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location("champion_estimator", Path(__file__).with_name("estimate_champion_time.py"))
est = importlib.util.module_from_spec(spec)
spec.loader.exec_module(est)


class AnchorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.anchor = est.load(est.DEFAULT_ANCHOR)

    def pair(self, factor=0.8, run=9001, reference_factor=1.0):
        baseline = deepcopy(self.anchor["frozen_records"][0])
        baseline.update(run=run, runner_execution="synthetic-execution-" + str(run))
        candidate = deepcopy(baseline)
        candidate["kernel_sha256"] = "new-source"
        for cell in candidate["classes"].values():
            # Reference and submission may both drift within the two gates.
            cell["submission_ns"] *= factor * reference_factor
            cell["incumbent_ns"] *= reference_factor
        return candidate, baseline

    def estimate(self, source=None, pairs=(), champion=None, suite=None):
        a = self.anchor
        return est.estimate_from_anchor(a, source or a["candidate_kernel_sha256"],
                                       champion or a["champion_digest"],
                                       suite or a["champion_suite"], pairs)

    def test_same_source_slow_controls_cannot_change_display(self):
        first = self.estimate()
        candidate, baseline = self.pair(factor=1000)
        candidate["kernel_sha256"] = self.anchor["candidate_kernel_sha256"]
        # Even an added slow control must not enter the frozen source estimate.
        after = self.estimate(pairs=[(candidate, baseline)])
        self.assertEqual(first["operations"], after["operations"])
        self.assertEqual(first["whole"], after["whole"])
        self.assertEqual(first["samples"], after["samples"])
        self.assertEqual(after["operations"], self.anchor["original_model"]["operations"])

    def test_paired_normalized_improvement_scales_every_operation_and_whole(self):
        updated = self.estimate("new-source", [self.pair(0.8, reference_factor=2.7)])
        original = self.anchor["original_model"]
        for op in est.OPS:
            self.assertAlmostEqual(updated["operations"][op]["ratio_median"], original["operations"][op]["ratio_median"] * 0.8)
        self.assertAlmostEqual(updated["whole"]["ratio_median"], original["whole"]["ratio_median"] * 0.8)
        self.assertEqual(updated["direct_same_suite_champion_comparison"], "UNKNOWN")

    def test_negative_pair_is_retained_in_predeclared_cell_median(self):
        updated = self.estimate("new-source", [self.pair(0.8, 9001), self.pair(1.4, 9002)])
        for delta in updated["cell_relative_delta_median"].values():
            self.assertAlmostEqual(delta, 1.1)
        self.assertEqual(len(updated["paired_updates"]), 2)
        self.assertGreater(updated["whole"]["ratio_median"], self.anchor["original_model"]["whole"]["ratio_median"])

    def test_work_projection_resums_whole_instead_of_averaging_operations(self):
        candidate, baseline = self.pair(1)
        for name, cell in candidate["classes"].items():
            if name.startswith("bmm:"):
                cell["submission_ns"] *= 0.5
        result = self.estimate("new-source", [(candidate, baseline)])
        for old, new in zip(self.anchor["original_model"]["samples"], result["samples"]):
            self.assertAlmostEqual(new["whole_ratio"],
                                   (sum(old["candidate_total_ns"].values()) - old["candidate_total_ns"]["bmm"] * 0.5) /
                                   sum(old["champion_projected_total_ns"].values()))
        self.assertEqual(result["operations"]["add"], self.anchor["original_model"]["operations"]["add"])

    def test_wrong_candidate_baseline_suite_runner_seed_and_reference_rejected(self):
        changes = [("candidate", "kernel_sha256", "wrong-source"),
                   ("baseline", "kernel_sha256", "wrong-baseline"),
                   ("candidate", "suite_sha256", "wrong-suite"),
                   ("candidate", "runner_execution", "other-job"),
                   ("candidate", "seed", -1),
                   ("candidate", "drawn_plan_sha256", "other-inputs"),
                   ("candidate", "incumbent_sha256", "other-reference"),
                   ("candidate", "rounds", 1), ("candidate", "full_gate", False)]
        for side, field, value in changes:
            with self.subTest(side=side, field=field):
                c, b = self.pair()
                (c if side == "candidate" else b)[field] = value
                with self.assertRaises(est.EstimateRejected):
                    self.estimate("new-source", [(c, b)])

    def test_changed_champion_digest_or_suite_rejected_even_for_same_source(self):
        with self.assertRaises(est.EstimateRejected):
            self.estimate(champion="new-champion")
        for key in ("version", "sha256"):
            suite = deepcopy(self.anchor["champion_suite"])
            suite[key] = "new-suite"
            with self.assertRaises(est.EstimateRejected):
                self.estimate(suite=suite)

    def test_absolute_ns_without_pair_rejected(self):
        with self.assertRaises(est.EstimateRejected):
            self.estimate("new-source")

    def test_duplicate_pair_missing_cell_and_invalid_time_rejected(self):
        pair = self.pair()
        with self.assertRaises(est.EstimateRejected):
            self.estimate("new-source", [pair, pair])
        for value in (0, -1, float("nan"), float("inf")):
            c, b = self.pair()
            c["classes"][next(iter(c["classes"]))]["submission_ns"] = value
            with self.assertRaises(est.EstimateRejected):
                self.estimate("new-source", [(c, b)])
        c, b = self.pair()
        del c["classes"][next(iter(c["classes"]))]
        with self.assertRaises(est.EstimateRejected):
            self.estimate("new-source", [(c, b)])

    def test_anchor_integrity_rejected(self):
        anchor = deepcopy(self.anchor)
        anchor["original_model"]["operations"]["add"]["ratio_median"] = 0.1
        with self.assertRaises(est.EstimateRejected):
            est.validate_anchor(anchor)

    def test_frozen_original_raw_gate_and_source_evidence_rechecks(self):
        self.assertEqual(len(self.anchor["frozen_records"]), 6)
        for row in self.anchor["frozen_records"]:
            checked = est.checked_record(row)
            self.assertEqual(checked["classes"], row["classes"])
            self.assertEqual(checked["raw_evidence"], row["raw_evidence"])
        for item in self.anchor["provenance"]["frozen_files"]:
            self.assertEqual(est.sha(est.ROOT / item["path"]), item["sha256"])

    def test_raw_private_report_reconstructs_every_frozen_operation(self):
        model = self.anchor["original_model"]
        report = est.load(est.ROOT / model["champion_report"])["report"]
        if isinstance(report, str):
            import json
            report = json.loads(report)
        self.assertEqual(report["suite"], self.anchor["champion_suite"])
        self.assertEqual(report["classes"], self.anchor["champion_classes"])
        for sample in model["samples"]:
            for op in est.OPS:
                total = sum(c["submission_ns"] * sample["cell_work"][key]
                            for key, c in report["classes"].items() if key.startswith(op + ":"))
                self.assertAlmostEqual(total, sample["champion_projected_total_ns"][op])

    def test_live_cli_dry_run_cannot_save(self):
        with patch.object(est, "save", side_effect=AssertionError("dry run attempted to write")):
            with contextlib.redirect_stdout(io.StringIO()):
                model = est.main(["--dry-run"])
        self.assertEqual(model["operations"], self.anchor["original_model"]["operations"])

    def test_missing_pair_is_not_silently_omitted(self):
        c, _ = self.pair()
        with self.assertRaises(est.EstimateRejected):
            est.select_pairs([c], [c["run"]], "new-source", self.anchor)
        with self.assertRaises(est.EstimateRejected):
            est.select_pairs([c], [], "new-source", self.anchor)

    def test_real_archived_negative_candidate_uses_its_own_paired_reference(self):
        records = est.load(est.DEFAULT_ANCHOR.parent / "freeze-anchor-public-results.json")["records"]
        source = "d5e3512f95dc938db6d41f63745d8bf777cb1f6865c7b4b83a8b9055db2b5b09"
        pairs = est.select_pairs(records, [39961709177], source, self.anchor)
        self.assertEqual(len(pairs), 1)
        result = self.estimate(source, pairs)
        candidate, baseline = pairs[0]
        cell = "bmm:dense"
        expected = (candidate["classes"][cell]["submission_ns"] / candidate["classes"][cell]["incumbent_ns"]) / (baseline["classes"][cell]["submission_ns"] / baseline["classes"][cell]["incumbent_ns"])
        self.assertAlmostEqual(result["cell_relative_delta_median"][cell], expected)
        self.assertGreater(result["operations"]["bmm"]["ratio_median"], self.anchor["original_model"]["operations"]["bmm"]["ratio_median"])


if __name__ == "__main__":
    unittest.main(verbosity=2)
