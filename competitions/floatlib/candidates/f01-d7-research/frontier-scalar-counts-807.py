"""Residual scalar routes in exposed807: source models of exact97f BMM and exact3d9 sum.

One checksum pass only. Loads selected existing AST definitions, never dependency
mains/imports, hardware, future plans or compiler tools. Stops once at <=600s and
preserves completed rows/witnesses. The two frontiers are not a compiled combination.
"""
from pathlib import Path
from collections import Counter
from datetime import datetime, timezone
import ast
import argparse
import hashlib
import json
import re
import time
import traceback

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
R = ROOT / "competitions/floatlib/research/astra-collab-20261023-r7"
OUTPUT = HERE / "frontier-scalar-counts-807.json"
PLAN_SHA = "9cc5d7368749c369172b019d66bc4cd8455ae4323d0b9a175bd031f936e78622"
FULL60F = "60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15"
SRC97F = "97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26"
SRC3D9 = "3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576"
M32 = (1 << 32) - 1
COUNT_KEYS = ("ordered_steps", "scalar_add_calls", "scalar_mul_calls",
              "add_nonfinite_cold_calls", "mul_nonfinite_cold_calls",
              "add_raw_nan_selected", "mul_raw_nan_selected",
              "add_no_nan_exceptional_misses", "mul_no_nan_exceptional_misses")


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def label(p):
    return p.relative_to(ROOT).as_posix()


def utc():
    return datetime.now(timezone.utc).isoformat()


def counter():
    return Counter(dict.fromkeys(COUNT_KEYS, 0))


def load_S():
    path = HERE / "scalar-opportunity.py"
    tree = ast.parse(path.read_text(encoding="utf-8"))
    functions = {"require", "sha", "label", "load_functions"}
    constants = {"HERE", "ROOT", "R", "BASE", "PROFILE", "FULL60F", "M32"}
    nodes = [n for n in tree.body if
             isinstance(n, ast.FunctionDef) and n.name in functions or
             isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets)]
    env = {"Path": Path, "hashlib": hashlib, "ast": ast, "__file__": str(path)}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(path), "exec"), env)
    assert set(n.name for n in nodes if isinstance(n, ast.FunctionDef)) == functions
    return env


def classify_sum(u):
    a = u & 0x7fffffff
    if 0x0bffffff <= ((a - 1) & M32):
        if a < 0x7f800000:
            return "table"
        return "infinity" if a == 0x7f800000 else "nan"
    return "low"


def add_call_counts(c, op, a, b, O):
    c["scalar_" + op + "_calls"] += 1
    cold = O["exp"](a) == 255 or O["exp"](b) == 255
    if cold:
        c[op + "_nonfinite_cold_calls"] += 1
        selected = O["choose"](a, b) is not None
        c[op + "_raw_nan_selected"] += selected
        c[op + "_no_nan_exceptional_misses"] += not selected


def sum_frontier(xs, O):
    """3d9: classify original input; native prefix may already be canonicalNaN."""
    acc = 0
    raw_mode = False
    calls = counter()
    stats = Counter()
    witness = None
    for k, u in enumerate(xs):
        if raw_mode:
            stats["suffix_words"] += 1
            if O["snan"](u):
                acc = u | 0x400000
                stats["suffix_snan_replacements"] += 1
            continue
        branch = classify_sum(u)
        assert (branch == "nan") == O["nan"](u)
        stats["prefix_" + branch + "_words"] += 1
        if branch == "nan":
            before = acc
            add_call_counts(calls, "add", acc, u, O)
            calls["ordered_steps"] += 1
            acc = O["add"](acc, u)
            assert O["nan"](acc) and not O["snan"](acc)
            stats["repair_outputs"] += 1
            if O["nan"](before):
                assert before == 0x7fc00000
                stats["repair_with_native_canonical_nan_left"] += 1
                key = "right_snan_overrides_canonical_left" if O["snan"](u) else "canonical_left_keeps_priority_over_right_qnan"
                stats[key] += 1
                witness = {"index": k, "left": hex(before), "right": hex(u), "result": hex(acc), "reason": key}
            raw_mode = True
        else:
            acc = O["canon"](O["add"](O["canon"](acc), O["canon"](u)))
            stats["native_prefix_adds"] += 1
    stats["source_words"] = len(xs)
    stats["no_raw_nan_outputs"] = not raw_mode
    return acc, calls, stats, witness


def dot_models(pairs, O, deadline):
    """Simultaneous old full fold/native pass and97f prefix; each step is mul THEN add."""
    full = native = prefix_result = 0
    old, prefix = counter(), counter()
    active = True
    stats = Counter()
    first = None
    for k, (x, y) in enumerate(pairs):
        if k % 1024 == 0 and time.monotonic() >= deadline:
            raise TimeoutError("600s bounded finite model expired")
        before = full
        product = O["mul"](x, y)
        add_call_counts(old, "mul", x, y, O)
        add_call_counts(old, "add", full, product, O)
        old["ordered_steps"] += 1
        if active:
            add_call_counts(prefix, "mul", x, y, O)
            add_call_counts(prefix, "add", full, product, O)
            prefix["ordered_steps"] += 1
        full = O["add"](full, product)
        np = O["canon"](O["mul"](O["canon"](x), O["canon"](y)))
        native = O["canon"](O["add"](O["canon"](native), np))
        if active:
            prefix_result = full
            if O["nan"](full):
                assert not O["snan"](full)
                active = False
                first = {"index": k, "acc_before": hex(before), "x": hex(x), "y": hex(y),
                         "product": hex(product), "result": hex(full)}
                stats["stop_from_raw_nan_product" if O["nan"](product) else "stop_from_no_nan_invalid_add"] += 1
                if O["nan"](product) and O["choose"](x, y) is None:
                    stats["stop_from_invalid_multiply_product"] += 1
    assert O["nan"](native) == O["nan"](full)
    if O["nan"](native):
        assert prefix_result == full
        stats["raw_replay_outputs"] += 1
        stats["skipped_suffix_steps"] = len(pairs) - prefix["ordered_steps"]
        return full, old, prefix, stats, first
    assert native == full
    return native, counter(), counter(), stats, None


def aggregates(rows, field):
    out = {}
    for timed in (True, False):
        for kernel in ("sum", "bmm"):
            subset = [r for r in rows if r["timed"] == timed and r["kernel"] == kernel]
            total = Counter()
            for r in subset:
                total.update(r[field])
            out[("timed" if timed else "raw") + "_" + kernel] = {
                "cases": len(subset), "outputs": sum(r["outputs"] for r in subset), "counts": dict(total)}
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--max-seconds", type=int, default=600)
    args = ap.parse_args()
    assert 1 <= args.max_seconds <= 600
    started = time.monotonic()
    deadline = started + args.max_seconds
    S = load_S()
    BASE, PROFILE = S["BASE"], S["PROFILE"]
    paths = [HERE / "scalar-opportunity.py", HERE / "scalar-nan-fallback-807.py",
             HERE / "scalar-nan-fallback-807.json", HERE / "scalar-opportunity-807.json",
             R / "public-nonfinite-opportunity.py", R / "nonfinite-oracle.py", R / "upstream/BenchSuite.lean",
             HERE.parent / "f01-d7-direct-nonnan/Kernel.lean",
             HERE.parent / "f01-d7-direct-nonfinite/Kernel.lean",
             HERE.parent / "f01-r7-sum-singlepass-fused-proof1/Kernel.lean",
             BASE / "public-drawn-plan.json", BASE / "f01-d7-direct-nonnan-verdict.json",
             PROFILE / "profile-current-control-0.json"]
    paths += [PROFILE / f"profile-current-instrumented-{i}.json" for i in range(3)]
    cached = {p: p.read_bytes() for p in paths}
    get = lambda p: json.loads(cached[p])
    assert sha(cached[BASE / "public-drawn-plan.json"]) == PLAN_SHA
    for name, expected in [("f01-d7-direct-nonnan", FULL60F), ("f01-d7-direct-nonfinite", SRC97F),
                           ("f01-r7-sum-singlepass-fused-proof1", SRC3D9)]:
        assert sha(cached[HERE.parent / name / "Kernel.lean"]) == expected
    # Exact exported scalar bodies, including nativeMul, remain unchanged in both frontiers.
    bodies = {}
    for name in ("f01-d7-direct-nonnan", "f01-d7-direct-nonfinite", "f01-r7-sum-singlepass-fused-proof1"):
        txt = cached[HERE.parent / name / "Kernel.lean"].decode("utf-8")
        pieces = {}
        for key, pattern in [
            ("add", r"@\[inline\] def add \(x y : Binary32\).*?(?=\ntheorem add_spec)"),
            ("mul", r"@\[inline\] def mul \(x y : Binary32\) : Binary32 :=\s+let ex :=.*?(?=\ntheorem mul_spec)"),
            ("nativeMul", r"@\[inline\] def nativeMul \(x y : Binary32\).*?(?=\ntheorem nativeMul_spec)")]:
            found = re.findall(pattern, txt, re.S)
            assert len(found) == 1, (name, key, len(found))
            pieces[key] = found[0]
        bodies[name] = pieces
    assert len({json.dumps(v, sort_keys=True) for v in bodies.values()}) == 1
    generator = S["load_functions"](cached[R / "public-nonfinite-opportunity.py"], R / "public-nonfinite-opportunity.py",
                                     ("word", "ctz", "element"), ("M64", "M32"))
    O = S["load_functions"](cached[R / "nonfinite-oracle.py"], R / "nonfinite-oracle.py",
                            ("exp", "frac", "nan", "snan", "inf", "zero", "canon", "choose", "unpack", "rounded", "add", "mul"))
    plan = get(BASE / "public-drawn-plan.json")
    old_saved = {r["name"]: r for r in get(HERE / "scalar-nan-fallback-807.json")["cases"]}
    scalar = get(HERE / "scalar-opportunity-807.json")
    assert scalar["complete"] and scalar["all_scalar_checksums_match_actual_lean"]
    assert scalar["inputs_sha256"][label(BASE / "public-drawn-plan.json")] == PLAN_SHA
    logs = {"control": get(PROFILE / "profile-current-control-0.json")}
    logs.update({f"instrumented_{i}": get(PROFILE / f"profile-current-instrumented-{i}.json")["benchmark_rows"] for i in range(3)})
    verdict = get(BASE / "f01-d7-direct-nonnan-verdict.json")
    assert verdict["seed"] == 807 and verdict["passed"] and verdict["stage"] == "score" and len(verdict["rounds"]) == 25
    result = {"status": "RUNNING", "complete": False, "started_at_utc": utc(), "max_seconds": args.max_seconds,
              "analysis_sha256": sha(Path(__file__).read_bytes()), "discovery_seed": 807, "plan_sha256": PLAN_SHA,
              "source_frontiers": {"old60f": FULL60F, "bmm97f": SRC97F, "sum3d9": SRC3D9},
              "inputs_sha256": {label(p): sha(b) for p, b in cached.items()},
              "scalar_export_runtime_bodies_equal": True,
              "scalar_body_sha256": {k: sha(v.encode()) for k, v in bodies["f01-d7-direct-nonnan"].items()},
              "counting": "One checksum pass, seed0. Timed and raw cases separated. Counts are call sites executed by source models, not cycles/time or new binary observations.",
              "native_model": "Existing exact word oracle with canonicalized operands/results, not Float32 hardware execution.",
              "composition": "97f BMM and3d9 sum are separate exact source components; no compiled combination is claimed.",
              "cases": [], "counterexamples": [], "boundary_witnesses": [],
              "new_Lean_fullgate_codegen_timing": "NOT_RUN", "gain": "UNKNOWN"}
    def save():
        result["analysis_seconds"] = time.monotonic() - started
        OUTPUT.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    # Three tiny priority/ordering witnesses, not a new random suite.
    for xs in ([0x7f800000, 0xff800000, 0xffc01234],
               [0x7f800000, 0xff800000, 0xff800011],
               [0x7fc00001, 0xffc00002, 0xff800003]):
        got, _, stats, witness = sum_frontier(xs, O)
        want = 0
        for x in xs:
            want = O["add"](want, x)
        assert got == want
        result["boundary_witnesses"].append({"kind": "sum", "inputs": list(map(hex, xs)), "output": hex(got),
                                            "stats": dict(stats), "priority": witness})
    try:
        for c in plan["cases"]:
            if c["kernel"] not in ("sum", "bmm"):
                continue
            if time.monotonic() >= deadline:
                raise TimeoutError("600s bounded finite model expired")
            n = c["length"] if c["kernel"] == "sum" else c["n"]
            count = c["batch"] if c["kernel"] == "sum" else c["batch"] * c["m"] * c["p"]
            old_total, new_total, details = counter(), counter(), Counter()
            old_trace, new_trace = hashlib.sha256(), hashlib.sha256()
            old_checksum = new_checksum = 0
            witnesses = []
            result["in_progress_case"] = {"name": c["name"], "outputs_completed": 0, "outputs_expected": count}
            if c["kernel"] == "bmm":
                A = [generator["element"](c, i, 0, n) for i in range(c["batch"] * c["m"] * n)]
                B = [generator["element"](c, i, 1, c["p"]) for i in range(c["batch"] * n * c["p"])]
            for q in range(count):
                if time.monotonic() >= deadline:
                    raise TimeoutError("600s bounded finite model expired")
                if c["kernel"] == "sum":
                    xs = [generator["element"](c, q * n + k, 0, n) for k in range(n)]
                    exact = 0
                    local = counter()
                    for u in xs:
                        add_call_counts(local, "add", exact, u, O)
                        local["ordered_steps"] += 1
                        exact = O["add"](exact, u)
                    if O["nan"](exact):
                        old_total.update(local)
                    got, calls, stats, witness = sum_frontier(xs, O)
                else:
                    j, i, b = q % c["p"], (q // c["p"]) % c["m"], q // (c["m"] * c["p"])
                    aa, bb = (b * c["m"] + i) * n, b * n * c["p"] + j
                    pairs = []
                    for k in range(n):
                        ia, ib = aa + k, bb + k * c["p"]
                        assert 0 <= ia < len(A) and 0 <= ib < len(B), "Unexpected default read in exposed807 dimensions"
                        pairs.append((A[ia], B[ib]))
                    got, local, calls, stats, witness = dot_models(pairs, O, deadline)
                    exact = got
                    old_total.update(local)
                    details["A_reads_during_raw_replay"] += calls["ordered_steps"]
                    details["B_reads_during_raw_replay"] += calls["ordered_steps"]
                new_total.update(calls)
                details.update(stats)
                if witness and len(witnesses) < 3:
                    witnesses.append({"output_index": q, **witness})
                if got != exact:
                    result["counterexamples"].append({"case": c["name"], "output_index": q, "got": hex(got), "old": hex(exact)})
                    raise AssertionError("Frontier output word differs")
                old_trace.update(exact.to_bytes(4, "little"))
                new_trace.update(got.to_bytes(4, "little"))
                old_checksum = ((old_checksum ^ exact) * 16777619) & M32
                new_checksum = ((new_checksum ^ got) * 16777619) & M32
                result["in_progress_case"]["outputs_completed"] = q + 1
            anchor = old_saved[c["name"]]
            assert old_checksum == new_checksum == anchor["checksum32"]
            assert old_trace.hexdigest() == new_trace.hexdigest() == anchor["output_words_le_sha256"]
            assert dict(old_total) == anchor["current60f_raw_replay_counts"], c["name"]
            matches = {name: rows[c["name"]]["checksum"] == new_checksum for name, rows in logs.items()}
            assert all(matches.values())
            result["cases"].append({"name": c["name"], "kernel": c["kernel"], "timed": c["timed"],
                "case": c, "outputs": count, "old60f_complete_replay_counts": dict(old_total),
                "frontier_scalar_counts": dict(new_total), "frontier_details": dict(details),
                "checksum32": new_checksum, "actual_Lean_checksum_matches": matches,
                "output_words_le_sha256": new_trace.hexdigest(), "old_output_word_sha_match": True,
                "old60f_counts_exact_match": True, "witnesses": witnesses})
            save()
            print(json.dumps({"case": c["name"], "frontier_add": new_total["scalar_add_calls"],
                              "frontier_mul": new_total["scalar_mul_calls"], "anchors": "4CHECKSUM_AND_OLD_WORD_SHA_MATCH"}), flush=True)
        assert len(result["cases"]) == 70
        result["old60f_totals"] = aggregates(result["cases"], "old60f_complete_replay_counts")
        result["frontier_totals"] = aggregates(result["cases"], "frontier_scalar_counts")
        result["frontier_detail_totals"] = aggregates(result["cases"], "frontier_details")
        reused = []
        for row in scalar["cases"]:
            assert row["name"] in {c["name"] for c in plan["cases"] if c["kernel"] in ("add", "mul")}
            assert all(v["match"] for v in row["checksum_comparisons"].values())
            op, d = row["kernel"], row["counts"]
            counts = counter()
            counts["scalar_" + op + "_calls"] = d["pairs"]
            counts[op + "_nonfinite_cold_calls"] = d["nonfinite_pairs"]
            counts[op + "_raw_nan_selected"] = d["input_nan_pairs"]
            counts[op + "_no_nan_exceptional_misses"] = d["nonfinite_pairs"] - d["input_nan_pairs"]
            reused.append({"name": row["name"], "kernel": op, "timed": row["timed"], "outputs": d["pairs"],
                           "counts": dict(counts), "checksum32": row["checksum32"],
                           "output_words_le_sha256": row["output_words_le_sha256"]})
        assert len(reused) == 86
        result["unchanged_standalone_scalar_cases_reused"] = reused
        result["standalone_scalar_totals"] = {}
        for timed in (True, False):
            for op in ("add", "mul"):
                group = [r for r in reused if r["timed"] == timed and r["kernel"] == op]
                total = counter()
                for row in group:
                    total.update(row["counts"])
                result["standalone_scalar_totals"][("timed" if timed else "raw") + "_" + op] = {
                    "cases": len(group), "counts": dict(total), "source": "Prior807 finite model/checksum anchors; not re-enumerated here."}
        result["checksum_comparisons_tensor"] = 70 * 4
        result["output_word_sha_comparisons"] = 70
        del result["in_progress_case"]
        result["dependencies_unchanged"] = all(p.read_bytes() == b for p, b in cached.items())
        assert result["dependencies_unchanged"]
        result["status"] = "PASS_FINITE_FRONTIER_MODEL_WITH_ACTUAL_PRIOR_CHECKSUM_ANCHORS"
        result["complete"] = True
    except Exception as exc:
        result["status"] = "TIMEOUT_PARTIAL" if isinstance(exc, TimeoutError) else "FAILED_PARTIAL"
        result["error"] = str(exc)
        result["traceback"] = traceback.format_exc()
        save()
        raise
    finally:
        result["completed_at_utc"] = utc()
        save()
    print(json.dumps({"status": result["status"], "seconds": result["analysis_seconds"],
                      "old": result["old60f_totals"], "frontier": result["frontier_totals"],
                      "details": result["frontier_detail_totals"], "standalone": result["standalone_scalar_totals"]}))


if __name__ == "__main__":
    main()

