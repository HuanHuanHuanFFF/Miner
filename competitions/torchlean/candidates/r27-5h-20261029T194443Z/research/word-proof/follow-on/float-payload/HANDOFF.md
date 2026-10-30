# Float payload word-side handoff — 00:00 UTC

Parent23:26 task handled; only integer format/cost, A owns Float logical proof.
Original QPD is2^62±M withM<2^39: both Nat entries immediate on64-bit;
one P entry read perMAC. No per-element big allocation or two-load claim.

- Dense aligned40: halve cache slots, but adds sign application; no actual
  work elimination shown. Pause as main whole-model route absent C/cost.
- Sparse aligned52: signed32 coefficient +20-bit original index; requires
  inputspan<=7. May remove separate I load and oldWsign-dependent P lookup.
  Reuse existingQPI, replace its QPD conversion; do not buildboth caches.
- Sparse shifted49:24mant+4delta+1sign+20index supports oldspan15 but
  reintroduces inputshift perMAC. Extra prep/query cost remainsUNKNOWN.
-1255B WordPayload.lean/ab409983 is pureword source, policyPASS, uncompiled,
  notqueued.72000 selections/36000 Python bit transports pass. ActualFloatArray
  read/write and Lean/native cost NOT_RUN. Span8 positive4294967040→-256
  is a real format counterexample; numerictoFloat is not rawofBits encoding.
- Actual index<n must come fromQPI/I9/getter proof; payload<2^52 is insufficient.
  OldR26 generatedC returnsdouble butget! haschecks; pinnedA get/uget excerpt
  isfb33ff76. Current23 C unavailable, actualtag/loadeliminationUNKNOWN.

See FORMAT-AND-COST.md, format-model.json, source-receipt.json. No newCI request
or frozen-source change. Original cutoff00:44:43, no newlongwork00:00.
