"""Observe the frozen four-byte parent chain without changing its parse decisions."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
PARENT = "candidates/r22-595-chain-halfhead"
EXPECTED = "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275"
CAP = 8
FIELDS = [
    "engine_calls", "queries", "short_queries", "long_queries", "cap_queries",
    "live_prev", "invalid_prev", "prev_same4", "prev_same8", "prev_matches_query8",
    "short_live_prev", "short_duplicate8", "short_parent_wins", "short_parent_extra",
    "long_live_prev", "long_parent_wins", "long_same8_parent_wins", "long_parent_extra",
    "search_queries", "search_steps", "search_invalid_end", "search_cap_unresolved",
    "search_distinct_found", "distinct_same4", "distinct_matches_query8",
    "distinct_improves_primary", "distinct_extra_vs_primary", "distinct_improves_parent",
    "distinct_extra_vs_parent", "short_dup_parent_wins", "cap_parent_wins",
]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


WRAPPER = r'''
// R25 observer only: these counters and extra comparisons never choose a parse result.
use std::sync::atomic::{AtomicU64, Ordering};
PD_CONSTANTS
static R25_PD_COUNTS: [AtomicU64; PD_WIDTH] = [const { AtomicU64::new(0) }; PD_WIDTH];
fn pd_hit(i: usize, value: u64) { R25_PD_COUNTS[i].fetch_add(value, Ordering::Relaxed); }
pub fn r25_pd_take() -> [u64; PD_WIDTH] {
    std::array::from_fn(|i| R25_PD_COUNTS[i].swap(0, Ordering::Relaxed))
}

fn r25_pd_query(s: &[u8], prev: &[u32; 32768], c: usize, c2: usize,
                cw: u64, p: usize, l: usize, d: usize, chosen: usize,
                chosen_d: usize, minl: usize) {
    assert!(c < p && p + 8 <= s.len() && l >= 4 && l <= 258 && chosen >= l && chosen <= 258);
    assert_eq!(cw, pc_be8(s, c));
    pd_hit(PD_QUERIES, 1);
    let short = l < 8;
    let long = l >= 8 && l < 258;
    pd_hit(if short { PD_SHORT_QUERIES } else if long { PD_LONG_QUERIES } else { PD_CAP_QUERIES }, 1);
    let won = chosen > l;
    if won { assert_eq!(chosen_d, p - c2); }
    if short {
        pd_hit(PD_SHORT_PARENT_WINS, won as u64);
        pd_hit(PD_SHORT_PARENT_EXTRA, if won { (chosen - l) as u64 } else { 0 });
    } else if long {
        pd_hit(PD_LONG_PARENT_WINS, won as u64);
        pd_hit(PD_LONG_PARENT_EXTRA, if won { (chosen - l) as u64 } else { 0 });
    } else {
        pd_hit(PD_CAP_PARENT_WINS, won as u64);
        assert!(!won);
    }
    let live = c2 < c && p.wrapping_sub(c2).wrapping_sub(1) < 32768;
    pd_hit(if live { PD_LIVE_PREV } else { PD_INVALID_PREV }, 1);
    if !live { assert!(!won); return; }
    let query = pc_be8(s, p);
    let older = pc_be8(s, c2);
    let same4 = (older >> 32) == (cw >> 32);
    let same8 = older == cw;
    pd_hit(PD_PREV_SAME4, same4 as u64);
    pd_hit(PD_PREV_SAME8, same8 as u64);
    pd_hit(PD_PREV_MATCHES_QUERY8, (older == query) as u64);
    if long {
        pd_hit(PD_LONG_LIVE_PREV, 1);
        if won {
            assert!(same8 && older == query);
            pd_hit(PD_LONG_SAME8_PARENT_WINS, 1);
        }
    }
    if !short { return; }
    pd_hit(PD_SHORT_LIVE_PREV, 1);
    if !same8 { return; }
    assert_ne!(query, cw);
    assert_eq!((chosen, chosen_d), (l, d));
    pd_hit(PD_SHORT_DUPLICATE8, 1);
    pd_hit(PD_SHORT_DUP_PARENT_WINS, won as u64);
    pd_hit(PD_SEARCH_QUERIES, 1);
    // At most eight extra old-chain links after the already-tested duplicate c2.
    // The frozen parser still uses its original depth1 result, never this diagnostic.
    let mut node = c2;
    for _ in 0..PD_CAP {
        let next = prev[node % 32768] as usize;
        pd_hit(PD_SEARCH_STEPS, 1);
        if next >= node || p.wrapping_sub(next).wrapping_sub(1) >= 32768 {
            pd_hit(PD_SEARCH_INVALID_END, 1);
            return;
        }
        node = next;
        let word = pc_be8(s, node);
        if word != cw {
            pd_hit(PD_SEARCH_DISTINCT_FOUND, 1);
            pd_hit(PD_DISTINCT_SAME4, ((word >> 32) == (query >> 32)) as u64);
            pd_hit(PD_DISTINCT_MATCHES_QUERY8, (word == query) as u64);
            let cap = (s.len() - p).min(258);
            let m = pc_common_from(s, node, p, cap, 0);
            let better_primary = m > l && m >= minl;
            let better_parent = m > chosen && m >= minl;
            pd_hit(PD_DISTINCT_IMPROVES_PRIMARY, better_primary as u64);
            pd_hit(PD_DISTINCT_EXTRA_VS_PRIMARY, if better_primary { (m - l) as u64 } else { 0 });
            pd_hit(PD_DISTINCT_IMPROVES_PARENT, better_parent as u64);
            pd_hit(PD_DISTINCT_EXTRA_VS_PARENT, if better_parent { (m - chosen) as u64 } else { 0 });
            return;
        }
    }
    // No peek beyond the cap: unresolved does not imply no different prefix exists.
    pd_hit(PD_SEARCH_CAP_UNRESOLVED, 1);
}
'''


def instrument(raw):
    assert sha(raw) == EXPECTED
    original = raw.decode()
    a = original.index("pub fn pc_run1c<const H: usize>")
    b = original.index("/// Structured binaries (class 3)", a)
    before = original[a:b]
    after = once(before, "    let n = input.len();",
        "    if km == 4294967295 && dp == 1 { pd_hit(PD_ENGINE_CALLS, 1); }\n    let n = input.len();")
    call = "                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);"
    after = once(after, call, call + "\n                if km == 4294967295 && dp == 1 { r25_pd_query(input, &prev, c, cl, cw, p, f.0, f.1, g.0, g.1, minl); }")
    constants = "\n".join(f"const PD_{name.upper()}: usize = {i};" for i, name in enumerate(FIELDS))
    constants += f"\nconst PD_WIDTH: usize = {len(FIELDS)};\nconst PD_CAP: usize = {CAP};"
    wrapper = WRAPPER.replace("PD_CONSTANTS", constants)
    observed = original[:a] + after + original[b:] + wrapper
    assert observed.removesuffix(wrapper).replace(after, before, 1).encode() == raw
    assert "pc_run1c::<32768>(input,out,4,0,1000000,4294967295,1,4)" in observed
    assert "pc_run1c::<32768>(input,out,6,0,1000000,4294967295,1,4)" in observed
    return observed.encode()


def check_counts(v):
    assert set(v) == set(FIELDS) and all(isinstance(x, int) and x >= 0 for x in v.values())
    assert v["queries"] == v["short_queries"] + v["long_queries"] + v["cap_queries"]
    assert v["queries"] == v["live_prev"] + v["invalid_prev"]
    assert v["prev_same8"] <= v["prev_same4"] <= v["live_prev"]
    assert v["prev_matches_query8"] <= v["live_prev"]
    assert v["short_duplicate8"] <= v["short_live_prev"] <= v["short_queries"]
    assert v["short_parent_wins"] <= v["short_live_prev"]
    assert v["long_parent_wins"] == v["long_same8_parent_wins"] <= v["long_live_prev"] <= v["long_queries"]
    assert v["long_parent_wins"] <= v["long_parent_extra"] <= 250 * v["long_parent_wins"]
    assert v["short_parent_wins"] <= v["short_parent_extra"] <= 254 * v["short_parent_wins"]
    assert v["short_dup_parent_wins"] == v["cap_parent_wins"] == 0
    assert v["search_queries"] == v["short_duplicate8"]
    assert v["search_queries"] == v["search_invalid_end"] + v["search_cap_unresolved"] + v["search_distinct_found"]
    assert v["search_queries"] <= v["search_steps"] <= CAP * v["search_queries"]
    assert v["distinct_matches_query8"] <= v["distinct_improves_primary"] <= v["distinct_same4"] <= v["search_distinct_found"]
    assert v["distinct_improves_parent"] == v["distinct_improves_primary"]
    assert v["distinct_extra_vs_parent"] == v["distinct_extra_vs_primary"]
    assert v["distinct_improves_primary"] <= v["distinct_extra_vs_primary"] <= 254 * v["distinct_improves_primary"]


def captured(command, logfile, timeout):
    try:
        p = subprocess.run(command, capture_output=True, text=True, timeout=timeout)
        logfile.write_text(p.stdout + p.stderr)
    except subprocess.TimeoutExpired as exc:
        def decode(v): return v.decode(errors="replace") if isinstance(v, bytes) else (v or "")
        logfile.write_text(decode(exc.stdout) + decode(exc.stderr) + f"\nTIMEOUT after {timeout}s\n")
        raise
    if p.returncode:
        raise RuntimeError(f"exit={p.returncode}; see {logfile.name}")
    return p


def self_check():
    source = ROOT / PARENT / "parse.rs"
    raw = source.read_bytes()
    observed = instrument(raw)
    assert source.read_bytes() == raw
    assert len(FIELDS) == len(set(FIELDS))
    check_counts(dict.fromkeys(FIELDS, 0))
    example = dict.fromkeys(FIELDS, 0)
    example.update(engine_calls=1, queries=2, short_queries=1, long_queries=1,
        live_prev=2, prev_same4=2, prev_same8=2, prev_matches_query8=1,
        short_live_prev=1, short_duplicate8=1, long_live_prev=1, long_parent_wins=1,
        long_same8_parent_wins=1, long_parent_extra=20, search_queries=1,
        search_steps=2, search_distinct_found=1, distinct_same4=1, distinct_matches_query8=1,
        distinct_improves_primary=1, distinct_extra_vs_primary=8,
        distinct_improves_parent=1, distinct_extra_vs_parent=8)
    check_counts(example)
    rejected = []
    for key in ("search_steps", "short_dup_parent_wins", "long_same8_parent_wins", "distinct_extra_vs_parent"):
        invalid = example.copy()
        invalid[key] = 99
        try: check_counts(invalid)
        except AssertionError: rejected.append(key)
        else: raise AssertionError("malformed counters accepted: " + key)
    report = {"status": "VERIFIED_LOCAL_SOURCE_REVERSAL_AND_COUNTER_SCHEMA_ONLY",
        "source_sha256": sha(raw), "observer_sha256": sha(observed), "observer_bytes": len(observed),
        "cap": CAP, "fields": FIELDS, "frozen_source_unchanged": True,
        "valid_schema_examples": ["zero", "short_duplicate_exposes_distinct_and_long_same_prefix_win"],
        "invalid_schema_examples_rejected": rejected, "rust_compile": "NOT_RUN", "native_token_decode": "NOT_RUN"}
    out = ROOT / "evidence/round25/sol/prefix-diversity-counts-selfcheck.json"
    out.write_bytes((json.dumps(report, indent=2) + "\n").encode())
    print(json.dumps({k: v for k, v in report.items() if k != "fields"}, indent=2))


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    from round4 import validate
    spec = validate(os.environ["ROUND4_SPEC"])
    entry = next(e for e in spec["entries"] if e["path"] == PARENT)
    frozen = ROOT / PARENT / "parse.rs"
    raw = frozen.read_bytes()
    assert sha(raw) == EXPECTED == entry["hashes"]["parse.rs"]
    build = Path(os.environ["RUNNER_TEMP"]) / "r25-prefix-diversity-counts-build"
    out = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/r25-prefix-diversity-counts"
    build.mkdir(); out.mkdir(parents=True)
    observer = instrument(raw)
    observed = build / "observed.rs"; observed.write_bytes(observer)
    harness = importlib.import_module("research-round13-counts").HARNESS
    harness = harness.replace("FROZEN", str(frozen)).replace("OBSERVED", str(observed))
    harness = harness.replace("observed::r13_take()", "observed::r25_pd_take()").replace("R13_COUNT", "R25_PD_COUNT")
    driver = build / "main.rs"; driver.write_text(harness)
    (out / "observer.rs").write_bytes(observer); (out / "harness.rs").write_text(harness)
    result = {"status": "STARTED_UNTIMED_PARENT_TRAJECTORY_OBSERVER", "run_id": os.environ["GITHUB_RUN_ID"],
        "git_sha": os.environ["GITHUB_SHA"], "batch": os.environ["ROUND4_SPEC"], "parent": entry["name"],
        "source_hashes": entry["hashes"], "observer_sha256": sha(observer), "harness_sha256": sha(harness.encode()),
        "fields": FIELDS, "additional_old_chain_step_cap": CAP,
        "scope": "Frozen parent trajectory, original four-byte depth1 PC routes only. The original chosen result drives every parse step; extra read-only comparisons/atomics never modify tables or results. Counts are untimed, local forward-match lengths, not compressed savings or a new candidate.",
        "cap_limit": "Eight extra old-chain links after the already-tested same8 predecessor. Cap exhaustion is unresolved, not absence of a different prefix.",
        "zero_limit": "Position0 may be a valid source; validity is strict decreasing timestamp plus actual window, never a zero/empty assumption."}
    report = out / "counts.json"; report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    binary = build / "counts"
    try:
        result["phase"] = "compile"
        captured(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(driver), "-o", str(binary)], out / "compile.log", 180)
        result["binary_sha256"] = sha(binary.read_bytes()); result["phase"] = "run"
        corpus = Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1"
        run = captured([str(binary), str(corpus)], out / "run.log", 240)
        rows = []
        for line in run.stdout.splitlines():
            if not line.startswith("R25_PD_COUNT "): continue
            _, name, size, *values = line.split()
            assert len(values) == len(FIELDS)
            data = (corpus / name).read_bytes(); assert len(data) == int(size)
            counters = dict(zip(FIELDS, map(int, values))); check_counts(counters)
            rows.append({"file": name, "raw_bytes": len(data), "input_sha256": sha(data), "counts": counters})
        assert len(rows) == len({r["file"] for r in rows}) == 28
        assert sum(r["raw_bytes"] for r in rows) == 15930000
        totals = {k: sum(r["counts"][k] for r in rows) for k in FIELDS}; check_counts(totals)
        assert frozen.read_bytes() == raw
        result.update(status="VERIFIED_UNTIMED_PARENT_OBSERVER_TOKEN_AND_DECODE_EQUAL", phase="complete", rows=rows, totals=totals)
    except Exception as exc:
        result.update(status="FAILED_OR_INCOMPLETE_PARENT_OBSERVER", error_type=type(exc).__name__, error=str(exc))
        report.write_bytes((json.dumps(result, indent=2) + "\n").encode()); raise
    report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    print(json.dumps({"status": result["status"], "totals": totals}, indent=2))


if __name__ == "__main__":
    if sys.argv[1:] == ["--self-check"]: self_check()
    else: main()
