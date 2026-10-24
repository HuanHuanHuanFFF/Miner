# R11-W01 independent rows/core audit

Status: SOURCE_INSPECTION. Pinned Lean compilation NOT_RUN. No replacement of this section is justified by the inspected text alone.

Exact source: `Kernel.original.lean`, SHA256 `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`, 252609 bytes.

## Findings

1. `blockRows_word` is a concrete address theorem. It does not assume an abstract packing specification. Four cases of `r : Fin 4` reduce `select4`; `blockAt_word` then retains `A.getD ((4*g+r)*n+k)` and `B.getD (((4*g+r)/m*n*p+j)+k*p)` inside the actual `NativeFinal.dot`. The B batch base is recomputed for each row, including crossings inside one group.
2. `rowWord_eq` has precisely the needed two Euclidean identities: `4*(r/4)+r%4=r`, and `(r/m)*m+r%m=r`. The former reconstructs the actual selected global row; the latter aligns with the original DirectRows address. `Nat.div_add_mod` remains valid when m=0; the public rowWord domain then has no inhabitant if batch*m=0.
3. `core_eq_rows` uses `Vector.ext` and an inhabited output index q to derive p>0, then q/p<batch*m and q%p<p. It never assumes p>0 globally. Its simplification list mirrors the retained, source-local `DirectRows.core_eq`: `Vector.getElem_ofFn` and `Vector.getElem_flatMap`. The proof terms in the two constructions of the same Fin indices are irrelevant. The resulting NativeFinal.dot arguments agree literally after these reductions.
4. `bmm_spec` is a concrete theorem chain: R11 core -> DirectRows.core -> DirectSmall.core -> referenceBmm -> original bmmSpec, including the original `.get` function equality. No abstract read obligation is added.

## Machine premises

The new USize loop indexes ONLY the prepared P12 vector `v` of length n. The dispatch extracts `h.2.2.2.1 : n < USize.size`; `(USize.ofNat n).toNat=n` follows by the exact source-local lemma call. Each `uget` obtains k.toNat<n from k<count and then rewrites v.size_toArray. The increment is justified by the source-local `Packed10Index.stepNat` / `next_decreases`, whose proof uses k<count and count.toNat<USize.size. This does not assume wraparound away.

Raw A and B addresses in packGeneral/packShared and replay are Nat indices to total `Array.getD`, not unguarded casts to USize. Tail indices therefore do not require all four hypothetical rows to fit either input's machine bound. Imposing that condition would be stronger than this implementation needs and could reject valid tails. A/B/output machine-length checks are explicitly present in dispatch; the proof of the only new uget needs n's bound plus its exact vector length.

For an emitted row r<batch*m and k<n, the actual A address is r*n+k<batch*m*n. For m>0, b=r/m<batch; with j<p, the actual B address b*n*p+j+k*p=(b*n+k)*p+j<batch*n*p. These follow from the same q/r index conditions used by the existing original-reference bridge. Unused tail lanes are never selected by rowWord, so their values are irrelevant even without proving they are zero.

## Zero dimensions and arbitrary Nat

- m=0 or batch=0: the new dispatch guard `4 <= batch*m` is false, so original fallback executes. Standalone R11 core has output length zero, and Vector.ext has no q to inspect. Division by m is never needed to extract an existing output.
- p=0: p=2 guard is false. Standalone core's lambda domain is empty; the local proof of p>0 follows from an output index only and does not assert 0>0.
- n=0: new `0<n` guard is false. The R11 theorems themselves still hold for n=0 under n<USize.size: pack is empty, wordLoop is at its base case, each lane begins +0, and exact finish matches empty ordered dot.
- n>=USize.size: new branch is rejected, even if a multiplication dimension happens to be zero.
- Arbitrary larger Nat dimensions: no proof may infer absence of machine wrap from a finite test. This branch uses explicit bounds; fallback retains its original arbitrary-Nat proof.

## Concrete crossing witness (mathematical construction, not execution)

Take batch=2, m=3, n=1, p=2, A=[1,1,1,1,1,1], B=[1,2,4,8]. Group 0 contains global rows 0,1,2,3 and B bases 0,0,0,2. Correct row 3 is [4,8]; a wrongly shared b0 would give [1,2]. The actual pack guard rejects sharing because b3 != b0. Group 1 contains rows 4,5 and two unused rows; only its first two rows are emitted. All these values are exactly representable binary32; no reduction reassociation is involved.

## Remaining formal acceptance

All listed local simplifications, Vector projections, and theorem invocations remain NOT_RUN in this environment. `RowEdgeCases.lean` is an optional appended diagnostic fragment, not a submission repair, and has not been compiled. It introduces no runtime definition or extra axiom. Do not count it as acceptance or add it to the <=256000-byte submission unless needed for local diagnostics.

Public pinned Lean source retrieval was attempted for Vector.Lemmas and Nat.Div.Lemmas. Web retrieval returned DisabledError and exec urllib returned Operation not permitted; no API assertion is based on those unavailable external contents.

## Optional proof-only normalization fallback and actual read theorem

`RowProofFallbacks.lean` supplies (1) the exact existing rowWord_eq statement and body with two explicit `dsimp only` checkpoints added around `rw`, solely to expose let/projection normalization if a real elaborator reports such a mismatch; and (2) a concrete selected-read bounds theorem over the actual A/B vectors. The latter derives m>0 from the inhabited r, b=r/m<batch by the same Nat.div_lt_iff_lt_mul API already used in the source, then uses the source-local pattern Nat.mul_le_mul_right to bound A and B. It is no abstract correctness assumption. Both are NOT_RUN; neither is needed to justify a zero-edit recommendation from source inspection.
