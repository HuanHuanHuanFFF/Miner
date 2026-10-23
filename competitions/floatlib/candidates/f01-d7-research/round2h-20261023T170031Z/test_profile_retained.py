"""Static C rewriting/parser/prior-gate tests; never compile or run Lean/Linux."""
from copy import deepcopy
import importlib.util
import json
from pathlib import Path
import shlex
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


prof = module("retained_prof_test", HERE / "profile-retained.py")
entry = module("retained_entry_test", HERE / "profile-retained-entry.py")
FIXTURE = ROOT / "competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39945391484/download-8f572f9d52f14db8ab7c867729396308/diagnostics/f01-d7-public-suite/public-suite"


def log_for(mapping, detail=1):
    lines = []
    cores = directs = 0
    for expected in mapping:
        cores += expected["expected_route"] == 2
        directs += expected["expected_route"] == 1
        values = {k: 0 for k in prof.FIELDS}
        values.update(call=expected["call"], detail=detail, route=expected["expected_route"],
                      core=cores, direct=directs, rows=expected["expected_rows"], dot_calls=expected["expected_dot_calls"])
        lines.append("FL_CALL " + " ".join(k + "=" + str(values[k]) for k in prof.FIELDS))
    lines.append(f"FL_END bmm_calls={len(mapping)} core_calls={cores} direct_calls={directs}")
    return "\n".join(lines)


class ProfileTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.directory = FIXTURE / "diagnostics/f01-r8-combined-result-guard"
        cls.raw = (cls.directory / "candidate-generated-0.c").read_bytes()
        cls.plan = json.loads((FIXTURE / "public-drawn-plan.json").read_bytes())
        cls.mapping = prof.call_map(cls.plan)

    def setUp(self):
        no_process = patch.object(prof.subprocess, "check_output", side_effect=AssertionError("No Git/compiler in static tests"))
        no_process.start()
        self.addCleanup(no_process.stop)

    def test_fixture_is_exact41_codegen_snapshot(self):
        self.assertEqual(prof.sha(self.raw), prof.FIXTURE_C)
        rows = json.loads((self.directory / "candidate-c-index.json").read_bytes())
        row = next(r for r in rows if r["module"] == "Submission")
        self.assertEqual(row["sha256"], prof.FIXTURE_C)
        self.assertEqual(row["kernel_sha256"], prof.PARENT)

    def test_every_bmm_and_core_real_return_has_probe(self):
        text, coverage = prof.instrument(self.raw.decode())
        for symbol, count, marker in ((prof.BMM, 3, "fl_ret_emit(fl_start);"),
                                      (prof.CORE, 4, "fl_ret_nativeA_ns+=fl_a-fl_start; fl_ret_packB_ns+=fl_b-fl_a;"),
                                      (prof.DIRECT, 1, "fl_ret_direct_ns+=FL_STAGE_NOW()-fl_start;"),
                                      (prof.REPLAY, 1, "fl_ret_replay_ns+=FL_STAGE_NOW()-fl_start;")):
            body = prof.function(text, symbol).group()
            self.assertEqual(len(prof.RETURN.findall(body)), count)
            for ret in prof.RETURN.finditer(body):
                self.assertTrue(body[:ret.start()].rstrip().endswith(marker), symbol)
        self.assertEqual(coverage["functions"][prof.DOT]["real_returns"], 2)
        self.assertTrue(coverage["all_real_returns_checked"])

    def test_counter_control_is_identical_except_internal_timer_switches(self):
        detailed, _ = prof.instrument(self.raw.decode())
        control, _ = prof.instrument(self.raw.decode(), False)
        self.assertEqual(detailed.replace("#define FL_DETAIL 1", "#define FL_DETAIL 0").replace("#define FL_STAGE_NOW() fl_ret_now()", "#define FL_STAGE_NOW() 0ULL"), control)
        self.assertIn("fl_ret_now(); fl_ret_bmm_calls++", control)

    def test_fixture_plan_maps_all_routes_and_three_phases(self):
        self.assertEqual(len(self.mapping), 137)
        self.assertEqual(sum(x["expected_route"] == 1 for x in self.mapping), 77)
        self.assertEqual(sum(x["expected_route"] == 2 for x in self.mapping), 60)
        self.assertEqual({p: sum(x["phase"] == p for x in self.mapping) for p in ("timed", "checksum", "raw")}, {"timed": 102, "checksum": 34, "raw": 1})
        for row in self.mapping:
            self.assertEqual(row["route_name"] == "direct", row["n"] <= 4 or row["p"] <= 2)

    def test_zero_times_are_valid_both_harness_modes(self):
        for detail in (0, 1):
            self.assertEqual(len(prof.parse_calls(log_for(self.mapping, detail), self.mapping, detail)), 137)

    def test_missing_call_extra_end_and_truncated_function_rejected(self):
        log = log_for(self.mapping)
        lines = log.splitlines()
        for bad in ("\n".join(lines[1:]), log + "\n" + lines[-1]):
            with self.assertRaises(RuntimeError):
                prof.parse_calls(bad, self.mapping)
        body = prof.function(self.raw.decode(), prof.BMM).group()
        with self.assertRaises(RuntimeError):
            prof.balanced(body[:body.rfind("}")])

    def test_route_counter_rows_and_output_dot_count_mismatch_rejected(self):
        log = log_for(self.mapping)
        first = self.mapping[0]
        changes = [("route=" + str(first["expected_route"]), "route=9"),
                   ("core=1", "core=999"), ("direct=1", "direct=999"),
                   ("rows=" + str(next(x["expected_rows"] for x in self.mapping if x["expected_route"] == 2)), "rows=999999"),
                   ("dot_calls=" + str(next(x["expected_dot_calls"] for x in self.mapping if x["expected_route"] == 1)), "dot_calls=999999")]
        for before, after in changes:
            with self.subTest(before=before), self.assertRaises(RuntimeError):
                prof.parse_calls(log.replace(before, after, 1), self.mapping)

    def test_negative_residual_or_overlapping_replay_exceeds_total_rejected(self):
        log = log_for(self.mapping)
        for before, after in (("direct_ns=0", "direct_ns=1"), ("replay_ns=0", "replay_ns=1")):
            with self.assertRaises(RuntimeError):
                prof.parse_calls(log.replace(before, after, 1), self.mapping)

    def test_changed_c_or_double_instrumentation_rejected(self):
        with self.assertRaises(RuntimeError):
            prof.instrument(self.raw.decode() + "\n")
        changed, _ = prof.instrument(self.raw.decode())
        with self.assertRaises(RuntimeError):
            prof.instrument(changed)

    def test_invalid_plan_duplicate_case_or_zero_dimension_rejected(self):
        for change in ("duplicate", "zero"):
            plan = deepcopy(self.plan)
            if change == "duplicate":
                plan["cases"].append(deepcopy(plan["cases"][0]))
            else:
                next(c for c in plan["cases"] if c["kernel"] == "bmm")["n"] = 0
            with self.assertRaises(RuntimeError):
                prof.call_map(plan)

    def prior_gate(self):
        kernel = Path("synthetic-candidate/Kernel.lean")
        verdict = {"passed": True, "mode": "gate", "slot": "full", "stage": "score", "submission": kernel.parent.name,
                   "seed": 825, "rounds": [[100, 100]] * 25, "suite": {"sha256": entry.SUITE}, "classes": {str(i): {} for i in range(26)},
                   "reference_complete": True, "incumbent_failed": False, "exhausted": False,
                   "verifier_fingerprint": "fixed", "verifier_fingerprint_end": "fixed"}
        raw = json.dumps(verdict).encode()
        summary = {"complete": True, "rounds": 25, "pairs": 500000, "seed": 825, "suite_sha256": entry.SUITE, "official_commit": entry.HEAD,
                   "results": [{"candidate": kernel.parent.name, "kernel_sha256": entry.PARENT,
                                "verdict_sha256": entry.sha(raw), "full_gate": True, "exit_code": 0, "validation_mode": "full-gate"}]}
        return kernel, raw, summary

    def test_entry_requires_hash_bound_original_full_gate_and_summary(self):
        kernel, raw, summary = self.prior_gate()
        result = entry.verify_original(kernel, raw, json.dumps(summary).encode(), 825)
        self.assertTrue(result["original_gate_passed"])
        for field, value in (("kernel_sha256", "wrong-source"), ("verdict_sha256", "wrong-verdict"), ("full_gate", False)):
            changed = deepcopy(summary)
            changed["results"][0][field] = value
            with self.assertRaises(RuntimeError):
                entry.verify_original(kernel, raw, json.dumps(changed).encode(), 825)
        with self.assertRaises(RuntimeError):
            entry.verify_original(kernel, raw, json.dumps(summary).encode(), 999)

    def test_full_profile_harness_with_fake_build_and_benchmark_io(self):
        # Runs the entire orchestration without starting Git, clang or a binary.
        with tempfile.TemporaryDirectory(prefix=".retained-profile-test-", dir=HERE) as directory:
            task = Path(directory).resolve()
            self.assertEqual(task.parent, HERE.resolve())
            official, upper, logical = task / "official", task / "layer/upper", task / "logical-build"
            for folder in (official / "suites", upper / "ir", upper / "bin"):
                folder.mkdir(parents=True)
            cpath, obj, binary = upper / "ir/Submission.c", upper / "ir/Submission.o", upper / "bin/benchFull"
            cpath.write_bytes(self.raw)
            obj.write_bytes(b"original-object")
            binary.write_bytes(b"original-binary")
            compiler = task / "clang"
            compiler.write_bytes(b"fake-compiler-never-executed")
            generator, suite, gate_path = official / "benchmark_suite.py", official / "suites/public-v2.json", official / "gate.py"
            for f in (generator, suite, gate_path):
                f.write_bytes(b"fake-pinned-input")
            compile_argv = [str(compiler), "-c", str(logical / "ir/Submission.c"), "-o", str(logical / "ir/Submission.o")]
            link_argv = [str(compiler), str(logical / "ir/Submission.o"), "-o", str(logical / "bin/benchFull")]
            (upper / "build.trace").write_text(json.dumps({"log": [{"message": ".> " + shlex.join(a)} for a in (compile_argv, link_argv)]}), encoding="utf-8")
            kernel = ROOT / "competitions/floatlib/candidates/f01-r8-combined-result-guard/Kernel.lean"
            fake = SimpleNamespace(_SANDBOX=True, STAGES=[("statement", None)], _PAIRS=500000, WORK=kernel,
                                   HERE=official, LAYER=task / "layer", BUILD=logical, _BENCH_CPU="",
                                   _BUILD_MEMORY_MB=1000, _BENCH_MEMORY_MB=1000)
            fake.benchmark_suite = SimpleNamespace(__file__=str(generator), load=lambda p: None,
                                                   make_plan=lambda spec, seed, pairs: deepcopy(self.plan))
            commands = []
            state = {"mode": None}
            def execute(argv, cap, **kwargs):
                commands.append(argv)
                if "--version" in argv:
                    return 0, "synthetic clang version; not a real compiler invocation"
                if "-c" in argv:
                    current = cpath.read_bytes()
                    state["mode"] = 0 if b"#define FL_DETAIL 0" in current else 1
                    obj.write_bytes(b"FL_CALL call=" + prof.sha(current).encode())
                    return 0, "synthetic compile"
                if argv == link_argv:
                    binary.write_bytes(obj.read_bytes() + b"binary")
                    return 0, "synthetic link"
                cells = "\n".join(f"{c['name']} {str(c['timed']).lower()} 1000 12345" for c in self.plan["cases"])
                return 0, cells + ("\n" + log_for(self.mapping, state["mode"]) if state["mode"] is not None else "")
            fake.run = execute
            original_sha = prof.file_sha
            pinned = {generator: prof.GENERATOR_SHA, suite: prof.SUITE_SHA, gate_path: prof.GATE_SHA}
            with patch.object(prof.subprocess, "check_output", return_value=prof.HEAD):
                with patch.object(prof, "file_sha", side_effect=lambda p: pinned.get(p) or original_sha(p)):
                    result = prof.run(fake, kernel, task / "results", self.plan, 825)
            self.assertTrue(result["complete"])
            self.assertEqual(len(result["measurements"]), 3)
            self.assertEqual(len(result["measurements"][0]["call_overhead"]), 137)
            self.assertTrue((task / "results/profile-retained-harness-control.c").exists())
            self.assertEqual(sum("-c" in a for a in commands), 2)
            self.assertEqual(result["official_gate_status"], "NOT_RUN_BY_THIS_MODULE")


if __name__ == "__main__":
    unittest.main(verbosity=2)
