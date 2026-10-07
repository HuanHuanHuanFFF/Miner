# Round 9: extracted length-reduction proof interfaces

Reviewed 2026-10-08 against run `37660750561`, batch `block-a`, source commit
`895ca6f98ef60e0f8cf2c082d619d45e68a2e60a`.
Receipt: `evidence/round9/37660750561/block-a/extraction/research.json`.
The receipt records `extraction_accepted=true`, `exit_code=0`, and
`proof_status=NOT_RUN` for both source candidates. This review does not report a
Lean gate result and did not change any candidate already dispatched to CI.

## Scalar: no definite interface defect found

**VERIFIED** from `r9-block-scalar/Funs.lean` under that receipt directory:

| Extracted declaration | Lines | Observed signature/state |
|---|---:|---|
| `d_bcost` | 5840–5852 | `(lc, ring, p, l)` returns U64 |
| `d_best_len_scalar_loop` | 5879–5888 | `(lc, ring, p, e, best, bl, l)`; loop state `(best,bl,l)`; result `(best,bl)` |
| `d_best_len_scalar` | 5893–5903 | `(lc,ring,p,lo,e)`; calls loop with `(best,lo,lo.wrapping_add(1))`, then packs |
| `d_best_len` | 5908–5918 | Same public signature; guarded scalar branch, otherwise original fallback |
| `d_best_len_old_loop` | 5817–5824 | `(lc,ring,p,e,bv,l)`; state `(bv,l)` |
| `d_best_len_old` | 5830–5835 | Calls old loop with `MAX_U64` and `lo` |

The scalar draft `Parse.lean` lines 2404–2461 use these same argument/state
orders. Its termination measure `e - l` uses the third scalar state field.
The renamed old-loop proof has the same two-state interface and the direct
wrapper term `d_best_len_old_loop_spec lc ring p e _ lo` agrees with actual
extraction. The dispatch theorem retains the unchanged `d_best_len_spec`
statement consumed by `d_cand_spec`.

No definite source/extraction interface mismatch was found for scalar. **UNKNOWN**:
its tactics compile, the original obligation is accepted, and the axiom/public
round-trip checks pass. Those results must come from the actual gate.

Saved scalar `Funs.lean` hash, checked against the receipt:
`bf2bbeaed1cb93e822c857778cb9b49b9eda85329904a5220d8b4b4da3364392`.

## Unroll4: one definite draft interface mismatch

**VERIFIED** from `r9-block-unroll4/Funs.lean`:

- Main loop lines 5913–5925 carry
  `(c0,c1,c2,c3,b0,b1,b2,b3,l)`, matching the nine-field draft theorem and its
  final-field termination measure.
- Scalar helper lines 6031–6040 and the old fallback lines 5817–5835 match the
  scalar and original fallback proofs.
- Tail-loop lines 5953–5960 take arguments `(lc,ring,p,e,l,bv)` and carry state
  `(l,bv)`, rather than the draft's assumed `(bv,l)`.
- Tail-loop body lines 5931–5947 increments `l` and returns `(l1,bv1)` on
  continuation. Wrapper line 6004 calls the loop with `l1` before `bv`.

The original unroll4 draft declares a call with `bv : U64` in the extracted
`l : Usize` argument position, and vice versa. That is a definite type/interface
mismatch found by inspection. It is not recorded as an executed Lean failure:
the first receipt explicitly says the proof was not run.

Saved unroll4 `Funs.lean` hash, checked against the receipt:
`e1444e6bfc52d5355c952f9fc0cc6bbb779e587ecf8d06fcf05544fe5a8a433c`.

## Separate corrected proof variant

After reporting the mismatch, the coordinator authorized the independent
`candidates/r9-block-unroll4-proof` directory and
`scripts/make-round9-unroll-proof.py`. The script verifies the exact saved
extraction hash and changes only the tail-loop theorem:

1. Declare/call `l` before `bv`.
2. Use measure `fun (l', _) => e.val - l'.val`.
3. Destructure loop state as `⟨l',bv'⟩`.

**VERIFIED** local generation and `--check` passed, including unchanged Rust
bytes, candidate hashes, exact reverse restoration of the old proof region, and
the file-size bound. The original `r9-block-unroll4` files remain unchanged.

| Corrected variant file | SHA-256 |
|---|---|
| Rust, same as original unroll4 | `5d9150e58309e599466bb084fb10eb370772bde3d08ae97775d6dcd0f26a1488` |
| Corrected proof | `8378f082d6c6dd44ba4f1158fe566bf2d3b89ab4347343b1a53dc91093e0ba6a` |

**UNKNOWN**: the corrected proof compiles or passes any official gate. This
variant was not dispatched by the reviewer. Public performance and the
coordinator's selection decision determine whether to spend a full gate on it.

## Tail filter: six-state interface confirmed

**VERIFIED**, 2026-10-08: run `37662165069`, batch `block-b`, source commit
`d6307730b0bf7a8534317efa1301232c7c25163e` saved a tail extraction with
`extraction_accepted=true`, `exit_code=0`, and `proof_status=NOT_RUN`.
Receipt: `evidence/round9/37662165069/block-b/extraction/research.json`.
The saved `r9-block-tail/Funs.lean` matches receipt hash
`d5f251223c15ad5e62f9dc9b92fa27717061d1362b8336c1369d584a9c5a1fc3`.

Observed interfaces in that file:

- Lines 2817–2827 define
  `d_walk_loop s prev i b8 cap cands nice nc best tw c k`, with mutable state
  `(cands,nc,best,tw,c,k)` and result `(cands,nc,best)`. This exactly matches the
  candidate's six-state theorem call, invariant pattern, and final-field depth
  measure.
- The loop body's captured environment at 2756–2760 places `nice` before its
  mutable `cands` argument. The extracted wrapper itself supplies that order at
  2825–2826; the proof unfolds this body and makes no manually ordered body call.
  The public loop function still takes `cands` before `nice`, as drafted.
- Lines 2832–2842 retain the public `d_walk` parameters
  `(s,prev,i,start,depth,b8,cap,cands,nc0,best0,nice)` and result
  `((nc,best),cands)`. The postcondition projections in `d_walk_spec` remain
  correct.
- The caller pair at lines 4763–4787 still binds `((nc,best),cands)` and passes
  the original `b8`, full `cap1`, candidate state, and final `nice` argument to
  both chains. The other extracted D caller branches use the same signature.
- Body lines 2771–2775 retain `best < cap`, `best < nice`, and `nc < 15` guards.
  Line 2782 still calls `probe s c i b8 cap best`; line 2794 refreshes the cached
  tail with `tailw s i l` after a successful longer match.

The candidate proof hash remains
`2b2fab469bc1acf3fc87f424e323392c82e5c40fd778e4e12bcd94b259f387ba`.
No definite interface error was found, and this review changed only this report.
**UNKNOWN**: tail's Lean tactics, original obligation, axiom checks, and full
public round trip pass; extraction acceptance alone does not establish them.
The coordinator's scheduled full gate will supply the proof outcome.

The corrected unroll4 proof remains UNKNOWN. The coordinator deferred its
additional gate after the public performance screen; the correction is retained
as an unverified proof artifact, rather than counted as an accepted candidate.
