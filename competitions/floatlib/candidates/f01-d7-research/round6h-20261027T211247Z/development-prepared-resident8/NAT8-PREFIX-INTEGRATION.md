# Concrete remaining Prefix joins

Read-only review at03:03Z found the needed generic writer interfaces already exist in A's scope. Do not reimplement them under a different name. All three files below still state NOT_RUN; their availability is not acceptance of raw8.

| Existing file under ../research/streaming-public | SHA256 | Bytes | Root needed |
|---|---|---:|---|
| FourWriterDirect.lean.inc | dfd9d0c0e72d8403fdc79dc33465872100f8dba9eb1312e7254565dbbc252e8f |1720| Submission.R22BlockWriter.emit_four_rows_prefix |
| FlatRowWriter.lean.inc |3287a582f4a8d6b380eb9ca3a690938b5a4271fbfc8b5c16a58302d47644274d|1842| Submission.R22BlockWriter.emit_flat_rows_prefix |
| BlockWriter.lean.inc |b6f6149f9ecaf9995c13447332839057b01e9b104a32c3254bc476da5f12bd2e|5932| Submission.R22BlockWriter.batch_fold_prefix |

The original raw8 `rows` uses **one flat tail emitter**, not a Fin.foldl over tail rows. Therefore `blocks_tail_prefix` is not the exact tail interface for this source. Use the original block fold invariant followed by `emit_flat_rows_prefix`. This avoids assuming equality of two unproved writer implementations.

1. For `b : Fin batch`, `r : Fin (m/4)`, let row offset=`4*r.val`, A base=`(b.val*m+offset)*n`, B base=`b.val*n*p`, cache base=`b.val*n*groups p`. The existing block bound gives offset+4≤m. Do not form blocks across batch boundaries.
2. For `j : Fin p`, use `g=j/2`, `c=j%2`. The pending `column_parts` supplies g<G, c<2, 2g+c=j and c=1⇒2g+1<p. Apply pending `cacheView_hread` at b,g,c to the **actual** original pack. Its index_joins proof handles `(b*n+k)*G+g` and `(b*n+k)*p+2g+c`. The invalid right field of an odd last pair is never required to agree with a raw next-row address.
3. Pending `readRow_eq_dot` then gives the exact original reader for each Fin4 row. Rewrite `(baseA+lane*n)` to `(b*m+offset+lane)*n`. Use retained `RowStream.point_row` and `(b*m+offset+lane)/m=b` to obtain the four `h0..h3` premises of `emit_four_rows_prefix`, with start=`(b*m+offset)*p`. Its four nested emits match raw8.rows4 literally. Handle p=0 through the original rows4 branch.
4. For `R22Resident8.blocks`, use retained `RowStream.foldl_inv` with invariant `Prefix point ((b*m+4*i)*p) acc`. After m/4 blocks its endpoint is `(b*m+4*(m/4))*p`.
5. Apply existing `emit_flat_rows_prefix` with offset=`m/4*4` and rows=`m%4`. Nat division gives offset+rows=m. Its exact quotient/remainder tail reader matches raw8.rows after commuting the fixed multiplication by4.
6. Apply `batch_fold_prefix` to the exact original output fold, then retained `RowStream.prefix_vector_eq_ofFn` and `RowStream.points_eq_reference`. This is the missing raw8.core→reference path. The outer original underflow branch has its retained proof; original fallback bmm must retain its original binding when exposing any new public bmm.
7. Verified ccee transports the machine loop to the Nat loop. Pending3adb/9da6 congruence leaves lift that transport through the identical output and exact guards. Their proofs have not been compiled; they cannot substitute for steps1–6.

First integration falsifiers: batch2,m5 must reset the four-row block at the second batch; p3's last right word is padding; m%4 tail must retain the flat quotient/remainder order. Existing finite models catch these, but no finite model establishes the Float32 or public theorem.

No new full Kernel, CI request, seed, threshold or runtime change is proposed by this note. Source-size integration and all remaining Lean acceptance are UNKNOWN. Prefer one exact statement/kernel/axiom probe for the assembled remaining interfaces in a future authorized batch, not separate copies of eight lane proofs.
