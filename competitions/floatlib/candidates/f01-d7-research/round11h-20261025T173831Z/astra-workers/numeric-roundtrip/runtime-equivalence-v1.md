# R17 sorted numerical ADD: exact wiring obligations

`Runtime-sorted-roundtrip-v1.lean.inc` is a two-definition runtime fragment, not a Kernel and not a submitted candidate. Its source deliberately contains no replacement public spec. `Bridge-normalize-v1.lean.inc` contains four complete but **uncompiled** helper attempts; the normalization-shift equality remains an explicit premise and must be discharged when wiring the actual callback.

## Runtime data flow

The public wrapper reads `u`, `v`, `eu`, `ev` once. Its normal-field guard is identical to f7f. It branches once on `eu < ev` and passes the selected `hi`, `lo`, `ehi`, `elo` as scalar arguments. It does not construct a prepared record, tuple, Option, array or closure.

The sorted worker computes `d`, each sign, `same`, and `adjust=[opposite signs]` once. The domain guard is `d<=7 && adjust<=d`, equivalent to f7f's `d<=7 && (same || 1<=d)`. Only then does it extract each mantissa, align the high mantissa, and compute N once. Under the original high-N guard it computes `R=N.toFloat32.toUInt32` once, followed by:

```text
baseShift = d - adjust
threshold = 1 << (baseShift + 24)
bump      = [threshold <= R]
shift     = baseShift + bump
E         = ehi - adjust + bump
word      = mkW highSign E (R >> shift)
```

`FastMul.mkW` supplies the existing exponent/fraction masks; the fraction is not separately masked twice. This preserves the checked packing interface and avoids a new raw-bit assembly proof. The accepted branch has no toBits or general log2 operation in its source.

The only output guard is `E<=254`. When it fails, the original B2 fallback runs with the **original ordered x/y**, as do nonnormal inputs, disallowed gaps/signs, zero and low-N cases. No new direct-infinity branch is introduced. The lower exponent guard is unnecessary: normal inputs give `elo>=1`, the sorted relation gives `ehi=elo+d`, and `adjust<=d`, hence `ehi-adjust>=1` before adding bump. This argument does not even need the high-N or numeric-cast theorem. `output_exponent_bounds` and `output_exponent_guard` are uncompiled arithmetic proof attempts for this exact fact.

## Existing evidence and exact reused interfaces

Baseline source: `f01-r15-dev-packed-b2-1/Kernel.lean`, SHA `622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`.

- `Submission.R2W01b.mantissa` and `R2W01c.mantissa_bounds`: raw normal significands.
- `Submission.FastMul.mkW`, `FastMul.mkW_ofNat`: exact packing.
- `Submission.R7W02.fromRaw_toModel`, `R7W02.exec_toModel_eq_rawModel`, `R7Native.toModelExecAdd`: raw/public representation boundaries.
- The original B2 `Submission.add` and `add_spec` become the fallback implementation and proof when D installs a new public entry. Renaming that original definition/theorem is part of controlled integration; the fragment does not perform the rename itself.

Previous full-gate source f7f: `f01-r16-dev-native-add-high3/Kernel.lean`, SHA `f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd`, run `40189703522`. Its full gate passed and its runtime performance failed; this fragment does not inherit a speed claim.

- `Submission.R16AddWord.normal_field`, `sorted_exponents`, `gap_nat`, `sameSign_eq`, `eligible_conditions`, `sorted_domain`, `magN_bounds`, `magW_nat`, `raw_add_dyadic`: exact old guard, unsigned no-wrap magnitude and aligned dyadic semantics.
- `Submission.A16N.model_round_normal`: normal-output rounding shape.
- `Submission.A16L.exact_high_low` / `exact_low_high`: retain original operand order when relating the sorted arithmetic to Model.add.

The uncompressed R16 research source uses `R14NatNormal`, `R16AddAlignment`, `magnitudeNat`, `magnitudeWord` for some of those names. The frozen 01cff probe uses `R14NatNormal`. Source extraction/renaming must be explicit in the final source manifest, with the actual resulting module compiled and audited. Old full-gate status does not certify a renamed integration automatically.

Pending source: frozen `Probe-high-u32-roundtrip-repair1.lean`, SHA `01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905`.

- `R16UInt32Roundtrip.high_roundtrip`: actual numerical cast returns `roundedInteger N`, for `2^23<=N<=2164260735`.
- `rounded_leading`, `high_mantissa`: normalized leading exponent and mantissa bounds, including h=31/shift=8.
- These and the other 22 original probe roots remain **NOT_COMPILED / NOT_AUDITED**. The four new helpers also remain uncompiled.

## Required proofs before a public spec can close

1. **Single sorting equals old mathematical sorting.** Relate the wrapper's two scalar argument branches to old `high/low` and exponent facts. Equal exponents select the original left operand, as in f7f. Relate sign Booleans and `adjust<=d` to the old disjunction; no new numerical domain is introduced.
2. **Unsigned arithmetic is exact in the accepted domain.** Reuse the actual old no-wrap alignment and magnitude lemmas, or instantiate their Nat statements with the scalar locals. Obtain `N = magN u v`, `N<=2164260735`; the high guard supplies `N>=8388608`. For opposite signs, d>=1 prevents unsigned subtraction wrap and gives the high operand's result sign.
3. **Numerical cast equality.** Apply the pending `high_roundtrip` to the computed N after discharging the original two bounds. This removes native conversion and clamp behavior as assumptions.
4. **R-threshold normalization.** Prove the actual word `shift` has `shift.toNat = R16UInt32Roundtrip.roundedShift N`. This is the main remaining mathematical bridge. Its interval argument is in `next-discriminator.md`; the implementation uses R, not N. Prove the threshold exponent is at most 31, so the UInt32 threshold shift is not accidentally reduced modulo 32. Prove the final shift is at most 8.
5. **Output exponent relation.** Establish `E.toNat = N.log2 + carry N + elo - 23`, including the unsigned-subtraction/no-wrap steps. The input field and adjustment guards prove `1<=E<=255`; the actual upper guard gives `E<255`. The normal-rounding lower premise also follows directly from `N.log2>=23` and `elo>=1`; it is not inferred by reversing a rounded carry.
6. **Cross-representation fraction.** The new conditional `numeric_shift_toNat` and `numeric_fraction_toNat` attempts turn step 3 plus step 4 into the same normalized mantissa/fraction as `model_round_normal`. Their `hs` premise is intentionally visible; it is not a completed threshold proof.
7. **Model/public equality.** Use `mkW_ofNat`, `model_round_normal`, `raw_add_dyadic`, and the existing fromRaw/model injection chain to close the accepted branch. Every reject branch uses the original fallback spec. Only then define the public `add_spec`; re-run all original obligations and full gate on the exact integrated source because SUM/BMM can resolve the public ADD.

## Selected C/assembly work contract

These are future observable requirements, not verified compiler claims:

- Derive the actual ADD callback from `BENCH_PLAN` closure wiring. Do not assume the old `lam__2` suffix remains stable.
- On an accepted path: two initial exponent extractions; one order selection; one high and one low sign extraction; one gap; two mantissa extractions; one alignment shift; one sum/difference; one UInt32-to-Float32 and one Float32-to-UInt32 conversion; one R-threshold test; one normalization right shift and one result packing.
- No repeated `high/low/exponent` extraction after the numeric conversion. The original x/y may remain live for the upper-guard fallback; actual saves/spills are an assembly question.
- No external `lean_float32_to_bits`, floating add/multiply, scale-table access, Nat arithmetic, allocation or indirect `lean_apply` on the accepted path. The known constant fallback argument must specialize/integrate away; `[inline]` alone is not evidence that it did.
- Clamps inside `lean_float32_to_uint32` and unsigned conversion lowering may remain. Count their actual branches/instructions; do not report them as eliminated because the mathematical proof bounds R.
- Multiple static fallback copies are possible but only one fallback executes on a rejected path. Do not count every static alternative as per-call work.
- Any codegen discrepancy changes the next action before a large proof expansion or another performance candidate. Passing this work contract is still not a performance result.

## Finite evidence and limits

`runtime-flow-v1-check.json` records 150297 synthetic input pairs, with 47922 accepted results. A separately written old classifier/magnitude expression agrees on all classifications; accepted words agree both with old toBits repacking and direct exact-add-to-binary32 conversion. The normal/gap conditions ensure the double reference sum is exact before its binary32 rounding. Fallback implementations were not executed; their preservation is a source/control-flow obligation, not a Python float NaN claim.

The first checker shared a magnitude routine between both classifiers; its original stdout has been retained with a matching SHA in `runtime-flow-initial-shared-oracle-*`. The current checker re-expresses the old path independently. Both are finite diagnostics, not an exhaustive proof, official gate, throughput measurement or success probability.
