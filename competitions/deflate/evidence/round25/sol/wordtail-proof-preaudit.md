# Wordtail minimal proof pre-audit

**DRAFT: no wordtail extraction, Lean compile or full gate has run.**
The original candidate directory remains frozen. Native444 finite
token/decode equality and all28 token/output hash pairs are verified
separately; they do not establish this proof.

The new `r25_pc_slot_word` has no input slice or mutable state. Its only
needed contract for the parser safety proof is a valid hash-table slot:

```lean
-- Source-inferred interface sketch; actual Funs must decide argument order.
@[local step]
theorem r25_pc_slot_word_spec
    (H : Std.Usize) (word km : Std.U32) (hH : 0 < H.val) :
    slot.r25_pc_slot_word H word km
      ⦃ fun a => a.val < H.val ⦄ := by
  rw [slot.r25_pc_slot_word]
  step*
```

This follows the parent `PC.slot_of_m_spec` pattern, minus its byte read.
The existing constant `pc_HB=15` supplies the legal U64 shift count; the
wrapping multiplication and cast are total, and remainder by positive H
gives the required bound. The exact tactic behavior is still untested.
This lemma should be inserted before `PC.f_record3_spec` in a new proof
pair only if actual total time justifies a gate.

`pc_f_record3` keeps its signature. The recording loops occur before the
local `tail_a` declaration or in the untouched non-TAIL1 branch, so no
additional captured loop state is intended. The actual extracted
headers must confirm that before relying on the parent loop specs.

For the new direct reads, `j=end-4<lim` and `lim+8=s.length<=Usize.max`
provide `j+8<=Usize.max`; the existing `PC.be8_spec` handles the word.
The first slot is bounded by the new helper lemma. The cached tail branch
explicitly tests `tail_a<H`, so `f_link_spec` can consume that bound
without proving semantic equality of the two key extractions. Its
position/HeadBound obligations are unchanged from the original tail.

The parser's correctness obligation does not need to prove that this hash
is equal to the parent hash: arbitrary bounded hints are subsequently
byte-validated. Exact hash/trace equality belongs to the separate quality
check. The public token/encoder parity supports the observed28 inputs,
while the real full gate would verify original obligation and axioms for
all allowed inputs on the exact Rust/Lean pair.

If paired total time remains insufficient, preserve this pre-audit and
stop full proof spending for this version. No timing benefit is inferred
from the small lemma or from the number of source loads.
