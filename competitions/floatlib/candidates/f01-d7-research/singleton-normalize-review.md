# Singleton normalize: independent static integration review

Reviewed exact [53d1 candidate](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-singleton-normalize/Kernel.lean), SHA-256 53d1c2c40642060c970189250ea1aee88c37ba3eb1309b2bcfed1f0fcf9a3fa7, 187374 bytes. D authored this runtime integration; this reviewer authored the reused c44c mathematical block, not the integration. That block remains uncompiled. Review began 2026-10-22 23:25:12 UTC within a 30-minute bound.

**No deterministic integration bug found in this static review.** Exact inverse transforms and fixed current policy/options pass. New Lean compilation, replay, axiom audit, full gate, generated C/object and performance are NOT_RUN/UNKNOWN. Static agreement does not establish formal correctness or speed.

## Byte identity and changed runtime

The first 174293 bytes equal exact parent97f. The final parent dispatcher/spec are renamed to bmmBeforeSingleton/bmmBeforeSingleton_spec; reversing those names reproduces every original parent byte. The appended proof block occurs once and equals c44c4afbbe117e97b857ac3541638f3cbee370ba86f837fc76be16c41d08ed26 (10793 bytes).

Reversing exactly two changes in the final singleton suffix reproduces the entire dab suffix byte-for-byte: restore Submission.add posZero in place of the raw normalizer, and remove the single inserted rw. Addresses, Fin proof, final n=1 dispatcher/spec, all dimensions and all defaults otherwise match the original singleton. The writing builder was parsed/read, never executed for this review. Its source SHA is ba7be9be148e824092fa504972d33f363cac905a5d17871af17aeec18b24c323.

## Proof, shape and name checks

- Kernel:4425 rewrites normalize(Submission.mul a b) back to Submission.add posZero (Submission.mul a b). The bridge is already declared at4388. After that rewrite the original dab pointwise proof remains: Fin.foldl_succ, Fin.foldl_zero, Fin.val_zero. The saved 808 failure differed only at two Nat coercions of Fin zero; val_zero targets precisely those terms. Rewrite matching and simp closure still require actual Lean.
- Kernel:4407 preserves bmmDecodeC m p q.val and A[(b*m+i)*n+0], B[(b*n+0)*p+j], with the same posZero getD defaults. These are the reference's exact k=0 addresses; no arithmetic reassociation or unchecked read is introduced.
- Kernel:4428 takes the new core only when n=1. n=0 and all n!=1 call the unchanged renamed parent, retaining its DirectSmall/packed decision. Empty batch/m/p output remains an empty Vector.ofFn domain; no positivity premise is added to the theorem.
- The new core contains one syntactic Submission.mul application. The normalizer receives that one call-by-value product; it does not source-level replay the product. Generated instruction multiplicity and inlining remain unobserved.
- The old final export names were renamed before new bmm/bmm_spec declarations. The closed D7SeedNormalize block precedes their use; singletonCore and bmmBeforeSingleton are new relative to the parent. No changed-source duplicate export or forward reference was found. add/mul/sum and all earlier declarations are preserved in the exact prefix.

The helper changes only raw negative zero to positive zero. It still computes actual scalar Submission.mul first, retaining its separately rounded product and NaN/invalid sign/payload behavior. The proof's general-q non-sNaN premise is discharged for actual products by the reused theorem closure. This reasoning depends on the new c44c port, whose elaboration and axioms remain NOT_RUN.

The recovered primary Lean Fin/Fold.lean matches the previously verified v4.34.0 Git blob f7039a47718cebc8c50a64f868667c69a0d5dcd8. Fin.foldl_succ:254 exposes f init (0 : Fin 1); foldl_zero:251 removes its empty suffix. The exact val_zero signature and source blob are recorded by the preceding fixed-source review. This review did not run Lean.

## Confirmed cost difference, unknown gain

The old parent n=1 path uses DirectSmall.core -> NativeFinal.dot -> dotLoop. It computes native acc+fa*fb, then checks the final NaN result and replays exact scalar semantics only if required. Its native product loop has no Submission.mul exponent-sum guard.

The new route calls Submission.mul, whose ex+ey<128 branch invokes LowScale.mul; the other branch calls nativeMul with finite guards and a special fallback. Thus it removes loop/final-check/add work but reintroduces scalar guards and potentially software low-scale arithmetic. A removed add is not evidence of a lower complete cost.

This difference matters for the exposed bmm:subnormal:0 configuration: ordinary input exponents are 11..23 (center17/spread6, no special/subnormal/zero injection), hence every exponent sum is22..46<128. The new route takes LowScale.mul there, whereas the old native loop did hardware multiplication. This is a source/config inference; actual cost and gain remain UNKNOWN. D may separately decide whether to prepare a native-product route; this review creates no such variant.

## Already public 807 n=1 exposure

The exact saved 807 plan has156 total cases:152 timed and4 untimed. BMM has35 cases:34 timed and1 untimed. Exactly three BMM timed cases have n=1; no untimed BMM case does. Outputs below are per complete case sweep, computed as batch*m*p and checked against saved row names, not performance shares.

| 807 case | batch,m,n,p | Output rows | Output elements | Saved diagnostic checksum |
| --- | --- | ---: | ---: | ---: |
| bmm:dense:5 | 22058,8,1,1 | 176464 | 176464 | 2351408007 |
| bmm:specials:1 | 226,21,1,3 | 4746 | 14238 | 4023775818 |
| bmm:subnormal:0 | 14705,6,1,2 | 88230 | 176460 | 0 |

These are367162 output elements over the three case sweeps. The checksums and optional per-case ns in JSON come from807's old8eb parent-stage diagnostic control, not new53d or the actual60f gate measurement. They identify existing observations only. No whole-cell timing is assigned to n=1, and no output/call proportion is used as a time share. No future plan or input was generated or read.

## Validation and next check

The unchanged fixed4b7 policy/options bodies accept exact53d (PASS_STATIC_ONLY; gate SHA1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194). Import/name/UTF8/byte intake checks pass within256000 bytes. Full source/input SHA records, raw808 error identity, exact807 plan/control/verdict identities and inverse-transform results are in singleton-normalize-review.json.

The first useful falsification is the exact53d statement build: retain any c44c proof-port error or new singleton rewrite target. Only after acceptance should this runtime composition receive the original full gate, actual statement codegen inspection, complete paired timing and frozen independent confirmation. No candidate, builder, official source, Git, CI or upload was modified by this review.
