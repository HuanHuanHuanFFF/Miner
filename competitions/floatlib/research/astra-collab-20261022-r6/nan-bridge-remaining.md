# NaN route: exact remaining bridge

W03 is conditional and NOT_RUN. R's additional fixed-source inspection narrows two premises without pretending a new compile happened.

From fixed FloatLib `Dyadic/Classification.lean`:

```lean
theorem isNaN_zero (fmt : FloatFormat) (sign : Bool) :
  isNaN (zero fmt sign) = false

theorem toDyadic?_eq_none_of_isNaN {fmt : FloatFormat} {x : Model fmt}
  (hx : isNaN x = true) : toDyadic? x = none
```

From fixed `Model/Carrier.lean`:

```lean
theorem isSNaN_eq_false_of_isNaN_eq_false {fmt : FloatFormat}
  (x : Model fmt) (hx : isNaN x = false) : isSNaN x = false
```

Thus W03's hzero can be supplied by composing isNaN_zero with the last lemma; its NaN decode premise already has the exact public theorem. These source declarations were inspected, but no new instantiated file was compiled here.

Still required before an all-input dot optimization: concrete quieting preservation/idempotence, non-signaling results from roundDyadic and nativeOverflow, and the invalid-result classifier; bind every helper to the actual binary32 descriptor and preserve NaN sign/payload. Once supplied, W03's pointwise absorption and ordered-fold induction connect to the real Spec, and a separate wrapper must connect its list or loop to the actual Packed10.finish fallback. The generic list theorem alone does not establish that wrapper.

A low-cost first runtime candidate after proof is available: on the fallback fold only, test accumulator quiet-NaN before reading operands or multiplying, return accumulator when true, otherwise retain the old step. A true early exit avoids loop overhead too, but needs a second loop-equivalence proof. Neither version is implemented/accepted in R6. New-suite time shares remain unknown until D's nested full gate completes.

Do not use this for FMA or ordinary sum. A later raw signaling NaN replaces an existing quiet sum accumulator; multiply first quiets the raw inputs before add sees its right operand. The distinction is exact stored-word behavior, not IEEE numerical equality.
