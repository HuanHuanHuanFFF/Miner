# R11-W02 — Ordered dot-product summaries for zero / one-nonzero B columns

Date: 2026-10-24. Status: mathematical analysis and finite category checker delivered; new Lean bridge **NOT_RUN**; full-call performance **NOT_RUN / UNKNOWN**.

## Evidence boundary

The uploaded source is a line-numbered text export (263,896 bytes), not the raw 252,609-byte `Kernel.lean`. Its embedded header reports candidate SHA256 `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`, parent `a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78`. I cannot independently validate those raw-source bytes from this export, so its own SHA is not claimed as Kernel SHA.

Concrete declarations already present in the supplied source:
- `R7W01.mul32_not_snan`: actual binary32 `Model.Spec.mul` never returns an sNaN.
- `R7W01.add_mul_absorb`: a left qNaN absorbs `Spec.mul x y` under actual `Spec.add`, preserving the complete model value/word.
- `R7W01.add_absorb_of_not_snan`: concrete `chooseNaN2` bridge; a left qNaN is displaced only by a signaling right operand.
- `R7W03.model_add_of_right_snan`: a right sNaN can take priority if the left is non-signaling. The dot theorem is safe because the right operand of each add is a multiplication result, proven non-signaling.
- `R7NaNReplay.replayFold_absorb`, `replayLoop_eq`, `NativeFinal.dot_eq`, `Packed10.finish_eq_fold`, and `R11CrossRows.blockAt_word` provide existing runtime/fold bridges. Not recompiled this turn.

## Theorem 1: a B column of arbitrary signed zeros

For one A row, every `B[k]` is `+0` (`0x00000000`) or `-0` (`0x80000000`). Let t be the least k for which A[k] is non-finite (NaN or infinity), if one exists. The original ordered dot from +0 is exactly:

1. If no t exists: `0x00000000` (+0).
2. If A[t] is NaN: the full word of `quietNaN(A[t])` (set quiet bit, preserve sign and all other payload bits).
3. If A[t] is infinity: FloatLib `invalidResult`, binary32 canonical qNaN `0x7fc00000`.

**Proof.** A finite value times signed zero yields signed zero. Under RN-even, `+0 + +0 = +0` and `+0 + -0 = +0`, so the finite prefix remains +0; this exact zero rule must be proved from actual FloatLib addition, not real arithmetic. If A[t] is NaN, actual `chooseNaN2` selects and quiets A[t], since B[t] is not NaN. If A[t] is infinity, infinity-times-zero is invalid and produces `invalidResult`. Both results are qNaNs. By `mul32_not_snan`, every later product is non-signaling, even when later A contains an sNaN (multiplication quiets it first). `add_mul_absorb` then proves each later ordered addition leaves the earlier qNaN word unchanged.

Minimal summary: `AllFinite`, `FirstNaN(index, quietedRawWord)`, or `FirstInfinity(index)`. It is independent of B's zero-sign pattern and can be shared across multiple all-zero columns of the same A row.

## Counterexamples to over-simplifications

- **Omit infinity:** A=`[+∞]`, B=`[-0]` gives canonical qNaN `0x7fc00000`, not +0.
- **Only store `hasNaN`:** A=`[sNaN(payload=1), +∞]` versus `[+∞, sNaN(payload=1)]`, B all zero. First returns quieted A NaN payload; second returns canonical invalid qNaN. Category and order matter.
- **“Original NaN always wins” is false:** A=`[+∞, sNaN(payload=1)]`, B all zero. The first invalid qNaN absorbs the later quieted NaN product.
- **Apply zero summary to a general column:** A=`[3.0]`, B=`[2.0]` yields 6.0.
- **Unconditional qNaN left absorption is false:** FloatLib allows a right sNaN to win under `chooseNaN2`. The dot theorem is safe because the right operand of each add is a product and `mul32_not_snan` rules out sNaN.

## Theorem 2: exactly one nonzero B element

Suppose exactly one B index r is nonzero; all other B[k] are signed zeros. Split A in original order into prefix `k<r`, center r, suffix `k>r`.

- If the prefix contains a first non-finite A[t], t<r, the prefix has already produced a qNaN. The actual center product is non-signaling, so cannot replace it; return the prefix summary.
- If the prefix is all finite, it leaves +0. At r execute actual `Spec.mul A[r] B[r]` then `Spec.add`; do not approximate this step. A[r]=NaN requires actual NaN selection/quieting; A[r]=infinity and nonzero B gives signed infinity (not infinity-times-zero invalid); finite multiplication may underflow or overflow.
- If the center result is qNaN, the suffix is absorbed.
- If the center result is non-NaN, the first suffix non-finite A multiplied by zero produces qNaN and replaces the non-NaN accumulator. If the suffix is all finite, prove its signed-zero additions preserve the reachable center result bits.

Thus `prefix summary + exact center step + suffix summary` is a plausible narrow extension, **not yet a closed theorem** until the final bit-preservation obligation is proved for actual reachable accumulator states. The suffix needs its first non-finite index strictly after r, not a global first-exception bit.

## Minimal Lean bridge and obligations

Reuse the concrete declarations, not an abstract IEEE model:

```lean
R7W01.mul32_not_snan (x y : M32) : isSNaN (Spec.mul x y) = false
R7W01.add_mul_absorb (q x y : M32)
  (hq : isNaN q = true) (hs : isSNaN q = false) :
  Spec.add q (Spec.mul x y) = q
R7NaNReplay.replayFold_absorb
  (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
  (k : Nat) (acc : Binary32)
  (hq : R7W01.execQuietGuard acc = true) :
  Fin.foldl.loop n (replayStep n baseA baseB p Araw Braw) acc k = acc
```

Proposed summary type (new, uncompiled):

```lean
inductive ZeroProductSummary
  | allFinite
  | firstNaN (k : Nat) (quietWord : UInt32)
  | firstInfinity (k : Nat)
```

`classifyZeroColumn` must scan raw A words in ascending k, select the least exponent-255 index, distinguish NaN (`fraction != 0`) from infinity (`fraction = 0`), and prove the raw quiet word agrees with actual `Model.quietNaN`.

Required bridges: (1) finite A × signed-zero B equals sign-xor zero word in actual `Spec.mul`; (2) actual ordered zero-product prefix from +0 stays +0; (3) summary result equals actual `Fin.foldl` bit-for-bit; (4) selected index is minimal and preceding A entries are finite; (5) summary finish uses original raw-word/`ofBits32` route, not native NaN canonicalization; (6) single-nonzero extension proves exact center step and bitwise suffix invariance for reachable states.

`R7NaNReplay.replayFold_absorb` is reusable after a qNaN is established; it does not prove classifier correctness or the finite +0 prefix. New Lean proof **NOT_RUN**.

## Cost and amortization

Let R be flattened output rows, P columns, N reduction length, Z all-zero columns, C per-term cost, S row-summary scan cost, F output word construction. Symbolically:

- baseline: about `R*P*N*C` plus current packing/output work;
- summary path: `R*N*S + R*Z*F + R*(P-Z)*N*C + scanB + dispatch + allocation/fallback`.

A rough win condition is `Z*N*C > N*S + Z*F + scanB-per-row + dispatch + allocation/fallback`. This is accounting, not latency prediction. Count scanning B to detect zero columns; scanning B and then rereading it in the packer may erase gains. A summary shares across zero columns of the same A row, not across distinct A rows unless their raw words match. Most promising: many all-zero columns per row and large N. Likely weak: small P/N or few zero columns.

For one-nonzero columns, prefix/suffix scans can still be O(N) per row/column. It pays only if sparsity is cheaply known in bulk, A scans are reused across columns, or summary construction fuses with input packing. Count B scan, A scan, summary storage, output construction, raw reads, fallback, batch-tail work, allocations and destruction.

## Falsifiable experiment

`check_r11_w02.py` exhaustively checks a bounded category model, **not** FloatLib execution. Formal/device tests must compare raw UInt32 output words. Sweep zero-column density 0%, one column, 50%, 100%; A all-finite, first sNaN, first qNaN, first infinity, infinity before later sNaN. For one-nonzero columns put r at first/middle/last and non-finite A before/at/after r. Record B scan, A summary, output construction, fallback and full-call times; pair/interleave baseline and candidate. Do not touch hidden confirmation inputs.

## Conclusion

The all-signed-zero column shortcut is mathematically sound if it preserves the earliest non-finite category and quieted raw NaN word, and the actual signed-zero prefix theorem is closed. It offers the cleanest reuse: one summary per A row for many zero columns.

The one-nonzero extension is promising but conditional: keep the center step exact and prove the reachable-state suffix bridge. Lean compilation, full gate and performance are **NOT_RUN**; performance is **UNKNOWN**.
