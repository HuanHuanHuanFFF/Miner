# Shared dynamic-carry interface review

Read C's `CheckedCarry128.lean`, `NormMomentRuntime.lean`, and
`norm_dynamic_guard.py` during the wait for the frozen word-modular repair.
This is a source/mathematical review; no new compile or speed claim.

- `add_sound` is the useful common leaf: split the low-word carry, check
  high+carry and then high+addend. Both monotone-add checks are required;
  checking only the final high word can miss an intermediate wrap.
- For the moment runtime, mantissa<2^24 and accepted shift≤40 imply each
  square<2^128. The two shift branches cover 2s<64 and64≤2s≤80; the right
  shift split avoids the machine shift-by64 problem. A static span40 change
  alone is unsound, as C's255-element134-bit witness demonstrates.
- The Lean runtime checks positive and negative first-moment additions as
  well as square additions. Therefore successful dynamic addition can remain
  sound beyond n<256. Its `prepare` currently has **no n<256 check**.
- The Python model explicitly rejects n≥256 and only dynamically checks
  square-sum overflow; within n<256 and shift≤40, each first-moment total is
  <2^72, so omitting its dynamic check in that scoped model is justified.
  The finite model is consequently not literal all-branch replay of the
  supplied Lean helper. Keep its “n≥256 fallback” claim scoped to the model
  or future caller, not to `NormMomentRuntime.prepare` as written.
- Inline Option/pair construction followed by immediate matching may or may
  not disappear. Only actual generated C establishes the allocation shape;
  arithmetic-step counts cannot replace that check.

No integration changes requested before C/D's waiting native evidence. A
compiled checked-add leaf could be reused by a future positive/negative
word-block carrier; the existing signed modular carrier remains distinct.
