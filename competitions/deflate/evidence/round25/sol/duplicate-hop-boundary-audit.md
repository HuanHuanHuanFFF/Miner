# Duplicate-hop boundary and proof pre-audit

**Source inspection only. Rust native, actual extraction, Lean and gate
have not run for this new pair.** The frozen Rust SHA-256 is
`f3df2b179c9236bab71204092805cd27220357e05606f11bb25ab4dc52c5a2f7`;
Lean is the exact parent copy
`4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6`.

- Original `pc_f_deepen` runs first. Every original accepted match stays
  available as g, and the final original `pc_f_try` only replaces g with a
  strictly longer, byte-validated match. This is local offer preservation,
  not monotone whole-file encoded improvement.
- The extra branch tests full4-byte mask, `dp=1` and **original** main
  length below8. Three-byte/dp2 and original main lengths8–258 return g
  without any additional word/chain access. The cached `cw` is forwarded
  from the existing main loop; the current head is not loaded again.
- `c2<c` and its wrapped distance in1–32768 are checked before the extra
  word read. Under the existing `c<=p`, this gives `c2<p`. The zero source
  remains allowed; it is not assumed to be an empty hint.
- `prev[c2%32768]` is one bounded array read. Its value is an untrusted
  hint. Even if a ring slot was overwritten, the final try checks strict
  `c3<c2`, actual window and real bytes. An exact32768-boundary alias can
  therefore produce no new match rather than an unchecked source.
- There is exactly one extra predecessor read and no loop/search to the
  diagnostic8-step cap. No insertion, table, route, skip/lazy or fold code
  changes. The source-reversal check recovers the whole parent bytewise.

The new wrapper's intended local proof needs the original `MatchAt` and
`c<=p`, plus **`p+8<=s.length`**. The last premise is needed before evaluating
the Rust checked addition `p+8`; the runtime comparison alone would not
prevent overflow for arbitrary external helper arguments. The actual main
loop already has `p<lim` and `lim+8=input.length`, so it can supply that
premise without changing the root obligation or adding an assumption.

This also bounds `c2+8` before the `pc_be8` call. The `%32768` index and U32
hint cast reuse the existing fixed-ring arithmetic. `f_deepen_spec` yields
a valid MatchAt for g; `c2<c<=p` supplies the anchor premise for the final
`f_try_spec`. The equality to `cw` gates the heuristic but need not become
a new proof assumption: even an arbitrary cached word cannot bypass the
final byte validator.

After a useful native/time result, inspect actual `r25_duplicate_deepen`
argument order and unchanged recording/main loop headers. Add only a
local-step wrapper MatchAt lemma before the main loop proof, with the
explicit checked-add premise above. Current inherited Lean does not have
that lemma and remains DRAFT. Full original extraction/obligation/axioms
and roundtrip must bind the exact final pair.
