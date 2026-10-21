# Tag4 proof port, pending actual extraction

This directory contains preparatory helper theorems, not a submission package. The measured `r10-finder-tag4` files remain unchanged. `helper-draft.lean` has no added axiom or sorry, but has not been compiled and its inferred tuple interfaces may be wrong.

The engine D loop requires no truth invariant for the supplemental cache: all cache contents are untrusted and `r10_supplement` guards the candidate position before calling `probe`. Retain the original head3/head4/head7 `LeAll` invariants and original position/continuation bounds.

Actual extracted interfaces to inspect before assembling `Parse.lean`:

1. `r10_cache_store`: expected `(Usize * Array U64 65536)` return; cache indices below 65536 and `a+1` safe. If scalar automation cannot prove the multiplication range, isolate `(x >> 17) <= 32767`, hence `2*(x>>17)+1 <=65535`.
2. `r10_supplement`: expected `((nc,best),cands)` return. `old>0 && old<=i` implies `c=old-1<i`; original `probe_spec` then gives `l<=cap`. The write uses `nc0%16`, and `nc0+1` is safe from `nc0<16`. Every branch preserves `best0<=best<=cap`.
3. `r10_insert_range_loop`: expected carried tuple `(head3,head4,prev4,head7,prev7,cache,q)`; measure `to-q`, cache unconstrained. Preserve original `LeAll` head bounds and `to+8<=Usize.max`.
4. `d_parse_loop`: the new cache is expected before `pa` in source-order parameters and carried state. Confirm that exact position from generated `Funs.lean`, including inner ite return tuple types.

Adapt only `d_parse_loop_spec` / `d_parse_spec` after the helpers: add the cache parameter and carried-state slot; add the store bind after original `insert_pos`; bind the supplemental result after continuation assembly, keeping its lower/upper best bounds; switch taken-match insertion to the extended range helper; and adjust all returned-state patterns, measure/invariant tuple patterns and initial invocation. The public Rust `d_parse` signature and final checked emitters are unchanged.

The original original obligation, allowed-axiom check, fresh re-extraction and public round trip still need to succeed for the exact final hashes. None of these conditions is discharged by the helper sketch or finite diagnostic.
