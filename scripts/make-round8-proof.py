"""Draft totality lemmas for Round 8's distance-price helpers.

This module changes proof text only. The helper loop interface is inferred from
the Rust body and the Round 7 Aeneas extraction pattern; a fresh Round 8
extraction and the official obligation/axiom gate are still required.
"""

from pathlib import Path
import argparse
import hashlib
import json


ANCHOR = "@[local step]\ntheorem rc_seq_loop_spec"

TOP = """-- Round 8 helper: totality only; candidate/cost optimality is not assumed.
@[local step]
theorem rc_pick_top_spec (cands) (nc k0 : Std.Usize) (dtab dcc) :
    slot.rc_pick_top cands nc k0 dtab dcc ⦃ fun _ => True ⦄ := by
  rw [slot.rc_pick_top]
  step*
  repeat' (split <;> step*)
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

"""

SUFFIX = """-- Round 8 helper: totality only; candidate/cost optimality is not assumed.
@[local step]
theorem rc_pick_suffix_loop_spec (cands) (nc : Std.Usize) (dtab dcc)
    (chosen price : Std.U32) (k : Std.Usize) :
    slot.rc_pick_suffix_loop cands nc dtab dcc chosen price k ⦃ fun _ => True ⦄ := by
  rw [slot.rc_pick_suffix_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, _, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨chosen', price', k'⟩ _
    simp only [slot.rc_pick_suffix_loop.body]
    step*
    repeat' (split <;> step*)
    all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
  · trivial

@[local step]
theorem rc_pick_suffix_spec (cands) (nc k0 : Std.Usize) (dtab dcc) :
    slot.rc_pick_suffix cands nc k0 dtab dcc ⦃ fun _ => True ⦄ := by
  rw [slot.rc_pick_suffix]
  step*
  all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))

"""


FULL_DEAD_LO = """@[local step]
theorem rc_seq_loop_spec (input : Slice Std.U8) (pa cands nc lc dtab dcc) (i s : Std.Usize) (base : Std.U32)
    (pcd tmax k : Std.Usize)
    (hi : i.val < input.length) (hN : input.length + 2147483648 ≤ Std.Usize.max) :
    slot.rc_seq_loop input pa cands nc lc dtab dcc i s base pcd tmax k ⦃ fun _ => True ⦄ := by
  have := dp_RING_val
  have := dp_BEXT_TOP_bound
  rw [slot.rc_seq_loop]
  apply Std.loop.spec_decr_nat
    (measure := fun (_, k') => 16 - k'.val)
    (inv := fun _ => True)
  · rintro ⟨pa', k'⟩ _
    simp only [slot.rc_seq_loop.body]
    step*
    have := dp_shr9 c
    apply WP.spec_bind (Pₘ := fun _ => True)
    · repeat' (split <;> step*)
      all_goals (subst_vars; scalar_tac (simpAllMaxSteps := 0))
    · intro pa2 _
      step*
  · trivial

"""


def adapt_full_dead_lo(proof: str) -> str:
    """Opt-in draft for extraction that removes unused `lo` from full's loop.

    Use only after fresh extraction confirms `rc_seq_loop` has no `lo` argument
    and its mutable loop state is `(pa, k)`. This is separate from `adapt`, whose
    default `full` behavior remains byte-preserving for the dispatched candidate.
    """
    newline = "\r\n" if "\r\n" in proof else "\n"
    anchor = ANCHOR.replace("\n", newline)
    end_anchor = "@[local step] theorem rc_seq_spec".replace("\n", newline)
    replacement = FULL_DEAD_LO.replace("\n", newline)
    if proof.count(replacement) == 1:
        return proof
    if proof.count(anchor) != 1 or proof.count(end_anchor) != 1:
        raise ValueError("expected one rc_seq_loop_spec and rc_seq_spec boundary")
    start = proof.index(anchor)
    end = proof.index(end_anchor, start)
    original = proof[start:end]
    if "(pcd tmax lo k : Std.Usize)" not in original:
        raise ValueError("input does not contain the reference three-state loop proof")
    patched = proof[:start] + replacement + proof[end:]
    if len(patched.encode("utf-8")) > 524288:
        raise ValueError("generated proof exceeds the official file-size bound")
    return patched


def adapt(proof: str, label: str) -> str:
    """Insert helper totality lemmas before the unchanged rc_seq proof.

    `full` preserves the reference proof text exactly. `top` and `suffix` are
    drafts until their generated interfaces and fresh gate results are checked.
    The operation is idempotent for a proof already produced by this function.
    """
    if label not in ("full", "top", "suffix"):
        raise ValueError(f"unknown Round 8 proof label: {label}")
    if label == "full":
        return proof
    # Preserve the input's newline convention for byte-traceable generation.
    newline = "\r\n" if "\r\n" in proof else "\n"
    anchor = ANCHOR.replace("\n", newline)
    if proof.count(anchor) != 1:
        raise ValueError("expected exactly one reference rc_seq_loop_spec anchor")
    helper = (TOP if label == "top" else SUFFIX).replace("\n", newline)
    marker = f"theorem rc_pick_{label}_spec"
    if marker in proof:
        if proof.count(helper) == 1:
            return proof
        raise ValueError("existing helper lemma differs from the Round 8 draft")
    if "theorem rc_pick_" in proof:
        raise ValueError("input contains a helper lemma for another variant")
    patched = proof.replace(anchor, helper + anchor, 1)
    if len(patched.encode("utf-8")) > 524288:
        raise ValueError("generated proof exceeds the official file-size bound")
    return patched


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--label", required=True, choices=("full", "top", "suffix"))
    parser.add_argument("--input", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--full-dead-lo", action="store_true",
                        help="Opt in to draft full proof with extracted (pa,k) loop state")
    args = parser.parse_args()
    if args.full_dead_lo and args.label != "full":
        parser.error("--full-dead-lo applies only to --label full")
    raw = args.input.read_bytes()
    proof = adapt(raw.decode("utf-8"), args.label)
    if args.full_dead_lo:
        proof = adapt_full_dead_lo(proof)
    patched = proof.encode("utf-8")
    if args.output.exists() and args.output.read_bytes() != patched:
        raise ValueError("output exists with different bytes; choose a new output")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(patched)
    print(json.dumps({
        "label": args.label,
        "full_dead_lo": args.full_dead_lo,
        "source_sha256": hashlib.sha256(raw).hexdigest(),
        "proof_sha256": hashlib.sha256(patched).hexdigest(),
        "proof_bytes": len(patched),
        "status": "DRAFT_UNTESTED_OFFICIAL_EXTRACTION_AND_LEAN_REQUIRED",
    }))


if __name__ == "__main__":
    main()
