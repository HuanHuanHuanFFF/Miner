"""Optional same-process relative timing diagnostics, separate from paired results.

The unmodified pinned engine loads incumbent, fast3 and up to three requested
methods in each process. The non-incumbent order is reversed in the second
process. No request in spec.interleaved_names means no output/build operations.
"""
from __future__ import annotations

import dataclasses
import hashlib
import inspect
import json
import math
import os
from pathlib import Path
import re
import statistics
import sys

ROOT = Path(__file__).resolve().parents[1]
BASELINE = "r3-432-fast3"
PREFIX = "INTERLEAVED_DIAGNOSTIC "
PINNED = {
    "validator/bench/driver.py": "8b29e832a5849c9e97649b390496dcda12c3ed081c39c0bf4a1c94d593f827e3",
    "validator/measure/src/main.rs": "ea4d6378fb0c03681488e4471a97ae001aa0dd3a61a30e9912606d5c4bd7adaa",
}
SCOPE = ("auxiliary same-process public relative performance; official multi-method engine/encoder/build/sandbox unchanged; "
         "method grouping/order differs from official per-candidate paired primary results; no Lean, gate, admission, rank or reward claim")


def digest(data):
    return hashlib.sha256(data).hexdigest()


def save(path, value):
    path.write_text(json.dumps(value, indent=2, ensure_ascii=False, allow_nan=False) + "\n", encoding="utf-8")


def requested():
    label = os.environ["ROUND4_SPEC"]
    if not re.fullmatch(r"[a-z0-9-]{1,48}", label):
        raise ValueError("Invalid ROUND4_SPEC")
    path = ROOT / "evidence/round4" / f"{label}.json"
    data = path.read_bytes()
    spec = json.loads(data)
    names = spec.get("interleaved_names")
    if names is None or names == []:
        return None
    if not isinstance(names, list) or not 1 <= len(names) <= 3 or len(set(names)) != len(names):
        raise ValueError("interleaved_names must be one to three distinct spec names")
    entries = spec["entries"]
    by = {e["name"]: e for e in entries}
    if len(by) != len(entries) or BASELINE not in by:
        raise ValueError("Spec must contain unique entries and fast3")
    if BASELINE in names or "incumbent" in names or any(n not in by for n in names):
        raise ValueError("Request only spec candidates; incumbent/fast3 are included automatically")
    for name in [BASELINE, *names]:
        if not isinstance(name, str) or not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9._-]{0,63}", name):
            raise ValueError("Unsafe method name")
    chosen = [by[n] for n in [BASELINE, *names]]
    return label, digest(data), chosen


def source_snapshot(entries):
    result = {}
    for entry in entries:
        path = (ROOT / entry["path"]).resolve()
        if not path.is_relative_to(ROOT.resolve()):
            raise ValueError("Spec source outside repository")
        if set(entry["hashes"]) != {"parse.rs", "Parse.lean"}:
            raise ValueError("Spec needs exactly parser/proof hashes")
        hashes = {}
        for filename in ("parse.rs", "Parse.lean"):
            data = (path / filename).read_bytes()
            if not 0 < len(data) <= 524288:
                raise ValueError("Candidate parser/proof size invalid")
            hashes[filename] = digest(data)
        if hashes != entry["hashes"]:
            raise ValueError(f"Spec source/proof hash mismatch: {entry['name']}")
        result[entry["name"]] = {"path": entry["path"], "hashes": hashes}
    return result


def check_workspace(workspace, parent):
    """Only a unique direct child created by the driver can be cleaned up."""
    w, p = workspace.resolve(), parent.resolve()
    if w == p or w.parent != p or not w.is_relative_to(p) or workspace.is_symlink():
        raise ValueError("Unexpected build workspace; refusing cleanup")
    return w


def median(method, field="total_s"):
    samples = [r[field] for r in method["reps"] if r["phase"] == "measured"]
    if len(samples) != 11 or any(v is None or not math.isfinite(v) or v < 0 for v in samples):
        raise ValueError("Incomplete/invalid measured samples")
    if field == "total_s" and any(v <= 0 for v in samples):
        raise ValueError("Nonpositive total timing")
    return statistics.median(samples)


def validate_raw(raw, order, inputs, source_hashes, library_hashes, incumbent):
    if not raw or raw[0].get("kind") != "meta":
        raise ValueError("Missing engine metadata")
    meta = raw[0]
    if meta.get("schema_version") != 4:
        raise ValueError("Expected the pinned v4 timing schema")
    if set(meta["methods"]) != set(order) or meta["warmup_rounds"] != 1 or meta["measured_rounds"] != 11:
        raise ValueError("Engine method/repetition set differs from request")
    for name in order:
        m = meta["methods"][name]
        if m["external"] or m["source_sha256"] != source_hashes[name] or m["lib_sha256"] != library_hashes[name]:
            raise ValueError(f"Loaded source/library mismatch: {name}")
    files = [r for r in raw[1:] if r.get("kind") == "file"]
    if len(files) != 28 or len({r["file"] for r in files}) != 28 or {r["file"] for r in files} != set(inputs):
        raise ValueError("Expected exactly the 28 public files")
    for row in files:
        expected = inputs[row["file"]]
        if row["sha256"] != expected["sha256"] or row["raw_bytes"] != expected["bytes"] or set(row["methods"]) != set(order):
            raise ValueError("File identity or measured method set differs")
        positions = []
        for name in order:
            m = row["methods"][name]
            if m["errors"] or m["deterministic"] is not True:
                raise ValueError(f"Roundtrip/determinism failure: {name}/{row['file']}: {m['errors']}")
            if any(m[k] is None for k in ("tokens", "tokens_sha256", "output_bytes", "output_sha256")):
                raise ValueError("Missing output/token identity")
            warm = [r for r in m["reps"] if r["phase"] == "warmup"]
            timed = [r for r in m["reps"] if r["phase"] == "measured"]
            if len(warm) != 1 or len(timed) != 11:
                raise ValueError("Incomplete warmup/measured rounds")
            median(m)
            for rep in m["reps"]:
                positions.append((rep["order_index"], name, rep["phase"]))
        # Metadata uses a sorted map; actual raw repetition indices certify CLI order.
        actual = [n for _, n, _ in sorted(positions)]
        if actual != order * 12:
            raise ValueError("Engine execution order differs from CLI order")
        if any(phase != ("warmup" if i < len(order) else "measured")
               for i, (_, _, phase) in enumerate(sorted(positions))):
            raise ValueError("Warmup/measured ordering differs")
    if incumbent not in order:
        raise ValueError("Incumbent absent")
    return files


def summarize(files, order, incumbent):
    base_axis = statistics.mean(median(r["methods"][BASELINE]) / median(r["methods"][incumbent]) for r in files)
    summary = []
    for name in order:
        per_file = []
        for row in files:
            m, base, ref = (row["methods"][n] for n in (name, BASELINE, incumbent))
            per_file.append({
                "file": row["file"], "raw_bytes": row["raw_bytes"], "input_sha256": row["sha256"],
                "total_ratio_to_shared_incumbent": median(m) / median(ref),
                "total_ratio_to_fast3": median(m) / median(base),
                "median_total_s": median(m), "median_parser_s": median(m, "time_s"),
                "median_encoder_s": median(m, "encode_s"), "incumbent_median_total_s": median(ref),
                "output_bytes": m["output_bytes"], "output_byte_delta_vs_fast3": m["output_bytes"] - base["output_bytes"],
                "tokens": m["tokens"], "tokens_equal_to_fast3": m["tokens_sha256"] == base["tokens_sha256"],
                "output_equal_to_fast3": m["output_sha256"] == base["output_sha256"],
            })
        axis = statistics.mean(r["total_ratio_to_shared_incumbent"] for r in per_file)
        summary.append({
            "method": name, "same_process_time_axis": axis,
            "same_denominator_axis_ratio_vs_fast3": axis / base_axis,
            "same_denominator_axis_change_pct_vs_fast3": 100 * (axis / base_axis - 1),
            "mean_file_total_ratio_vs_fast3": statistics.mean(r["total_ratio_to_fast3"] for r in per_file),
            "mean_file_compression_pct": statistics.mean(100 * r["output_bytes"] / r["raw_bytes"] for r in per_file),
            "public_tokens_equal_to_fast3": all(r["tokens_equal_to_fast3"] for r in per_file),
            "public_output_equal_to_fast3": all(r["output_equal_to_fast3"] for r in per_file),
            "files": per_file,
        })
    return summary


def run(config_request, output, report):
    label, spec_hash, entries = config_request
    if os.environ.get("GITHUB_ACTIONS") != "true" or os.environ.get("RUNNER_OS") != "Linux" or sys.platform != "linux":
        raise RuntimeError("Interleaving is CI-only on the temporary Linux runner")
    if os.environ.get("GITHUB_REPOSITORY") != "HuanHuanHuanFFF/Miner":
        raise RuntimeError("Unexpected repository")
    upstream = Path(os.environ["DEFLATE_ROOT"]).resolve()
    report.update({"spec": label, "spec_sha256": spec_hash, "sources_before": source_snapshot(entries), "phases": []})
    trusted = {}
    for relative, expected in PINNED.items():
        observed = digest((upstream / relative).read_bytes())
        if observed != expected:
            raise RuntimeError(f"Pinned multi-method API changed: {relative}")
        trusted[relative] = observed
    sys.path.insert(0, str(upstream / "validator"))
    from bench import corpora, driver
    from bench.results import INCUMBENT, parse as parse_results
    from sandbox import bwrap
    if Path(driver.__file__).resolve() != (upstream / "validator/bench/driver.py").resolve():
        raise RuntimeError("Unexpected driver module")
    api = {"_make_workspace": ["config", "candidates"], "_generate": ["config", "workspace", "candidates"],
           "_build": ["config", "workspace", "crates"], "_rustc_version": ["config", "workspace", "crate"],
           "measure_sandbox": ["config", "workspace", "corpus"], "_cleanup": ["config", "workspace", "keep"]}
    for function, arguments in api.items():
        if list(inspect.signature(getattr(driver, function)).parameters) != arguments:
            raise RuntimeError(f"Pinned driver signature changed: {function}")
    report["pinned_api"] = {"hashes": trusted, "signatures": api,
                            "engine_support": "Args.methods is a vector; each name=crate is loaded, and bench_file iterates methods in CLI order each round"}
    parent = Path(os.environ["RUNNER_TEMP"]).resolve() / "round4-interleaved-build"
    # Match round4's sandbox/resource/build configuration; only its own workspace differs.
    config = dataclasses.replace(driver.Config.from_env(upstream / "validator"), workspace=parent,
                                 cpus=str(min(os.sched_getaffinity(0))), reps=11, warmup=1, bars=False, keep=driver.Keep.NEVER)
    if not config.enabled:
        raise RuntimeError("Refusing unsandboxed optional diagnostics")
    report["sandbox"] = driver.check(config)
    report["benchmark_provenance"] = driver.provenance(config)
    report["resource_config"] = {k: getattr(config, k) for k in ("timeout", "memory_mb", "build_memory_mb", "cpus", "reps", "warmup", "bars", "enabled")}
    immutable = {p: digest(p.read_bytes()) for p in [
        config.engine, config.incumbent_source, config.toolchain,
        config.template / "Cargo.toml", config.template / "lib.rs",
        config.validator / "measure/src/deflate.rs", config.validator / "measure/src/token.rs",
    ]}
    report["official_build_encoder_hashes"] = {str(p.relative_to(upstream)): h for p, h in immutable.items()}
    corpus = corpora.load(config.validator).by_name("corpus-stage1")
    if not corpus.public:
        raise RuntimeError("Refusing held-out corpus")
    inputs = {p.name: {"bytes": p.stat().st_size, "sha256": digest(p.read_bytes())}
              for p in sorted(corpus.path.iterdir()) if p.is_file()}
    if len(inputs) != 28 or any(v["bytes"] <= 0 for v in inputs.values()):
        raise RuntimeError("Public corpus shape differs from 28 nonempty files")
    report["inputs"] = inputs
    candidates = {e["name"]: (ROOT / e["path"]).resolve() / "parse.rs" for e in entries}
    for name in candidates:
        driver._check_name(name)
    workspace = driver._make_workspace(config, candidates)
    workspace = check_workspace(workspace, parent)
    report["build_workspace"] = str(workspace)
    report["cleanup"] = {"policy": "delete only this verified unique driver-created child after success; retain failures until temporary runner disposal; never delete parent/official checkout", "retained": True}
    successful = False
    try:
        crates = driver._generate(config, workspace, candidates)
        source_hashes = {name: digest((crate / "src/parse.rs").read_bytes()) for name, crate in crates.items()}
        for name in candidates:
            if source_hashes[name] != report["sources_before"][name]["hashes"]["parse.rs"]:
                raise RuntimeError("Generated crate source differs")
        report["generated_source_hashes"] = source_hashes
        rustc = driver._rustc_version(config, workspace, crates[INCUMBENT])
        report["rustc_version"] = rustc
        driver._build(config, workspace, crates)
        library_hashes = {name: digest((crate / "target/release/libcandidate.so").read_bytes()) for name, crate in crates.items()}
        report["library_hashes"] = library_hashes
        previous = None
        non_incumbent = list(candidates)
        for phase, group in (("forward", non_incumbent), ("reverse", list(reversed(non_incumbent)))):
            order = [INCUMBENT, *group]
            cmd = [str(config.engine), str(corpus.path), *(f"{n}={crates[n]}" for n in order),
                   "--corpus-name", corpus.name, "--reps", "11", "--warmup", "1", "--rustc-version", rustc, "--no-bars"]
            measured = bwrap.run(driver.measure_sandbox(config, workspace, corpus), cmd, cwd=None, timeout=config.timeout)
            # Preserve the exact complete engine stdout before validation or enrichment.
            (output / f"{phase}-engine.jsonl").write_text(measured.stdout, encoding="utf-8")
            (output / f"{phase}-stderr.txt").write_text(measured.stderr, encoding="utf-8")
            phase_meta = {"phase": phase, "command": cmd, "method_order": order, "returncode": measured.returncode,
                          "engine_stdout_sha256": digest(measured.stdout.encode()), "scope": SCOPE}
            report["phases"].append(phase_meta)
            save(output / f"{phase}-metadata.json", phase_meta)
            if measured.returncode:
                raise RuntimeError(f"{phase}: shared engine returned {measured.returncode}; failure may not be attributable to one method")
            parsed = parse_results(measured.stdout, corpus)
            failures = {name: list(parsed.failures(name)) for name in order if parsed.failures(name)}
            if failures:
                phase_meta["method_failures"] = failures
                save(output / f"{phase}-metadata.json", phase_meta)
                raise RuntimeError(f"{phase}: official roundtrip/determinism/timing failure")
            raw = list(parsed.raw_records)
            rows = validate_raw(raw, order, inputs, source_hashes, library_hashes, INCUMBENT)
            if previous is not None:
                for row in rows:
                    before = previous[row["file"]]
                    for name in order:
                        for key in ("output_bytes", "output_sha256", "tokens", "tokens_sha256"):
                            if before["methods"][name][key] != row["methods"][name][key]:
                                raise RuntimeError(f"Cross-order output/token identity changed: {name}/{row['file']}")
            previous = {r["file"]: r for r in rows}
            phase_meta["status"] = "VALID_AUXILIARY_DIAGNOSTIC"
            phase_meta["summary"] = summarize(rows, order, INCUMBENT)
            phase_meta["worst_spread"] = parsed.worst_spread()
            save(output / f"{phase}-metadata.json", phase_meta)
            print(PREFIX + json.dumps({"phase": phase, "status": phase_meta["status"], "methods": len(order), "files": len(rows)}), flush=True)
        successful = True
    finally:
        report["sources_after"] = source_snapshot(entries)
        if report["sources_after"] != report["sources_before"]:
            successful = False
            raise RuntimeError("Original parser/proof bytes changed")
        for relative, expected in trusted.items():
            if digest((upstream / relative).read_bytes()) != expected:
                successful = False
                raise RuntimeError("Official pinned API source changed")
        for path, expected in immutable.items():
            if digest(path.read_bytes()) != expected:
                successful = False
                raise RuntimeError("Official engine/encoder/build source changed")
        if successful:
            check_workspace(workspace, parent)
            driver._cleanup(config, workspace, keep=False)
            report["cleanup"]["retained"] = workspace.exists()
            if workspace.exists():
                raise RuntimeError("Own workspace cleanup was not confirmed")
    report["status"] = "AUXILIARY_DIAGNOSTIC_OK"


def main():
    report = {"scope": SCOPE, "script_sha256": digest(Path(__file__).read_bytes()), "status": "AUXILIARY_DIAGNOSTIC_FAILED",
              "run_id": os.environ.get("GITHUB_RUN_ID"), "git_sha": os.environ.get("GITHUB_SHA")}
    output = None
    try:
        config_request = requested()
        if config_request is None:
            print(PREFIX + json.dumps({"status": "NOT_REQUESTED", "scope": SCOPE}), flush=True)
            return
        if os.environ.get("GITHUB_ACTIONS") != "true" or os.environ.get("RUNNER_OS") != "Linux" or sys.platform != "linux":
            raise RuntimeError("Interleaving is CI-only; no local build/output directories are created")
        output = Path(os.environ["RUNNER_TEMP"]).resolve() / "round4-receipts/interleaved"
        output.mkdir(parents=True, exist_ok=True)
        run(config_request, output, report)
    except Exception as exc:
        report["failure"] = {"type": type(exc).__name__, "error": str(exc), "detail": getattr(exc, "detail", None)}
        print(PREFIX + json.dumps({"status": report["status"], "failure": report["failure"]}), flush=True)
    finally:
        if output is not None:
            save(output / "summary.json", report)
    print(PREFIX + json.dumps({"status": report["status"], "receipt": "round4-receipts/interleaved/summary.json"}), flush=True)


if __name__ == "__main__":
    main()
