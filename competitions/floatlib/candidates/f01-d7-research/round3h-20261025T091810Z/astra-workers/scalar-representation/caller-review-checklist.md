# Selected-caller check for c972 native repack

Read only the exact candidate's selected MainFull scalar MUL caller and/or linked helper, after confirming the input SHA. Statement-generated C is implementation evidence; timed ELF identity and dynamic cost are separate.

For the exact B2 diagnostic build40168024176, public `BENCH_PLAN` selects `_lean_main -> closed__5 -> main___lam__3___boxed -> main___lam__3`; `lam__1` is used by the legacy Bench.runFull branch. New generated indices may change, so trace closures again rather than assuming this suffix. Baseline identity and excerpts are in `b2-caller-review.json`.

1. Normal arm: two UInt32 numeric casts, one Float32 MUL, one `toBits`, integer field extraction/repack. `core` binds `mid` once; `outputExponent` is a proof-facing helper and must not cause a second runtime multiplication. The copied `Nat`/`Model` math must be erased from the selected arm.
2. Expect no scaleTable reads and no second/third Float32 multiply in that arm; the original fallback legitimately still contains those operations. Count by reachable branch, not global function occurrence totals.
3. Guard: original exponents1..254 and sum128..380. Confirm no signed-width confusion in `exu-1`, and that late subtraction300 is integer word arithmetic following midpoint exponent extraction. Positive midpoint exponent173/174 keeps the final exponent1..254. Current signed Bool uses original proven sign helper.
4. `toBits` remains an external fixed-runtime call with its own NaN normalization check. No claim of removing that call, spill/restore, integer-to-float latency or all branches. It returns the actual rounded midpoint, not the exact48-bit product.
   B2's normal C call is in tail position; c972 uses its result for integer repacking, so check whether the new caller must save exponent sum/sign across an actual call. Tailcall/spill difference is a hypothesis until the exact selected object is inspected.
5. Original low-scale/nonfinite/zero/out-of-band routes must remain selected through B2 fallback. Test all original four operations; the altered public MUL also appears in raw replay/reference paths even though native packed BMM hot loops keep their own operations.
6. Retain ADD/SUM and slow whole samples. R15 already exhibited changed whole/ADD time with identical generated ADD source; do not excuse new regressions as harmless code layout or CPU noise without discriminating evidence.

This checklist does not create a new measurement or authorize CI. D remains the sole run owner. c972 is unchanged while awaiting compiler feedback.
