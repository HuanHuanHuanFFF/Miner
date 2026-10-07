"""Equivalent backward-DP length reductions derived from verified R7 block1.

Only candidates/r9-block-* and evidence/round9/block-design.md belong to this
experiment. Candidate proof lemmas are drafts pending fresh extraction/gate.
"""

from pathlib import Path
import argparse
import hashlib
import json


ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r7-mid361-block1"

COST = """/// Unpacked endpoint price; each operand is at most u32::MAX.
#[inline(always)]
pub fn d_bcost(lc: &[u32; 512], ring: &[u64; D_RING], p: usize, l: usize) -> u64 {
    (ring[p.wrapping_add(l) % D_RING] >> 32).wrapping_add(lc[l % 512] as u64)
}

"""

SCALAR = """/// Compare raw endpoint costs; ascending iteration retains the shortest tie.
#[inline(always)]
pub fn d_best_len_scalar(lc: &[u32; 512], ring: &[u64; D_RING], p: usize, lo: usize, e: usize) -> u64 {
    let mut best = d_bcost(lc, ring, p, lo);
    let mut bl = lo;
    let mut l = lo.wrapping_add(1);
    while l < e {
        let v = d_bcost(lc, ring, p, l);
        if v < best {
            best = v;
            bl = l;
        }
        l += 1;
    }
    (best << 9) | bl as u64
}

"""

FOUR = """/// Four independent raw-cost reductions, then packed merge and a short tail.
#[inline(always)]
pub fn d_best_len_four(lc: &[u32; 512], ring: &[u64; D_RING], p: usize, lo: usize, e: usize) -> u64 {
    let mut c0 = d_bcost(lc, ring, p, lo);
    let mut c1 = d_bcost(lc, ring, p, lo.wrapping_add(1));
    let mut c2 = d_bcost(lc, ring, p, lo.wrapping_add(2));
    let mut c3 = d_bcost(lc, ring, p, lo.wrapping_add(3));
    let mut b0 = lo;
    let mut b1 = lo.wrapping_add(1);
    let mut b2 = lo.wrapping_add(2);
    let mut b3 = lo.wrapping_add(3);
    let mut l = lo.wrapping_add(4);
    while l < e && e - l >= 4 {
        let v0 = d_bcost(lc, ring, p, l);
        let v1 = d_bcost(lc, ring, p, l.wrapping_add(1));
        let v2 = d_bcost(lc, ring, p, l.wrapping_add(2));
        let v3 = d_bcost(lc, ring, p, l.wrapping_add(3));
        if v0 < c0 { c0 = v0; b0 = l; }
        if v1 < c1 { c1 = v1; b1 = l.wrapping_add(1); }
        if v2 < c2 { c2 = v2; b2 = l.wrapping_add(2); }
        if v3 < c3 { c3 = v3; b3 = l.wrapping_add(3); }
        l += 4;
    }
    let v0 = (c0 << 9) | b0 as u64;
    let v1 = (c1 << 9) | b1 as u64;
    let v2 = (c2 << 9) | b2 as u64;
    let v3 = (c3 << 9) | b3 as u64;
    let v01 = if v0 < v1 { v0 } else { v1 };
    let v23 = if v2 < v3 { v2 } else { v3 };
    let mut bv = if v01 < v23 { v01 } else { v23 };
    while l < e {
        let v = (d_bcost(lc, ring, p, l) << 9) | l as u64;
        if v < bv { bv = v; }
        l += 1;
    }
    bv
}

"""

COST_PROOF = """@[local step]
theorem d_bcost_spec (lc ring p l) :
    slot.d_bcost lc ring p l ⦃ fun _ => True ⦄ := by
  have hring : slot.D_RING.val = 1024 := by simp [slot.D_RING]
  rw [slot.d_bcost]
  step*
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

"""

SCALAR_PROOF = """@[local step]
theorem d_best_len_scalar_loop_spec (lc ring p e) (best : Std.U64) (bl l : Std.Usize) :
    slot.d_best_len_scalar_loop lc ring p e best bl l ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len_scalar_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, l') => e.val - l'.val)
    (inv := fun _ => True)
  · rintro ⟨best', bl', l'⟩ _
    simp only [slot.d_best_len_scalar_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem d_best_len_scalar_spec (lc ring p lo e) :
    slot.d_best_len_scalar lc ring p lo e ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len_scalar]
  step*

"""

FOUR_PROOF = """@[local step]
theorem d_best_len_four_loop0_spec (lc ring p e) (c0 c1 c2 c3 : Std.U64)
    (b0 b1 b2 b3 l : Std.Usize) :
    slot.d_best_len_four_loop0 lc ring p e c0 c1 c2 c3 b0 b1 b2 b3 l ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len_four_loop0]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, _, _, _, _, _, _, l') => e.val - l'.val)
    (inv := fun _ => True)
  · rintro ⟨c0', c1', c2', c3', b0', b1', b2', b3', l'⟩ _
    simp only [slot.d_best_len_four_loop0.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem d_best_len_four_loop1_spec (lc ring p e) (bv : Std.U64) (l : Std.Usize) :
    slot.d_best_len_four_loop1 lc ring p e bv l ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len_four_loop1]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, l') => e.val - l'.val)
    (inv := fun _ => True)
  · rintro ⟨bv', l'⟩ _
    simp only [slot.d_best_len_four_loop1.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem d_best_len_four_spec (lc ring p lo e) :
    slot.d_best_len_four lc ring p lo e ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len_four]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

"""

DISPATCH_PROOF = """@[local step]
theorem d_best_len_spec (lc ring p lo e) :
    slot.d_best_len lc ring p lo e ⦃ fun _ => True ⦄ := by
  rw [slot.d_best_len]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

"""


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def generate() -> dict[str, dict[str, bytes]]:
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    parent_manifest = json.loads((BASE / "manifest.json").read_text())
    assert all(sha(raw[n]) == parent_manifest["hashes"][n] for n in raw)
    source, proof = (raw[n].decode("utf-8") for n in ("parse.rs", "Parse.lean"))
    start = source.index("/// The cheapest end of one candidate at node p")
    end = source.index("/// Push a candidate's end", start)
    old_source = source[start:end]
    assert old_source.count("pub fn d_best_len(") == 1
    fallback = old_source.replace("d_best_len(", "d_best_len_old(", 1)
    ps = proof.index("@[local step]\ntheorem d_best_len_loop_spec")
    pe = proof.index("@[local step]\ntheorem d_push_loop_spec", ps)
    old_proof = proof[ps:pe]
    fallback_proof = old_proof.replace("d_best_len", "d_best_len_old")
    result = {}
    for label in ("scalar", "unroll4"):
        name = "r9-block-" + label
        call = "d_best_len_scalar(lc, ring, p, lo, e)"
        branch = call if label == "scalar" else (
            "if e - lo >= 4 { d_best_len_four(lc, ring, p, lo, e) } "
            "else { d_best_len_scalar(lc, ring, p, lo, e) }"
        )
        dispatch = f"""/// Valid LZ77 intervals compare unpacked costs and pack once; other inputs use the original scan.
#[inline(always)]
pub fn d_best_len(lc: &[u32; 512], ring: &[u64; D_RING], p: usize, lo: usize, e: usize) -> u64 {{
    if lo < e && e <= 259 {{
        {branch}
    }} else {{
        d_best_len_old(lc, ring, p, lo, e)
    }}
}}

"""
        new_source = COST + SCALAR + (FOUR if label == "unroll4" else "") + fallback + dispatch
        rust = source[:start] + new_source + source[end:]
        assert rust.replace(new_source, old_source, 1) == source
        new_proof = COST_PROOF + SCALAR_PROOF + (FOUR_PROOF if label == "unroll4" else "") + fallback_proof + DISPATCH_PROOF
        lean = proof[:ps] + new_proof + proof[pe:]
        assert lean.replace(new_proof, old_proof, 1) == proof
        files = {"parse.rs": rust.encode(), "Parse.lean": lean.encode()}
        assert all(len(b) <= 524288 for b in files.values())
        manifest = {
            "candidate": name,
            "parent": "candidates/r7-mid361-block1",
            "base_submission_id": "361",
            "parent_hashes": parent_manifest["hashes"],
            "hashes": {n: sha(b) for n, b in files.items()},
            "bytes": {n: len(b) for n, b in files.items()},
            "attribution": {
                "author_hotkey": parent_manifest["attribution"],
                "public_reference": "references/round7-public-361/PROVENANCE.json",
                "verified_parent": "candidates/r7-mid361-block1/VERIFICATION.json",
            },
            "mechanism": "Raw-cost length reduction with one final packing" + (" and four independent minimum chains" if label == "unroll4" else ""),
            "guard": "lo < e <= 259; unroll4 also requires e - lo >= 4; other ranges use the exact original scan",
            "equivalence_status": "INFERRED: raw cost < 2^33 and length < 512 make packed order lexicographic; shortest ties retained. Fresh Rust differential and public paired outputs required.",
            "proof_status": "UNKNOWN: totality helper lemmas drafted; exact extracted loop interfaces and original obligation/axiom gate not run.",
            "performance_status": "UNKNOWN: compiler code and paired total-compression timings not measured.",
            "audit": "Reverse one d_best_len source/proof region replacement restores verified block1 bytes; search, cost tables, routes, D gap/back/push logic, encoder and output checks unchanged.",
        }
        files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode()
        result[name] = files
    return result


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    for name, files in generate().items():
        dest = ROOT / "candidates" / name
        if args.check:
            assert all((dest / n).read_bytes() == b for n, b in files.items()), name
        else:
            dest.mkdir(parents=True, exist_ok=True)
            for n, b in files.items():
                if (dest / n).exists() and (dest / n).read_bytes() != b:
                    raise ValueError(f"existing {name}/{n} differs; preserve it")
                (dest / n).write_bytes(b)
        print(json.dumps({"candidate": name, "hashes": json.loads(files["manifest.json"])["hashes"], "proof_status": "DRAFT_UNTESTED"}))


if __name__ == "__main__":
    main()
