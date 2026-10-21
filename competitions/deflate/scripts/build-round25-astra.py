"""Build two bounded fast-PC experiments; do not launch CI or change official files."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "evidence/round25/astra"
PARENT = ROOT / "candidates/r22-595-chain-halfhead"
EXPECTED_PARENT = "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def save_json(path, value):
    assert not path.exists(), path
    path.write_bytes((json.dumps(value, indent=2, ensure_ascii=False) + "\n").encode())


def write_candidate(name, rust, mechanism, difference, proof):
    path = ROOT / "candidates" / name
    assert not path.exists(), path
    path.mkdir()
    files = {"parse.rs": rust.encode(), "Parse.lean": (PARENT / "Parse.lean").read_bytes()}
    assert all(0 < len(v) <= 524288 for v in files.values())
    for filename, data in files.items():
        (path / filename).write_bytes(data)
    hashes = {filename: sha(data) for filename, data in files.items()}
    save_json(path / "manifest.json", {
        "candidate": name, "parent": PARENT.name, "hashes": hashes,
        "mechanism": mechanism, "difference_from_old_work": difference,
        "attribution": {
            "source": "references/round21-public-595/source-receipt.json",
            "parent": "candidates/r22-595-chain-halfhead/manifest.json",
            "ownership": "Inherited public PC matcher, original routing and original author headers retained."
        },
        "proof_migration": proof,
        "proof_status": "DRAFT_UNCOMPILED_FOR_NEW_EXACT_PAIR",
        "performance_status": "UNKNOWN", "formal_submission_sent": False
    })
    return {"name": name, "path": path.relative_to(ROOT).as_posix(), "control": False,
            "hashes": hashes, "anchor": "public595", "comparison_baseline": "combo",
            "native_decode_reference": "combo"}


def insertion_model():
    cases = 0
    added = 0
    # Finite model of insertion ordering, including the n-8 search boundary.
    # It is not a native Rust, decode, equality, or Lean correctness check.
    for p in range(8):
        for length in range(3, 259):
            for lookahead in (1, 2):
                for remaining in (0, 1, 4, 8, 16):
                    end = p + length
                    n = end + remaining
                    if n <= 16 or p >= n - 8:
                        continue
                    lim = n - 8
                    ins0 = p + lookahead
                    stop = min(end, ins0 + 2, lim)
                    head = list(range(ins0, stop))
                    ins = max(ins0, stop)
                    old_tail = end - 1 if ins + 1 < end else ins
                    old = head + ([old_tail] if old_tail < end and old_tail < lim else [])
                    extra = [end - 4] if end >= 4 and ins <= end - 4 and end - 4 < lim else []
                    new = head + extra + ([old_tail] if old_tail < end and old_tail < lim else [])
                    assert new == sorted(set(new))
                    assert all(i in new for i in old)
                    assert len(new) - len(old) in (0, 1)
                    if extra:
                        assert extra[0] + 4 == end and extra[0] >= p and extra[0] < lim
                        added += 1
                    cases += 1
    return {"status": "VERIFIED_FINITE_INSERTION_ORDER_MODEL", "cases": cases,
            "cases_with_one_added_index": added,
            "scope": "Small finite position/length/boundary model only; all Rust/gate/performance claims remain UNKNOWN."}


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    data = (PARENT / "parse.rs").read_bytes()
    assert sha(data) == EXPECTED_PARENT
    base = data.decode()
    start = base.index("pub fn pc_f_record3<const H: usize>")
    end = base.index("/// `pc_run1` with chain links", start)
    body = base[start:end]
    old = "    if pc_TAIL == 1 {"
    assert body.count(old) == 1
    insertion = """    // One complete four-byte key at the matched suffix, before the crossing end-1 key.
    // Preserve the original head inserts and monotone position order; never duplicate them.
    if end >= 4 && ins <= end - 4 && end - 4 < lim {
        let j = end - 4;
        let a = pc_slot_of_m::<H>(s, j, km);
        pc_f_link::<H>(head, prev, a, j);
    }
"""
    tail = base[:start] + body.replace(old, insertion + old) + base[end:]
    entries = [write_candidate("r25-astra-end4", tail,
        "Add at most one previously unrecorded end-4 key after the original head positions and before end-1 in pc_f_record3. Existing chain depth, head tables, search/lazy/skip/fold rules and routes stay unchanged.",
        "R3 INS_MAX 2-to-6/8 densified the match head. This retains that head density and inserts only the terminal four-byte key wholly inside the matched span; the original end-1 key crosses the first mismatch except at the 258 cap. R22/R23 increased search depth without improving insertion coverage. This experiment changes candidate availability, not depth.",
        "No Rust function signature or explicit loop state changes. f_record3_spec must cover one extra slot_of_m/f_link call under j<lim and j<end. Original HeadBound, coherent ahead refresh and independent byte validators can be reused; exact extracted interface and fresh original gate remain required.")]

    helper = """/// R25: one previous-distance attempt exactly one byte after a match, only on a failed head.
/// The output token is only a hint: the original byte/window validator establishes validity.
#[inline(always)]
pub fn pc_f_find_gap1(s: &[u8], out: &[u32], nt: usize, ls: usize,
    prev: &[u32; 32768], c: usize, cw: u64, p: usize, km: u32,
    dp: usize, minl: usize) -> (usize, usize) {
    let f = pc_probe_m(s, c, cw, p, km);
    if f.0 >= 3 {
        let cl = prev[c % 32768] as usize;
        pc_f_deepen(s, prev, c, cl, p, f.0, f.1, dp, minl)
    } else if p > ls && p - ls == 1 && nt > 0 && nt <= out.len() {
        let t = out[nt - 1];
        if t >= 16777216 {
            let d = ((t - 16777216) / 256 + 1) as usize;
            if d <= 32768 && d <= p {
                let rc = p - d;
                let rw = pc_be8(s, rc);
                let g = pc_probe_m(s, rc, rw, p, km);
                if g.0 >= minl { g } else { (0, 0) }
            } else { (0, 0) }
        } else { (0, 0) }
    } else { f }
}

"""
    marker = "/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes."
    assert base.count(marker) == 1
    gap = base.replace(marker, helper + marker)
    old_search = """            let f = pc_probe_m(input, c, cw, p, km);
            if f.0 >= 3 {
                let cl = prev[c % 32768] as usize;
                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);
"""
    new_search = """            let g = pc_f_find_gap1(input, out, nt, ls, &prev, c, cw, p, km, dp, minl);
            if g.0 >= 3 {
"""
    assert gap.count(old_search) == 1
    gap = gap.replace(old_search, new_search)
    entries.append(write_candidate("r25-astra-gap1", gap,
        "On pc_run1c primary failure at exactly p=ls+1, probe the previous output match distance once. Reuse out[nt-1] rather than a new table/state variable; original successful primary and deepening path is preserved. No chain deepening follows a rescued match.",
        "A bounded conditional revisit of R11 gaprepeat, which reduced size 0.0222624pp but cost 0.850916% total time on fast3. Old code tried all failed-probe positions with any pending literal gap; this permits one position per inter-match literal run, excludes long miss stretches, and operates on actual595 pc_run1c. R13 predecessor rescue instead retries hash-collision chains; this probes a distance independent of the hash chain. It is not claimed as an entirely new repeat-distance mechanism.",
        "Add pc_f_find_gap1_spec returning FoundAt plus length<=258 and distance<=32768. Reuse probe_m_spec, f_deepen_spec, FoundAt.real and MatchAt bounds. Arbitrary out token is a hint and needs no decoded-token invariant; guards establish safe read and rc<=p. No main-loop tuple field or Rust loop parameter added, but actual extraction must be checked. Inherited Lean does not yet contain the helper theorem."))
    save_json(OUT / "entries.json", entries)
    save_json(OUT / "insertion-model.json", insertion_model())
    save_json(OUT / "preflight.json", {
        "status": "PREDECLARED_IMPLEMENTATIONS_NOT_NATIVE_TESTED",
        "parent_sha256": EXPECTED_PARENT,
        "gap": "Fast595 combo has narrow conditional share windows and failed independent observations. Deeper chain and gain acceptance saved bytes but cost total time. Need real inexpensive compression margin.",
        "candidates": entries,
        "minimum": "Full28-file original encoder, exact candidate/actual combo/public595 source identities, per-file token and compressed bytes, independent decode. End4 and gap1 are separate, not combined.",
        "observer_if_needed": {
            "end4": "Count eligible suffix insertions, added-key head displacements, whether later accepted source is an added suffix position, and per-file byte changes. Counts are not compressed savings.",
            "gap1": "Count parent failed heads at gap1, legal previous-distance hints, valid recovered matches/covered bytes by length and distance. If output is unchanged or weak, compare gap1 versus other gap opportunity before any wider search."
        },
        "cost_cap_first_native_runner_minutes": 12,
        "stop": "Decode/panic error stops that source. No output change and no new useful opportunity closes quality investment. Worse bytes or inflated tokens require credible speed/geometry headroom before timing. Native quality is not a speed result; existing counterexamples and new same-source controls must remain visible.",
        "promotion": "Original paired total compression against exact combo/public595 and same-source shadow; latest frozen official snapshot replay per block. Only then proof migration, fresh exact original full gate and frozen cross-runner confirmation within the common deadline.",
        "proof": "Copied parent Lean is explicitly DRAFT. No complete gate or parser proof claim."
    })
    print(json.dumps({"entries": entries, "finite_model": insertion_model()}, indent=2))


if __name__ == "__main__":
    main()
