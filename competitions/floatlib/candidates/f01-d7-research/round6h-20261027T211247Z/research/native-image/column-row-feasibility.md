# Local certificates: preserve as interfaces, no current full implementation

This supersedes the single-global-B Bool as the active proposal. That Bool is correct but conservatively rejects unrelated columns and batches. It is retained in `FusedPreparedB.lean.inc` only as the earlier scoped sketch.

**Current decision: mathematical/interface reserve only.** The controller's bounded check on two already-seen R22 discovery seeds sampled 155 outputs using 17037 word reads / 6251 MACs. It found 4 / 1 locally certified NaN samples; the complete cases touched by those samples account for 0.4468% / 0.1557% of whole time. No sampled positive was additionally rejected by global-B certification. These are neither a full-exposure upper bound nor removable time, a success probability, or private-suite evidence. They do not support a 10% whole-package opportunity. See the exact controller `local-nonnan-certificate-exposure.json` hash in this directory's manifest.

## Exact corrected predicate

For output `(batch b, row r, column j)`, use `rowNoNaN[b,r] && colNoNaN[b,j]`. A four-row group can carry four bits in one scalar UInt8, initially 15, ANDing the four current raw-input classifier bits once per k. The mask is separate from the per-column accumulation Cell. B has `batch*p` Bool flags, initially true, ANDed only by values in that same batch and column.

The smallest whole-matrix illustration is A=[Inf], B=[payload-qNaN,0]. The second column is a valid T19 invalid result despite the global B flag being false. `column-row-counterexamples.json` embeds the same issue inside the **actual quad guard** at batch=1,m=4,n=2,p=2: every A row is [Inf,1], and B rows are [payload-qNaN,0] and [1,1]. The four column1 results are canonical NaNs with valid local certificates; global B admits none. This demonstrates conservatism, not a correctness bug in the old global certificate, and is not a workload-frequency estimate.

## Minimal iteration sketch and interfaces

`ColumnRowSummary.lean.inc`, **3978 B / 14e59b3f**, is **NOT_RUN**. It supplies:

- A single row-major B preparation loop with scalar row/column/batch-flag-base counters, avoiding per-element division/modulo. The native output array and flag array are separate recursive arguments; the result structure is only constructed at exit in the source.
- The explicit `Ready` contract: the raw length equals batch*n*p; prepared values equal the *old whole map* exactly; flags have length batch*p; `colSafe[b*p+j]=true` iff every original B read in that column is nonNaN.
- Four conditional interfaces: `getD_of_ready`, `column_read_not_nan`, `column_dot_read_not_nan`, and `row_read_not_nan`.
- `rowMaskStep` and an explicit `RowMaskReady` contract, preserving four distinct row identities and the exact raw A bases.

**Missing:** no theorem proves that `prepare` produces Ready, nor that an integrated A4 loop produces RowMaskReady. The sketches must not be represented as verified certificates. The B invariant must connect `sourceIndex`, row, column and flagBase to the same row-major source index, preserve converted-prefix order, and conjoin exactly the processed members of each column. The A invariant must show each mask bit is the conjunction for that row's processed k prefix. Mask OR is wrong because a later safe input would restore a failed bit.

The 355 small structural configurations check only array order/column-index bookkeeping, including n/p=0 and multiple batches. A mutant forgetting batch identity fails at batch=2,n=1,p=1 with a NaN only in batch1. This is bounded host evidence; it is not Lean or execution of the new runtime.

`DotImageInterface.lean.inc` remains usable unchanged. Given the actual native-loop result equality from the quad lane proof and the exact row/column read hypotheses, its `direct_import_eq_finish` proposition replaces the old finish by native import for all results, including NaN. Existing W12 supplies the arithmetic closure already present in B2; no new axiom or cross-width cast is used.

## Complete overhead and reopen condition

The B loop adds a `batch*p` flag-array initialization, a flag read/AND/write for every B element, raw classification, loop counters and control. Array Bool uses array slots; it must not be described as a one-byte bitmap or free immediate storage. Input data is not revisited, but the flags are revisited once per k. COW or accidental retained aliases can turn a cheap intended update into copying; actual C/ASM must establish unique reuse. The source's final-only structure does not establish allocation behavior.

A adds four raw classifications per k/group, construction of a four-bit mask, and a scalar mask dependency. Current `advance` owns its A loads, so a real fusion must share those loads with the mask producer rather than adding a second read/decode pass. Refactoring that runtime invalidates old source hashes and requires new lane refinement.

At finish, each row bit can be tested outside its emit. A certified row still needs a per-column flag load/branch unless another separately justified representation removes it. This may cost more than the endpoint's existing floating nonNaN comparison on ordinary outputs. Certified NaN results avoid only the existing *quiet-stop replay prefix*, not a hypothetical full n-step replay. Native import, all output writes, and rejected-certificate fallback remain costs.

Do not reopen a whole-table scan, add per-step native NaN-event tests, introduce Thunks, or select cases by benchmark labels. D's current cost3 and the underlying quad/prepared representation take priority. Reconsider only after that representation has a substantial signal and D can include this certificate experiment at low marginal cost in a complete caller comparison. No new queue is requested.
