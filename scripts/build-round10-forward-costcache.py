"""D cost-model rebuilds guarded by actual statistics changes.

Every original update position and every count-halving check remain. Only a
pure make_costs call whose inputs are unchanged can be skipped. This is not an
update-interval or parser-quality parameter change.
"""
from pathlib import Path
import argparse
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-record-nonempty"
NAME = "r10-forward-costcache"


def sha(data):
    return hashlib.sha256(data).hexdigest()


HELPER = r'''/// Keep the original frequency-total and halving checks at every update.
/// Skip rebuilding the pure tables only when no frequency changed since their
/// last build and this update also performs no halving.
pub fn d_update_costs_cached(lf: &mut [u32; 320], df: &mut [u32; 32], lsym: &[u8; 512], litc: &mut [u32; 256], lc: &mut [u32; 512], dcc: &mut [u32; 32], huff: usize, dirty: bool) {
    let mut tot = 0u32;
    let mut z = 0usize;
    while z < 286 {
        tot = tot.wrapping_add(lf[z]);
        z += 1;
    }
    let mut refresh = dirty;
    if tot > HALF_AT {
        halve(lf, df);
        refresh = true;
    }
    if refresh {
        make_costs(lf, df, lsym, litc, lc, dcc, huff);
    }
}

'''


def generate():
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    parent = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(data) == parent["hashes"][n] for n, data in raw.items())
    verified = json.loads((BASE / "VERIFICATION.json").read_text())
    assert verified["official_accepted"] and verified["files"] == parent["hashes"]
    original = raw["parse.rs"].decode()
    a = original.index("pub fn d_parse(")
    b = original.index("// ── glue ──", a)
    old = original[a:b]
    new = old
    replacements = [
        ("    let mut next_upd = UPD;", "    let mut next_upd = UPD;\n    // Initial prices precede two count halvings, so their inputs are already dirty.\n    let mut costs_dirty = true;"),
        ("                backtrack(input, &pa, plan, s, st, &lsym, &dtab, &mut lf, &mut df, &mut tb);",
         "                backtrack(input, &pa, plan, s, st, &lsym, &dtab, &mut lf, &mut df, &mut tb);\n                costs_dirty = true;"),
        ("            backtrack(input, &pa, plan, s, i, &lsym, &dtab, &mut lf, &mut df, &mut tb);",
         "            backtrack(input, &pa, plan, s, i, &lsym, &dtab, &mut lf, &mut df, &mut tb);\n            costs_dirty = true;"),
        ("            update_costs(&mut lf, &mut df, &lsym, &mut litc, &mut lc, &mut dcc, huff);",
         "            d_update_costs_cached(&mut lf, &mut df, &lsym, &mut litc, &mut lc, &mut dcc, huff, costs_dirty);\n            costs_dirty = false;"),
    ]
    for before, after in replacements:
        assert new.count(before) == 1, before
        new = new.replace(before, after, 1)
    # The final tail backtrack has no subsequent price update, so needs no mark.
    assert new.count("backtrack(input,") == 3
    assert new.count("costs_dirty = true;") == 3
    assert new.count("costs_dirty = false;") == 1
    source = original[:a] + HELPER + new + original[b:]
    assert source.replace(HELPER + new, old, 1) == original
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": NAME, "parent": "candidates/r10-record-nonempty", "base_submission_id": "361",
        "parent_hashes": parent["hashes"], "hashes": {n: sha(data) for n, data in files.items()},
        "bytes": {n: len(data) for n, data in files.items()}, "attribution": parent["attribution"],
        "mechanism": "Preserve every D price-update position and halving decision; skip only make_costs when frequency inputs have not changed since the last build and no halving occurs now.",
        "source_evidence": "UPD=2048 and CHUNK=4096; statistics change at backtrack/direct long-match updates, while the original update_costs unconditionally reconstructs prices at each UPD boundary.",
        "dirty_protocol": "Initially true because two halvings follow the initial make_costs; mark true after either in-loop backtrack (the long-jump case also includes direct match counts); clear after each scheduled update. The final tail backtrack has no later update.",
        "halving_guard": "The original wrapping frequency sum and HALF_AT comparison always execute. Any halving forces a rebuild even when dirty was false; no assumed count bound is used to suppress halving.",
        "unchanged": "UPD/CHUNK/HALF_AT, sampling/model formulas, routes, search schedule and budgets, rs recording, backward pass, and output verification.",
        "audit": "One helper plus four localized d_parse substitutions; reverse the region to restore the verified record-nonempty parent exactly. No new finder table, greedy seed, pass, or alternative cost model.",
        "verified_parent": "candidates/r10-record-nonempty/VERIFICATION.json",
        "equivalence_status": "INFERRED exact prices/plan/tokens: make_costs is pure in lf/df/lsym/huff and every possible in-loop frequency mutation marks dirty. Requires 444-case token/decode equality and identical public output.",
        "proof_status": "UNADAPTED_PARENT_ONLY: cached-update totality and the additional Boolean loop state need fresh extraction and original complete gate.",
        "performance_status": "UNKNOWN: dependent on how many scheduled updates occur without new statistics; flag overhead and code layout may erase saved rebuilds. Paired total compression required.",
    }
    assert all(len(data) <= 524288 for data in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files


def model_check():
    mask = (1 << 32) - 1
    cases = []
    def run_case(label, initial, events, details=None):
        lf = list(initial[0]); df = list(initial[1])
        old_lf = lf[:]; old_df = df[:]
        # A cost fingerprint represents all arguments of the pure make_costs.
        old_cost = tuple(old_lf + old_df)
        cached_cost = tuple(lf + df)
        def halve(a, b):
            for j in range(286): a[j] = ((a[j] + 1) & mask) // 2
            for j in range(30): b[j] = ((b[j] + 1) & mask) // 2
        halve(lf, df); halve(lf, df)
        halve(old_lf, old_df); halve(old_lf, old_df)
        dirty = True
        updates = rebuilt = skipped = clean_halves = longest = streak = 0
        for event in events:
            if event[0] == "count":
                _, ls, ds, amount = event
                lf[ls] = (lf[ls] + amount) & mask
                old_lf[ls] = (old_lf[ls] + amount) & mask
                if ds is not None:
                    df[ds] = (df[ds] + 1) & mask
                    old_df[ds] = (old_df[ds] + 1) & mask
                dirty = True
                streak = 0
            else:
                assert event[0] == "update"
                old_total = sum(old_lf[:286]) & mask
                total = sum(lf[:286]) & mask
                assert old_total == total
                if old_total > 10000: halve(old_lf, old_df)
                old_cost = tuple(old_lf + old_df)
                refresh = dirty
                if total > 10000:
                    halve(lf, df)
                    refresh = True
                    if not dirty:
                        clean_halves += 1
                        streak += 1
                        longest = max(longest, streak)
                else:
                    streak = 0
                if refresh:
                    cached_cost = tuple(lf + df)
                    rebuilt += 1
                else:
                    skipped += 1
                dirty = False
                updates += 1
                assert lf == old_lf and df == old_df and cached_cost == old_cost, (label, event, updates)
        cases.append({"case": label, "scheduled_updates": updates, "rebuilds": rebuilt,
                      "skipped_rebuilds": skipped, "halvings_while_previously_clean": clean_halves,
                      "max_consecutive_clean_halvings": longest, **(details or {})})
    def initial(value):
        lf = [0] * 320; df = [0] * 32
        lf[65] = value; lf[256] = 1
        for j in range(257, 286): lf[j] = 400 if j < 265 else 150 if j < 273 else 30
        for j in range(30): df[j] = 60 if j < 4 else 120
        return lf, df
    for value in (0, 8192, 1000000, (1 << 32) - 1):
        run_case(f"no-new-counts-{value}", initial(value), [("update",)] * 48)
    for seed in range(8):
        rng = random.Random(105361 + seed)
        events = []
        i = chunk_start = 0
        next_update = 2048
        jumps = crossings = chunk_flushes = 0
        while i < 131073:
            # The no-jump case crosses both the UPD and CHUNK boundaries;
            # other cases include long-match jumps spanning update boundaries.
            jump = seed > 0 and rng.randrange(401) == 0
            if jump:
                events.append(("count", rng.randrange(256), None, rng.randrange(1, 1024)))
                events.append(("count", rng.randrange(257, 286), rng.randrange(30), 1))
                length = rng.randrange(32, 259)
                jumps += 1
                crossings += i < next_update <= i + length
                i += length
                chunk_start = i
            else:
                i += 1
            if i - chunk_start >= 4096:
                events.append(("count", rng.randrange(256), None, 4096))
                chunk_flushes += 1
                chunk_start = i
            if i >= next_update:
                events.append(("update",))
                next_update = i + 2048
        run_case(f"UPD-CHUNK-long-jumps-{seed}", initial(8192), events,
                 {"long_jumps": jumps, "long_jumps_crossing_update": crossings, "chunk_flushes": chunk_flushes})
    assert sum(c["skipped_rebuilds"] for c in cases) > 0
    assert max(c["max_consecutive_clean_halvings"] for c in cases) >= 3
    assert sum(c.get("long_jumps_crossing_update", 0) for c in cases) > 0
    assert sum(c.get("chunk_flushes", 0) for c in cases) > 0
    return {"status": "VERIFIED_FINITE_DIRTY_STATE_MODEL",
            "scope": "Frequency arrays and the pure make_costs argument fingerprint agree after each update; actual Rust prices/tokens are not executed here.",
            "initialization": "Both models make initial prices, halve counts twice, and set dirty=true before the first scheduled update.",
            "cases": cases,
            "scheduled_updates": sum(c["scheduled_updates"] for c in cases),
            "skipped_rebuilds": sum(c["skipped_rebuilds"] for c in cases),
            "clean_halvings": sum(c["halvings_while_previously_clean"] for c in cases),
            "source_sha256": json.loads(generate()["manifest.json"])["hashes"]["parse.rs"]}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--model-check", action="store_true")
    args = ap.parse_args()
    files = generate()
    dest = ROOT / "candidates" / NAME
    if args.check:
        assert all((dest / n).read_bytes() == data for n, data in files.items())
    else:
        dest.mkdir(parents=True, exist_ok=True)
        for n, data in files.items():
            if (dest / n).exists() and (dest / n).read_bytes() != data:
                raise ValueError(f"preserve existing different file {dest / n}")
            (dest / n).write_bytes(data)
    print(json.dumps({"candidate": NAME, "hashes": json.loads(files["manifest.json"])["hashes"], "status": "UNADAPTED_PARENT_ONLY"}))
    if args.model_check:
        report = model_check()
        (dest / "dirty-model-check.json").write_text(json.dumps(report, indent=2) + "\n")
        print(json.dumps({k: v for k, v in report.items() if k != "cases"}))


if __name__ == "__main__":
    main()
