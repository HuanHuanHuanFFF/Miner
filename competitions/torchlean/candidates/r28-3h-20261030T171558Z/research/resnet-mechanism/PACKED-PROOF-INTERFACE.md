# Packed-support integration: remaining exact obligations

Processed root request174700. No extra variant or broad proof queue is being added. `6bf92e5f/252199B` remains a native-only prototype; `c6a4da97/252334B` remains the complete-claim source awaiting its original gate. The prototype's original base theorem is explicitly renamed; the new `Submission.kernels` has no `Submission.correct`.

`PackedFoldBridge.lean` states the minimum actual arithmetic interfaces with UInt64, not a floating-point approximation:

1. `step_zero`: for arbitrary encoded weights, both source11 split products vanish at encoded X=2^57; the four UInt64 accumulators stay unchanged.
2. `compressed_fold`: filtering exactly those terms preserves all four modulo64 accumulators from any starting state; no accumulation-order or exponent premise is required for this equality.
3. `scan_one_window` / `all_windows`: live encodings with exact decode and no zero collision can be concatenated with sentinel0. Each emitted `(position,state)` equals the full original window fold, with reset at the correct position.
4. `finalizer_unchanged`: the same original `Yq5`, bias parameters, `zW` full signed-zero replay and activation consume those identical states/positions. No new bias rounding or zero-sign claim is introduced.

`PackedSupport.lean` supplies uncompiled Int/Nat payload/index/bound formulas and the older generic integer omission lemma. `PackedFoldBridge.lean` strengthens the omission interface to the actual four UInt64 words. All statements are source drafts; no compiler or axiom receipt exists.

The producer/array obligations still open are specific and checkable:

- Under the wrapper's kh=kw3,stride=pad1,h>0,w>0, derive ho=h,wo=w; `row=(c*(h+2)+y)*(w+2)+x` plus dy/dx matches source11's padded `Ybi` and `Ys` offsets.
- Original `Ybg` admits |X|<2^55. Extra K=9*cin<128 gives t<128, hence packed value is strictly in(0,2^63); source UInt64 shift/or/sub/toNat refine the Int/Nat formula without wrap/collision.
- The nested array-builder emits exactly each window's filtered terms in original channel/row/column order, then sentinel0, including fully empty windows.
- The Nat fuel/index loop over `packed.size` matches `scan`; its two output arrays preserve channel-major order, including odd cout where the second channel is deliberately not emitted.
- The final kernel equality is conditional on the new generic shape/zero-density/numerical guards and uses the untouched original fallback otherwise. Combining with baseCorrect closes all12 only after these obligations and exact new-source gate succeed.

Performance remains UNKNOWN. Prep copies overlapping live terms, reserves full K+1 capacity, and later frees the cache inside inference. Nat loop, bounds checks, density pass, allocation and fallback prepasses are all part of the prototype's measured path; none may be excluded from a native discriminator. Do not undertake the expensive producer/array proof before a useful complete-path cost signal.
