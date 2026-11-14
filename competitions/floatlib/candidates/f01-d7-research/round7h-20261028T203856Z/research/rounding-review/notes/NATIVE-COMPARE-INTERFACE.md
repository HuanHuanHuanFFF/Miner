# C: actual Native64 comparison interface

Current task first clock23:33:49UTC. The required midpoint-word review is finished in `midpoint-words1-review.json` (review SHA09ef1eadc8efe136440fee162be9316f48118f4d2312f08e4547e24a56c6bce3), with no concrete static blocker and no Lean acceptance claimed. No existing3556-case model was rerun.

## Fixed-source investigation

The inspected public Native entry points cover arithmetic AddSub/Sqrt/Integer representation; no native comparison wrapper was found there. The specifically requested `Configured/NativeFPU/Proof.lean` blob4252d2c3… and Runtime blob484127a0… contain proved softwareFma32/softwareFma64 adapters, not a native Float.lt comparison bridge. `ExecFloat.compare` and `Model.totalOrder` are separate software/runtime capabilities and are not evidence of a cheap native comparison.

The exact native path is Lean4.34 `Float.lt` in Float.lean:115, `Float.Model.lt` in Model/Float.lean:146, then `UnpackedFloat.lt` and `UnpackedFloat.compare` in `Unpacked/Operations/Compare.lean` (blobc6e194efed120883b795fa06da9b99e95db0674e). That last comparator lexicographically compares exponent then mantissa for equal nonzero signs, reversing for negatives, and handles signed zero numerically. Its documented same-format canonical-input requirement is essential. Unrestricted finite tuples(.finite positive2 0) and(.finite positive1 1) both denote2 but compare.lt; this is not a counterexample for valid native Float.unpack values.

Useful public numerical-canonical interface already exists:

- `Model.cexp_toDyadic?`, fixed `Conversion/Text/Representation.lean:26`, blob31b1e299fad7c680f7b64ecd0526c0081439863b; preserved earlier as `FloatLib-Text-Representation.lean.raw`. A nonzero decoded value's exponent equals its format-canonical exponent.
- `Flocq.cexp_mono_abs`, `Theory/Format/Magnitude.lean:115`, blob2ea970f44626fe1428b529b0a1ddf1e93e13918b; monotonicity follows for nonzero values ordered by absolute magnitude.
- `Flocq.fltMonotoneExp`, `Theory/Format/Formats.lean:322`, blob645d99d8fec289e408b1fe5298610ee524241777; supplies the required monotone exponent-selector instance for Model.fexpOf binary64.
- `Model.toReal_eq_unpackedToReal_toModel` and `Model.unpackedToReal_finite`, fixed Model/RealSemantics.lean:127,102 (blob10e8f500803dedef49b8a8247ddf6d220f819784), connect native unpack cases to the same real denotation.

New source originals and hashes are retained under `native-compare-sources/` and `native-compare-source-receipts.json`. Existing imported sources are reused by their earlier preserved receipts. The numeric exponent theorem is distinct from `IsModelCanonical`, which addresses canonical NaN encoding.

## Minimal actual probe, not a runtime ordering framework

`f01-r24-research-native-compare-bridge1` contains one root, `Submission.R24NativeCompare.native_lt_iff_real`, on actual Float inputs. Only input finiteness is assumed. The proof derives actual unpack decodes, uses numerical canonical exponents and monotonicity to handle different exponents, multiplies by a common positive scale for equal exponents, and splits signs/zeros exactly. Therefore no supplied abstract order-equality premise or mantissa-normalization assumption stands in for native semantics.

Kernel SHA8c7a1509ac9ba7e3d1e5b34cf7dd395f48645f1b4db954a1f737e8d97d76d805/235559B; fragment34769149311e8784001883fbb3a4341d7b12526ac5cdaf40398335758f1a4920/8729B. B2 first226829B is unchanged. Helper-v8,one root,180s and repository-relative component paths are manifest-bound. Static packaging passes. No local Lean, compiled native test, CI dispatch, axiom audit or timing ran here.

The source is frozen for root's one independent critical check and D's actual CI. Any failure in Bool/Prop reduction or sign-case simplification is a source typing/integration failure to repair from diagnostics, not a counterexample to numeric order. The full filter still needs its midpoint/value/error composition and measured caller; this proof does not establish speed or competitive admission.
