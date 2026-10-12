"""New observer version: identify main/record origin of accepted long-table hints."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import sys

ROOT = Path(__file__).resolve().parents[1]
BASE = importlib.import_module("research-round25-dual8-counts")
BASE_OBSERVER = "dcf6a6c23708ab00ae17c52aaa571b12fe2be0375a25bb5b04c247dac2fdbe87"
REFERENCE = ROOT / "evidence/round25/38127500920/counts-e-native/diagnostics/r25-dual8-counts/counts.json"
ORIGINS = ["initialized_zero", "main", "record"]
ORIGIN_FIELDS = ["queries", "word8_probe_calls", "word8_equal", "accepted", "accepted_match_bytes",
                 "accepted_extra_bytes_vs_primary", "primary_bytes_at_accept", "accepted_distance_sum"]
EXTRA_FIELDS = [f"{d}.{o}.{f}" for d in BASE.DOMAINS for o in ORIGINS for f in ORIGIN_FIELDS]
FIELDS = BASE.FIELDS + EXTRA_FIELDS


def instrument(raw):
    baseline = BASE.instrument(raw)
    assert BASE.sha(baseline) == BASE_OBSERVER
    text = baseline.decode()
    once = BASE.once
    # The tag array is local to exactly the same engine invocation as the real long table.
    text = once(text, "        let mut long = [0u32; 32768];",
                "        let mut long = [0u32; 32768];\n        let mut origin = [0u8; 32768];")
    text = once(text, "            let c8 = long[la] as usize;",
                "            let c8 = long[la] as usize;\n            let source_origin = origin[la] as usize;")
    text = once(text, "            long[la] = p as u32;",
                "            long[la] = p as u32;\n            origin[la] = 1;")
    text = once(text, "r25_d8_probe(input, c, cw, c8, p, km)",
                "r25_d8_probe(input, c, cw, c8, p, km, source_origin)")
    text = once(text, "pub fn r25_d8_record3<const H: usize>(s: &[u8], head: &mut [u32; H], long: &mut [u32; 32768], ins0:",
                "pub fn r25_d8_record3<const H: usize>(s: &[u8], head: &mut [u32; H], long: &mut [u32; 32768], origin: &mut [u8; 32768], ins0:")
    needle = "r25_d8_link::<H>(s, head, long, "
    assert text.count(needle) == 4
    text = text.replace(needle, "r25_d8_link::<H>(s, head, long, origin, ")
    text = once(text, "r25_d8_link::<H>(input, &mut head, &mut long, pre_slot, q);",
                "r25_d8_link::<H>(input, &mut head, &mut long, &mut origin, pre_slot, q);")
    text = once(text, "r25_d8_record3::<H>(input, &mut head, &mut long, ins,",
                "r25_d8_record3::<H>(input, &mut head, &mut long, &mut origin, ins,")
    text = once(text, "pub fn r25_d8_link<const H: usize>(s: &[u8], head: &mut [u32; H], long: &mut [u32; 32768], a: usize, i: usize) {",
                "pub fn r25_d8_link<const H: usize>(s: &[u8], head: &mut [u32; H], long: &mut [u32; 32768], origin: &mut [u8; 32768], a: usize, i: usize) {")
    text = once(text, "    r25_obs_link_inner::<H>(s, head, long, a, i)\n}",
                "    r25_obs_link_inner::<H>(s, head, long, a, i);\n    origin[r25_obs_slot_inner(s, i)] = 2;\n}")
    # Above uses the uncounted pure slot helper only for observer tags; E logical hash counts stay exact.
    text = once(text, "pub fn r25_d8_probe(s: &[u8], c: usize, cw: u64, c8: usize, p: usize, km: u32) -> (usize, usize) {",
                "pub fn r25_d8_probe(s: &[u8], c: usize, cw: u64, c8: usize, p: usize, km: u32, source_origin: usize) -> (usize, usize) {")
    text = once(text, "    if word_probe {\n        // Extra observer loads reproduce the already-tested condition; they are not timed.\n        r25_hit(base + 6, (pc_be8(s, c8) == pc_be8(s, p)) as u64);\n    }",
                "    let word_equal = word_probe && pc_be8(s, c8) == pc_be8(s, p);\n    r25_hit(base + 6, word_equal as u64);")
    final = """    assert!(source_origin < 3);
    let ob = (domain * 3 + source_origin) * 8;
    r25_origin_hit(ob, 1);
    r25_origin_hit(ob + 1, word_probe as u64);
    r25_origin_hit(ob + 2, word_equal as u64);
    if result.0 > first.0 {
        r25_origin_hit(ob + 3, 1);
        r25_origin_hit(ob + 4, result.0 as u64);
        r25_origin_hit(ob + 5, (result.0 - first.0) as u64);
        r25_origin_hit(ob + 6, first.0 as u64);
        r25_origin_hit(ob + 7, result.1 as u64);
    }
    result
}
"""
    pos = text.index("pub fn r25_d8_probe(")
    text = text[:pos] + once(text[pos:], "    result\n}\n", final)
    text = once(text,
        "pub fn r25_take() -> [u64; 82] { std::array::from_fn(|i| R25_D8_COUNTS[i].swap(0, Ordering::Relaxed)) }",
        "pub fn r25_take() -> [u64; 178] { std::array::from_fn(|i| if i < 82 { R25_D8_COUNTS[i].swap(0, Ordering::Relaxed) } else { R25_D8_ORIGINS[i - 82].swap(0, Ordering::Relaxed) }) }")
    text += """
static R25_D8_ORIGINS: [AtomicU64; 96] = [const { AtomicU64::new(0) }; 96];
fn r25_origin_hit(i: usize, value: u64) { R25_D8_ORIGINS[i].fetch_add(value, Ordering::Relaxed); }
"""
    assert len(FIELDS) == 178 and len(EXTRA_FIELDS) == 96
    return text.encode()


def check_counts(flat):
    BASE.check_counts({f: flat[f] for f in BASE.FIELDS})
    for domain in BASE.DOMAINS:
        for field in ORIGIN_FIELDS:
            assert sum(flat[f"{domain}.{origin}.{field}"] for origin in ORIGINS) == flat[f"{domain}.{field}"]
        for origin in ORIGINS:
            v = {f: flat[f"{domain}.{origin}.{f}"] for f in ORIGIN_FIELDS}
            assert v["accepted"] <= v["word8_equal"] <= v["word8_probe_calls"] <= v["queries"]
            assert v["accepted_match_bytes"] == v["accepted_extra_bytes_vs_primary"] + v["primary_bytes_at_accept"]


def self_check():
    frozen = ROOT / "candidates/r25-astra-dual8/parse.rs"
    raw = frozen.read_bytes()
    observed = instrument(raw)
    assert frozen.read_bytes() == raw
    assert len(FIELDS) == len(set(FIELDS)) == 178
    check_counts(dict.fromkeys(FIELDS, 0))
    evidence = json.loads(REFERENCE.read_bytes())
    row = next(r for r in evidence["rows"] if r["counts"]["main_long_reads"])
    fixture = dict.fromkeys(FIELDS, 0)
    fixture.update(row["counts"])
    for domain in BASE.DOMAINS:
        for field, value in row["domains"][domain].items():
            fixture[f"{domain}.{field}"] = value
        for field in ORIGIN_FIELDS:
            fixture[f"{domain}.record.{field}"] = row["domains"][domain][field]
    # All-record is an artificial schema fixture, not a claim about the actual origins.
    check_counts(fixture)
    malformed = fixture.copy()
    malformed["primary_miss.main.queries"] += 1
    try:
        check_counts(malformed)
    except AssertionError:
        invalid_rejected = True
    else:
        raise AssertionError("origin total mismatch was accepted")
    # Check tag chronology independently of parser semantics: capture before overwrite, reset per engine.
    tags = [0] * 4
    values = [0] * 4
    def record(slot, value):
        values[slot] = value
        tags[slot] = 2
    def main(slot, value):
        previous = (values[slot], tags[slot])
        values[slot], tags[slot] = value, 1
        return previous
    assert main(0, 0) == (0, 0)
    record(0, 7)
    assert main(0, 11) == (7, 2)
    assert main(0, 17) == (11, 1)
    record(0, 23)
    record(0, 29)
    assert main(0, 31) == (29, 2)
    result = {"status": "VERIFIED_LOCAL_GENERATION_SCHEMA_AND_TAG_ORDER_ONLY", "source_sha256": BASE.sha(raw),
              "E_observer_sha256": BASE_OBSERVER, "new_observer_sha256": BASE.sha(observed), "field_count": len(FIELDS),
              "observer_bytes": len(observed), "tag_cases": ["initial_zero", "record_then_main", "main_then_main", "two_records_then_main"],
              "schema_fixture": "One real E count row assigned to record only for schema validation; not measured origin data.",
              "origin_total_mismatch_rejected": invalid_rejected,
              "compile": "NOT_RUN", "native": "NOT_RUN", "E_script_and_source_unchanged": True}
    path = ROOT / "evidence/round25/astra/dual8-origins-selfcheck.json"
    path.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    print(json.dumps(result, indent=2))


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    from round4 import validate
    spec = validate(os.environ["ROUND4_SPEC"])
    entry = next(e for e in spec["entries"] if e["name"] == "r25-astra-dual8")
    frozen = ROOT / entry["path"] / "parse.rs"
    raw = frozen.read_bytes()
    assert BASE.sha(raw) == BASE.EXPECTED == entry["hashes"]["parse.rs"]
    reference = json.loads(REFERENCE.read_bytes())
    assert reference["status"] == "VERIFIED_UNTIMED_FROZEN_OBSERVER_TOKEN_AND_DECODE_EQUAL"
    assert reference["observer_sha256"] == BASE_OBSERVER
    previous = {r["file"]: r for r in reference["rows"]}
    build = Path(os.environ["RUNNER_TEMP"]) / "r25-dual8-origins-build"
    build.mkdir()
    out = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/r25-dual8-origins"
    out.mkdir(parents=True)
    observed = build / "observed.rs"
    observer = instrument(raw)
    observed.write_bytes(observer)
    harness = importlib.import_module("research-round13-counts").HARNESS
    harness = harness.replace("FROZEN", str(frozen)).replace("OBSERVED", str(observed))
    harness = harness.replace("observed::r13_take()", "observed::r25_take()").replace("R13_COUNT", "R25_D8_ORIGIN")
    driver = build / "main.rs"
    driver.write_text(harness)
    (out / "observer.rs").write_bytes(observer)
    (out / "harness.rs").write_text(harness)
    result = {"status": "STARTED_UNTIMED_ORIGIN_OBSERVER", "run_id": os.environ["GITHUB_RUN_ID"],
              "git_sha": os.environ["GITHUB_SHA"], "batch": os.environ["ROUND4_SPEC"], "candidate": entry["name"],
              "source_hashes": entry["hashes"], "observer_sha256": BASE.sha(observer), "harness_sha256": BASE.sha(harness.encode()),
              "E_observer_sha256": BASE_OBSERVER, "E_receipt": REFERENCE.relative_to(ROOT).as_posix(),
              "E_receipt_sha256": BASE.sha(REFERENCE.read_bytes()), "fields": FIELDS,
              "scope": "Local byte tags shadow actual long-table slots. Main captures origin before its overwrite; record tags update after the original write. No original output or query result changed. Origin counts are not causal savings or removable-update counts.",
              "limits": "Record may feed later main queries and changed parse trajectories. Removing record updates would expose older hints and change future states. Initialization/source0 is distinguished by tag, not inferred from stored position0. Additional observer hash/tag work is excluded from logical E counters."}
    report = out / "counts.json"
    report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    binary = build / "origins"
    try:
        result["phase"] = "compile"
        BASE.captured(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(driver), "-o", str(binary)], out / "compile.log", 180)
        result["binary_sha256"] = BASE.sha(binary.read_bytes())
        result["phase"] = "run"
        corpus = Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1"
        run = BASE.captured([str(binary), str(corpus)], out / "run.log", 240)
        rows = []
        for line in run.stdout.splitlines():
            if not line.startswith("R25_D8_ORIGIN "):
                continue
            _, name, size, *values = line.split()
            assert len(values) == len(FIELDS)
            data = (corpus / name).read_bytes()
            assert len(data) == int(size)
            flat = dict(zip(FIELDS, map(int, values)))
            check_counts(flat)
            row = {"file": name, "raw_bytes": len(data), "input_sha256": BASE.sha(data),
                   "counts": {k: flat[k] for k in BASE.GLOBAL_FIELDS},
                   "domains": {d: {f: flat[d + "." + f] for f in BASE.DOMAIN_FIELDS} for d in BASE.DOMAINS},
                   "origins": {d: {o: {f: flat[f"{d}.{o}.{f}"] for f in ORIGIN_FIELDS} for o in ORIGINS} for d in BASE.DOMAINS}}
            for key in ("raw_bytes", "input_sha256", "counts", "domains"):
                assert row[key] == previous[name][key], (name, key, "E observer count drift")
            rows.append(row)
        assert len(rows) == len({r["file"] for r in rows}) == 28
        assert sum(r["raw_bytes"] for r in rows) == 15930000
        totals = {"counts": {k: sum(r["counts"][k] for r in rows) for k in BASE.GLOBAL_FIELDS},
                  "domains": {d: {f: sum(r["domains"][d][f] for r in rows) for f in BASE.DOMAIN_FIELDS} for d in BASE.DOMAINS},
                  "origins": {d: {o: {f: sum(r["origins"][d][o][f] for r in rows) for f in ORIGIN_FIELDS} for o in ORIGINS} for d in BASE.DOMAINS}}
        result.update(status="VERIFIED_UNTIMED_ORIGINS_TOKEN_DECODE_AND_ALL_E_COUNTS_EQUAL", phase="complete", rows=rows, totals=totals)
        assert frozen.read_bytes() == raw
    except Exception as exc:
        result.update(status="FAILED_OR_INCOMPLETE_ORIGIN_OBSERVER", error_type=type(exc).__name__, error=str(exc))
        report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
        raise
    report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    print(json.dumps({"status": result["status"], "origin_totals": totals["origins"]}, indent=2))


if __name__ == "__main__":
    if sys.argv[1:] == ["--self-check"]:
        self_check()
    else:
        main()
