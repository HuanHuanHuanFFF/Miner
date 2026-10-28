# Erased cache-read bounds for Pair8

Start **22:53:15 UTC**, check bound **23:08:15 UTC**, shared deadline unchanged. Reads D's exact Pair8 **cd0e3399 / 7587 B** and A's cache-value proof **2850a16c / 4310 B**. This work does not duplicate the pack value proof or modify0ec runtime.

**The old check is still present.** `selected-read-receipt.json` binds current0ec input to the actual owned Main callback `R22Pair8.guarded`, then its C call path through core/output/rows/blocks/rows4/loop to the specialized map. The map C computes cache size, compares the Nat index and selects zeroPair on failure. Source-bound ASM retains `0x110 cmp rax,rsi`, `0x113 jae0x200`, and zeroPair's0x203 relocation. The original Submission source is byte-identical around the owned timed Main; the ASM is a statement diagnostic object, not a new checked-read or final-gate ELF. No cycle share or speedup is measured here.

## Exact safe API

Pinned Lean4.34 source `Array-MapIdx.lean.primary` (ad3789b1) and Array.Basic show the callback is:

```lean
Array.mapFinIdx (xs : Array α)
  (f : (i : Nat) → α → (h : i < xs.size) → β)
```

It is a Nat index, element, then an erased bound proof; it is not a Fin-index callback. `Array.mapFinIdx_eq_mapIdx` already proves the two maps equal when their pointwise values agree. Both safe APIs use the existing library backend; no library or trust-interface change is needed.

`CheckedRead.lean.inc` has four **NOT_RUN** proof-only roots and is1418 bytes:

1. `cache_index_lt`: from `base+n*G≤cache.size`, `k<n`, and `j<G`, derive `base+k*G+j<cache.size`. Multiplying k+1≤n by G and using j<G closes the arithmetic, including the vacuous G=0 case.
2. `read_eq_getD`: a proof-indexed read equals the old getD/default read under the bound.
3. `advance_map_eq`: for arbitrary state array and update closure, mapFinIdx with proof-indexed cache reads equals the old mapIdx/getD body. Instantiate G=groups p, state=s.toArray, `s.size_toArray`, zero=zeroPair, and the unchanged update closure capturing all four A values. A's CacheAgreement can remain expressed with getD.
4. `pack_span`: D's existing packB_size plus b:Fin batch gives `b*n*G+n*G≤cache.size` for the complete packed cache. No cache-value lemma, extra input shape guard or dynamic scan is needed.

## Candidate integration boundary

If D tests this later, carry the span proof as a Prop argument through the internal row/loop functions, and pass the already available k<n proof from the original loop branch. Do not insert a new `if` or runtime decidability test for the span. The map callback's third argument supplies j<state.size; the existing Vector length equality supplies j<G. The resulting proof terms erase.

Only the cache read becomes `cache[baseC+k*groups p+j]'h`. A loads/defaults, decode, eight ordered arithmetic chains, map ownership, state layout, output indexing, valid/padding lanes and raw finish are unchanged. Nat address construction and its reference/big-Nat handling are **not** automatically removed by deleting a range check.

The source-level proposal has no new runtime guard. Actual generated code must confirm that the cache-size/default branch disappears, map/Cell reuse is retained, and no replacement bounds check/closure is introduced. Since the old read is always in range under its internal caller invariant, its old branch may be predictable; static removal is not a time estimate. D decides any next complete-caller measurement. No same-source reseed or new CI is requested.
