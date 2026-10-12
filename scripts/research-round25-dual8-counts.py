"""Untimed dual8 work/acceptance counts on a temporary, token-equivalent observer."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = "4bfe5d2973ed553922eca1d451912bda5d8ad2d6f16c0ccb83419c5086f20f88"
DOMAINS = ["primary_miss", "primary_len3_7", "primary_len8_257", "primary_len258"]
GLOBAL_FIELDS = ["engine_calls", "initialized_engine_calls", "hash8_calls", "main_long_reads",
                 "main_long_updates", "record_long_updates", "miss_zero_head_hint",
                 "miss_nonzero_out_of_window", "miss_live_nonzero_key_collision", "miss_other"]
DOMAIN_FIELDS = ["queries", "same_head_hint", "later_head_hint", "older_hint", "live_older_hint",
                 "word8_probe_calls", "word8_equal", "accepted", "accepted_match_bytes",
                 "accepted_extra_bytes_vs_primary", "primary_bytes_at_accept", "accepted_distance_sum",
                 "accepted_len8_15", "accepted_len16_31", "accepted_len32_63", "accepted_len64_127",
                 "accepted_len128_257", "accepted_len258"]
FIELDS = GLOBAL_FIELDS + [d + "." + f for d in DOMAINS for f in DOMAIN_FIELDS]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new)


def instrument(raw):
    assert sha(raw) == EXPECTED
    text = raw.decode()
    text = once(text, "pub fn r25_d8_slot(", "pub fn r25_obs_slot_inner(")
    text = once(text, "pub fn r25_d8_link<const H: usize>(", "pub fn r25_obs_link_inner<const H: usize>(")
    text = once(text, "pub fn r25_d8_probe(", "pub fn r25_obs_probe_inner(")
    a = text.index("pub fn r25_d8_run1<const H: usize>")
    body = text[a:]
    body = once(body, "    let n = input.len();", "    r25_hit(0, 1);\n    let n = input.len();")
    body = once(body, "        let mut long = [0u32; 32768];",
                "        let mut long = [0u32; 32768];\n        r25_hit(1, 1);")
    body = once(body, "            let c8 = long[la] as usize;",
                "            let c8 = long[la] as usize;\n            r25_hit(3, 1);")
    body = once(body, "            long[la] = p as u32;",
                "            long[la] = p as u32;\n            r25_hit(4, 1);")
    text = text[:a] + body
    wrapper = r'''
use std::sync::atomic::{AtomicU64, Ordering};
static R25_D8_COUNTS: [AtomicU64; 82] = [const { AtomicU64::new(0) }; 82];
fn r25_hit(i: usize, value: u64) { R25_D8_COUNTS[i].fetch_add(value, Ordering::Relaxed); }
pub fn r25_take() -> [u64; 82] { std::array::from_fn(|i| R25_D8_COUNTS[i].swap(0, Ordering::Relaxed)) }

#[inline(always)]
pub fn r25_d8_slot(s: &[u8], i: usize) -> usize {
    let result = r25_obs_slot_inner(s, i);
    r25_hit(2, 1);
    result
}

#[inline(always)]
pub fn r25_d8_link<const H: usize>(s: &[u8], head: &mut [u32; H], long: &mut [u32; 32768], a: usize, i: usize) {
    r25_hit(5, 1);
    r25_obs_link_inner::<H>(s, head, long, a, i)
}

#[inline(always)]
pub fn r25_d8_probe(s: &[u8], c: usize, cw: u64, c8: usize, p: usize, km: u32) -> (usize, usize) {
    // Extra observer-only primary probe. It is pure and excluded from logical algorithm work counts.
    let first = pc_probe_m(s, c, cw, p, km);
    let result = r25_obs_probe_inner(s, c, cw, c8, p, km);
    assert!(result.0 >= first.0);
    let domain = if first.0 < 3 { 0 } else if first.0 < 8 { 1 } else if first.0 < 258 { 2 } else { 3 };
    let base = 10 + domain * 18;
    r25_hit(base, 1);
    r25_hit(base + 1, (c8 == c) as u64);
    r25_hit(base + 2, (c8 > c) as u64);
    r25_hit(base + 3, (c8 < c) as u64);
    let live = c8 < c && p.wrapping_sub(c8).wrapping_sub(1) < 32768;
    r25_hit(base + 4, live as u64);
    let word_probe = first.0 < 258 && live && p + 8 <= s.len();
    r25_hit(base + 5, word_probe as u64);
    if word_probe {
        // Extra observer loads reproduce the already-tested condition; they are not timed.
        r25_hit(base + 6, (pc_be8(s, c8) == pc_be8(s, p)) as u64);
    }
    if first.0 < 3 {
        if c == 0 { r25_hit(6, 1); }
        else if p.wrapping_sub(c).wrapping_sub(1) >= 32768 { r25_hit(7, 1); }
        else if (((cw ^ pc_be8(s, p)) >> 32) & km as u64) != 0 { r25_hit(8, 1); }
        else { r25_hit(9, 1); }
    }
    if result.0 > first.0 {
        assert!(result.0 >= 8 && word_probe);
        r25_hit(base + 7, 1);
        r25_hit(base + 8, result.0 as u64);
        r25_hit(base + 9, (result.0 - first.0) as u64);
        r25_hit(base + 10, first.0 as u64);
        r25_hit(base + 11, result.1 as u64);
        let bucket = if result.0 < 16 { 0 } else if result.0 < 32 { 1 } else if result.0 < 64 { 2 }
            else if result.0 < 128 { 3 } else if result.0 < 258 { 4 } else { 5 };
        r25_hit(base + 12 + bucket, 1);
    }
    result
}
'''
    assert len(FIELDS) == 82
    return (text + wrapper).encode()


def check_counts(flat):
    assert all(x >= 0 for x in flat.values())
    query_sum = sum(flat[d + ".queries"] for d in DOMAINS)
    assert query_sum == flat["main_long_reads"] == flat["main_long_updates"]
    assert flat["hash8_calls"] == flat["main_long_reads"] + flat["record_long_updates"]
    assert sum(flat[k] for k in GLOBAL_FIELDS[6:]) == flat["primary_miss.queries"]
    for d in DOMAINS:
        v = {f: flat[d + "." + f] for f in DOMAIN_FIELDS}
        assert v["queries"] == v["same_head_hint"] + v["later_head_hint"] + v["older_hint"]
        assert v["accepted"] <= v["word8_equal"] <= v["word8_probe_calls"] <= v["live_older_hint"] <= v["older_hint"]
        assert v["accepted_match_bytes"] == v["accepted_extra_bytes_vs_primary"] + v["primary_bytes_at_accept"]
        assert v["accepted"] == sum(v[f] for f in DOMAIN_FIELDS[12:])
        assert 8 * v["accepted"] <= v["accepted_match_bytes"] <= 258 * v["accepted"]
    assert flat["primary_len258.accepted"] == flat["primary_len258.word8_probe_calls"] == 0


def captured(command, logfile, timeout):
    try:
        p = subprocess.run(command, capture_output=True, text=True, timeout=timeout)
        logfile.write_text(p.stdout + p.stderr)
    except subprocess.TimeoutExpired as exc:
        def decode(value):
            return value.decode(errors="replace") if isinstance(value, bytes) else (value or "")
        logfile.write_text(decode(exc.stdout) + decode(exc.stderr) + f"\nTIMEOUT after {timeout}s\n")
        raise
    if p.returncode:
        raise RuntimeError(f"exit={p.returncode}; see {logfile.name}")
    return p


def self_check():
    frozen = ROOT / "candidates/r25-astra-dual8/parse.rs"
    before = frozen.read_bytes()
    observed = instrument(before)
    assert frozen.read_bytes() == before
    assert len(FIELDS) == len(set(FIELDS)) == 82
    for name in ("slot", "link", "probe"):
        assert observed.count(("pub fn r25_d8_" + name).encode()) == 1
        assert observed.count(("pub fn r25_obs_" + name + "_inner").encode()) == 1
    check_counts(dict.fromkeys(FIELDS, 0))
    example = dict.fromkeys(FIELDS, 0)
    example.update(engine_calls=1, initialized_engine_calls=1, hash8_calls=3,
                   main_long_reads=1, main_long_updates=1, record_long_updates=2,
                   miss_live_nonzero_key_collision=1)
    for field in ("queries", "older_hint", "live_older_hint", "word8_probe_calls", "word8_equal", "accepted", "accepted_len8_15"):
        example["primary_miss." + field] = 1
    example["primary_miss.accepted_match_bytes"] = 12
    example["primary_miss.accepted_extra_bytes_vs_primary"] = 12
    example["primary_miss.accepted_distance_sum"] = 64
    check_counts(example)
    rejected = []
    for key in ("hash8_calls", "miss_other", "primary_miss.accepted_match_bytes"):
        invalid = example.copy()
        invalid[key] += 1
        try:
            check_counts(invalid)
        except AssertionError:
            rejected.append(key)
        else:
            raise AssertionError("malformed counter receipt accepted: " + key)
    report = {"status": "VERIFIED_LOCAL_GENERATION_AND_COUNTER_SCHEMA_ONLY", "source_sha256": sha(before),
              "observer_sha256": sha(observed), "observer_bytes": len(observed), "field_count": len(FIELDS),
              "fields": FIELDS, "compile": "NOT_RUN", "native": "NOT_RUN", "frozen_source_unchanged": True}
    report["counter_schema_preflight"] = {"valid_cases": ["zero", "one_long_match_after_live_key_collision"],
                                           "invalid_cases_rejected": rejected}
    path = ROOT / "evidence/round25/astra/dual8-counts-selfcheck.json"
    path.write_bytes((json.dumps(report, indent=2) + "\n").encode())
    print(json.dumps({k: v for k, v in report.items() if k != "fields"}, indent=2))


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    from round4 import validate
    spec = validate(os.environ["ROUND4_SPEC"])
    entry = next(e for e in spec["entries"] if e["name"] == "r25-astra-dual8")
    frozen = ROOT / entry["path"] / "parse.rs"
    raw = frozen.read_bytes()
    assert sha(raw) == EXPECTED == entry["hashes"]["parse.rs"]
    build = Path(os.environ["RUNNER_TEMP"]) / "r25-dual8-counts-build"
    build.mkdir()
    out = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/r25-dual8-counts"
    out.mkdir(parents=True)
    observed = build / "observed.rs"
    observer = instrument(raw)
    observed.write_bytes(observer)
    original_harness = importlib.import_module("research-round13-counts").HARNESS
    harness = original_harness.replace("FROZEN", str(frozen)).replace("OBSERVED", str(observed))
    harness = harness.replace("observed::r13_take()", "observed::r25_take()").replace("R13_COUNT", "R25_D8_COUNT")
    driver = build / "main.rs"
    driver.write_text(harness)
    # These temporary copies are retained as diagnostic artifacts, never compiled as a candidate.
    (out / "observer.rs").write_bytes(observer)
    (out / "harness.rs").write_text(harness)
    result = {"status": "STARTED_UNTIMED_OBSERVER", "run_id": os.environ["GITHUB_RUN_ID"],
              "git_sha": os.environ["GITHUB_SHA"], "batch": os.environ["ROUND4_SPEC"], "candidate": entry["name"],
              "source_hashes": entry["hashes"], "observer_sha256": sha(observer),
              "harness_sha256": sha(harness.encode()), "fields": FIELDS,
              "scope": "Counts on actual frozen dual8 trajectory only. Extra observer primary probes/word loads/atomics are excluded from logical counts. No measured speed or compressed saving claim.",
              "zero_hint_limit": "c=0 may be the valid position0 or zero initialization; zero-head observations do not prove the table was empty or history has no match.",
              "collision_limit": "Live nonzero current-head prefix mismatch is a current4-byte hash collision, not proof that no older match exists.",
              "coverage_limit": "Accepted match/extra bytes are local lengths, not net decoded coverage, compressed bytes, or full-program savings."}
    report = out / "counts.json"
    report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    binary = build / "counts"
    try:
        result["phase"] = "compile"
        captured(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes",
                  str(driver), "-o", str(binary)], out / "compile.log", 180)
        result["binary_sha256"] = sha(binary.read_bytes())
        result["phase"] = "run"
        corpus = Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1"
        run = captured([str(binary), str(corpus)], out / "run.log", 240)
        rows = []
        for line in run.stdout.splitlines():
            if not line.startswith("R25_D8_COUNT "):
                continue
            _, name, size, *values = line.split()
            assert len(values) == len(FIELDS)
            data = (corpus / name).read_bytes()
            assert len(data) == int(size)
            flat = dict(zip(FIELDS, map(int, values)))
            check_counts(flat)
            rows.append({"file": name, "raw_bytes": len(data), "input_sha256": sha(data),
                         "counts": {k: flat[k] for k in GLOBAL_FIELDS},
                         "domains": {d: {f: flat[d + "." + f] for f in DOMAIN_FIELDS} for d in DOMAINS}})
        assert len(rows) == 28 and len({r["file"] for r in rows}) == 28
        assert sum(r["raw_bytes"] for r in rows) == 15930000
        totals = {"counts": {k: sum(r["counts"][k] for r in rows) for k in GLOBAL_FIELDS},
                  "domains": {d: {f: sum(r["domains"][d][f] for r in rows) for f in DOMAIN_FIELDS} for d in DOMAINS}}
        result.update(status="VERIFIED_UNTIMED_FROZEN_OBSERVER_TOKEN_AND_DECODE_EQUAL", phase="complete", rows=rows, totals=totals)
        assert frozen.read_bytes() == raw
    except Exception as exc:
        result.update(status="FAILED_OR_INCOMPLETE_OBSERVER", error_type=type(exc).__name__, error=str(exc))
        report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
        raise
    report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    print(json.dumps({"status": result["status"], "totals": totals}, indent=2))


if __name__ == "__main__":
    if sys.argv[1:] == ["--self-check"]:
        self_check()
    else:
        main()
