"""D-only 16-bit predecessor deltas, preserving the original forward planner.

The finite Python model checks observable in-window chain visits, including
current-slot overwrites and u32 position wrap. It does not replace Rust token
differentials, extraction, the complete Lean gate, or official timing.
"""
from pathlib import Path
import argparse
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r9-block-scalar"
NAME = "r10-forward-delta16"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, old
    return text.replace(old, new, 1)


def function(source, name):
    start = source.index(f"pub fn {name}(")
    body = source.index("{", start)
    depth = 1
    end = body + 1
    while depth:
        if source[end] == "{":
            depth += 1
        elif source[end] == "}":
            depth -= 1
        end += 1
    return source[start:end]


def generate():
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    origin = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(b) == origin["hashes"][n] for n, b in raw.items())
    source = raw["parse.rs"].decode()
    insert = function(source, "insert_pos").replace("pub fn insert_pos(", "pub fn d16_insert_pos(")
    insert = insert.replace("prev4: &mut [u32; WN]", "prev4: &mut [u16; WN]")
    insert = insert.replace("prev7: &mut [u32; WN]", "prev7: &mut [u16; WN]")
    insert = once(insert, "prev4[q % WN] = c4 as u32;", "prev4[q % WN] = d16_link(q, c4);")
    insert = once(insert, "prev7[q % WN] = c7 as u32;", "prev7[q % WN] = d16_link(q, c7);")
    region = function(source, "insert_range").replace("insert_range(", "d16_insert_range(")
    region = region.replace("prev4: &mut [u32; WN]", "prev4: &mut [u16; WN]")
    region = region.replace("prev7: &mut [u32; WN]", "prev7: &mut [u16; WN]")
    region = once(region, "insert_pos(", "d16_insert_pos(")
    skip = function(source, "skip_same").replace("skip_same(", "d16_skip_same(")
    skip = once(skip, "prev: &[u32; WN]", "prev: &[u16; WN]")
    skip = once(skip, "let nx = prev[start % WN] as usize;", "let nx = start.wrapping_sub(prev[start % WN] as usize);")
    walk = function(source, "d_walk").replace("d_walk(", "d16_walk(")
    walk = once(walk, "prev: &[u32; WN]", "prev: &[u16; WN]")
    walk = once(walk, "let nx = prev[c % WN] as usize;", "let nx = c.wrapping_sub(prev[c % WN] as usize);")
    extra = '''/// Distance-coded D predecessor chains. A zero delta is a chain terminator.
/// Links beyond the DEFLATE window cannot lead to a useful older node.
#[inline(always)]
pub fn d16_link(q: usize, c: usize) -> u16 {
    let delta = q.wrapping_sub(c);
    if delta <= 32768 { delta as u16 } else { 0 }
}

'''
    for note, helper in (
        ("Original insertion order and u32 heads; only the two predecessor stores are distance-coded.", insert),
        ("Insert all skipped positions exactly as in the original D path.", region),
        ("Reconstruct one predecessor, retaining the original strict-decrease stop test.", skip),
        ("Original D probe order with 16-bit backward links; stops and candidate handling are unchanged.", walk),
    ):
        extra += "/// " + note + "\n#[inline(always)]\n" + helper + "\n\n"
    old_parse = function(source, "d_parse")
    new_parse = once(old_parse, "let mut prev4 = [0u32; WN];", "let mut prev4 = [0u16; WN];")
    new_parse = once(new_parse, "let mut prev7 = [0u32; WN];", "let mut prev7 = [0u16; WN];")
    for old, new, count in (("insert_pos(", "d16_insert_pos(", 1),
                            ("insert_range(", "d16_insert_range(", 1),
                            ("skip_same(", "d16_skip_same(", 2),
                            ("d_walk(", "d16_walk(", 2)):
        assert new_parse.count(old) == count
        new_parse = new_parse.replace(old, new)
    source = once(source, old_parse, extra + new_parse)
    assert source.replace(extra + new_parse, old_parse, 1) == raw["parse.rs"].decode()
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    manifest = {
        "candidate": NAME, "parent": "candidates/r9-block-scalar", "base_submission_id": "361",
        "parent_hashes": origin["hashes"], "hashes": {n: sha(b) for n, b in files.items()},
        "bytes": {n: len(b) for n, b in files.items()}, "attribution": origin["attribution"],
        "mechanism": "D-only predecessor arrays change from absolute u32 positions to u16 backward distances 1..32768, with zero termination; absolute hash heads and all forward/backward planning remain unchanged.",
        "fixed_chain_state_bytes_before": 262144, "fixed_chain_state_bytes_after": 131072,
        "audit": "Only d_parse's two prev array types and six helper call sites change; five copied/small helpers are added. Reversing that region restores the scalar source exactly. Shared DP functions, router, knobs, candidates, record encoding, planner and emitters remain byte-identical.",
        "equivalence_argument": "For live c with 0 < i-c < WN, the slot still belongs to c, so a representable link recovers its original predecessor. A discarded link is already older than the active window. At c=i-WN the slot may have just been overwritten, but every strictly decreasing successor is out of window in either representation. A stale skip_same start likewise cannot reach a newer in-window node.",
        "equivalence_status": "INFERRED: requires fresh 444-case Rust token/decode equality and public output equality. Finite link-model tests are separate evidence, not a proof of compression semantics.",
        "proof_status": "UNADAPTED_PARENT_ONLY: new helper totality and d_parse U16 loop-state bridge still require fresh extraction and original obligation/axiom gate.",
        "performance_status": "UNKNOWN: saves 128 KiB of fixed chain state and half its initialization/store traffic but adds one distance encode/decode operation; measure paired total compression.",
    }
    assert all(len(b) <= 524288 for b in files.values())
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
    return files


def model_check():
    mask = (1 << 64) - 1
    checks = 0
    boundary_visits = 0
    inserted = 0
    cases = []
    for window in (7, 16, 31, 32768):
        for mode in range(4):
            for wrap in (False, True):
                n = 4 * window + 5
                start = (1 << 32) - 2 * window if wrap else 0
                heads = [0] * (1 if mode == 0 else 17)
                old = [0] * window
                new = [0] * window
                rng = random.Random(827361 + window + 31 * mode)
                local = 0
                def visits(i, c, depth, compact):
                    answer = []
                    while depth > 0 and 1 <= i - c <= window:
                        answer.append(c)
                        nx = (c - new[c % window]) & mask if compact else old[c % window]
                        if nx >= c:
                            break
                        c, depth = nx, depth - 1
                    return answer
                for i in range(start, start + n):
                    key = 0 if mode == 0 else (i % 17 if mode == 1 else (rng.randrange(17) if mode == 2 else (0 if i % window < 3 else i % 17)))
                    previous = heads[key]
                    heads[key] = i & 0xFFFFFFFF
                    old[i % window] = previous
                    delta = (i - previous) & mask
                    new[i % window] = delta if delta <= window else 0
                    inserted += 1
                    if window == 32768 and not (
                        (i - start) % 257 == 0 or i % window < 4
                        or i - start < 16 or i >= start + n - 16
                        or abs(i - (1 << 32)) < 16
                    ):
                        continue
                    # Cover a current head, every exact boundary, and stale starts
                    # after the current insertion has overwritten its ring slot.
                    starts = (previous, max(0, i - window), max(0, i - window - 1))
                    for current in starts:
                        for depth in (1, 2, 7, 48):
                            a = visits(i, current, depth, False)
                            b = visits(i, current, depth, True)
                            assert a == b, (window, mode, wrap, i, current, depth, a, b)
                            boundary_visits += sum(i - c == window for c in a)
                            checks += 1
                            local += 1
                            ax = old[current % window]
                            bx = (current - new[current % window]) & mask
                            ac, ad = (ax, depth - 1) if ax < current else (current, 0)
                            bc, bd = (bx, depth - 1) if bx < current else (current, 0)
                            a = visits(i, ac, ad, False)
                            b = visits(i, bc, bd, True)
                            assert a == b, ("skip", window, mode, wrap, i, current, depth, a, b)
                            checks += 1
                            local += 1
                cases.append({"window": window, "mode": mode, "u32_wrap": wrap, "insertions": n, "comparisons": local})
    return {"status": "VERIFIED_FINITE_LINK_MODEL", "scope": "Python state model only; observable in-window chain visit sequences, direct and skip_same. Not Rust token equality or universal equivalence.",
            "insertions": inserted, "comparisons": checks, "exact_window_boundary_visits": boundary_visits,
            "cases": cases, "source_sha256": json.loads(generate()["manifest.json"])["hashes"]["parse.rs"]}


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
        (dest / "delta-model-check.json").write_text(json.dumps(report, indent=2) + "\n")
        print(json.dumps({k: v for k, v in report.items() if k != "cases"}))


if __name__ == "__main__":
    main()
