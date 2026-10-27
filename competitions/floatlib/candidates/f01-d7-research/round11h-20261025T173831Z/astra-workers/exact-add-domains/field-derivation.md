# Exact cancellation fields — independent paper derivation

Status: **PAPER_DERIVATION + FINITE_INTEGER_MODEL_ONLY**. No new Lean declaration, Kernel, target compilation or full gate. The field formula is correct under the complete contract below. This is an exact word/model argument, not an appeal to real-valued Sterbenz alone.

Let `B=2^23`. For an input raw word `u`, write sign `s(u)`, exponent `e(u)=(u>>23)&255`, fraction `f(u)=u&(B-1)`, and normal mantissa `M(u)=B+f(u)`. Require both exponents in `1..254` and opposite signs. Order the **unsigned sign-cleared words** `u&0x7fffffff`, `v&0x7fffffff`; call the larger one `hi` and the smaller `lo`. Carry the original signs with the words. Let `a=e(lo)`, `d=e(hi)-a`, require `d<=1`, and compute

`N = (M(hi) << d) - M(lo)`.

The remaining guard is `N<2^24`. Input raw zeros, subnormal inputs, nonfinite inputs, same signs, gaps outside the domain, and `N>=2^24` keep the original B2 ADD. This restriction is a sufficient domain; it does not claim that every excluded difference needs rounding.

## 1. Sorting, alignment and magnitude

For normal finite words, sign-cleared raw order is lexicographic exponent/fraction order and therefore magnitude order. If `d=0`, sorting gives `M(hi)>=M(lo)`, and `0<=N<=B-1`. If `d=1`, `2M(hi)>=2B>M(lo)` and

`1 <= N <= 2(2B-1)-B = 3B-2 < 2^25`.

Thus subtraction is nonnegative, and the aligned operand is below `2^25`; both the shift and subtraction are exact UInt32 operations. Exponent-only tie ordering would be insufficient: `0x3f800000 + 0xbfc00000` must have the negative sign of the larger magnitude and produce `0xbf000000`.

Normal decoding is exactly `(-1)^s M*2^(e-150)`. Hence the original-order exact sum is `(-1)^s(hi) N*2^(a-150)`. This is obtained either by the fixed same-exponent opposite-sign lemmas, or by the fixed adjacent-exponent opposite-sign lemmas. No raw NaN addition is commuted. For `d>=2`, the analogous difference would be at least `4B-(2B-1)=2B+1`, so it could not meet `N<2B`; nevertheless, test the gap before a machine shift.

## 2. Zero has its own canonical result

`N=0` is possible only at `d=0` with equal mantissas, hence equal nonzero magnitudes and opposite signs. The fixed `Model.addDyadic_oppositeSign_sameExponent_eq_zero` returns `{negative:=false, significand:=0, exponent:=0}`. The fixed rounder maps it to raw **+0**. Return `0x00000000` before log2 or any field expression. This does not alter the behavior of raw ±0 inputs because they fail the initial normal guard.

## 3. Nonzero normal output

Suppose `0<N<2B`, and set `h=floor(log2 N)`, so `0<=h<=23` and `2^h<=N<2^(h+1)`. If `h+a>=24`, define

`E = h+a-23`, `sig = N<<(23-h)`, `fraction = sig-B`, `sign=s(hi)`.

The normalized significand satisfies `B<=sig<2B`, so the fraction is in `0..B-1`. `E>=1`. Moreover:

- If `d=0`, then `N<B`, so `h<=22` and `a<=254`, yielding `E<=253`.
- If `d=1`, then `a<=253` and `h<=23`, again yielding `E<=253`.

Thus the result is finite normal, with no overflow or invalid field masking. Its value is exactly

`sig*2^(E-150) = N*2^(23-h)*2^(h+a-173) = N*2^(a-150)`.

More strongly, expanding the fixed `NativeBinary32.roundDyadic` gives these exact fields: its total exponent is `h+a-150>=-126`; when `h<23`, it takes the left-shift branch above; when `h=23`, `roundShiftRightEven N 0=N`. The significand is below `2^24`, so no carry occurs. Its upper exponent is below the overflow branch. No rounding approximation or native numerical conversion is involved.

All UInt32 field operations are bounded: `23-h` is in `0..23`, `sig<2^24`, `h+a<=277`, and subtraction of 23 occurs only after the normal predicate. Packing `(sign<<31)|(E<<23)|fraction` therefore exactly represents the proved fields; masks must not substitute for the bounds.

## 4. Nonzero subnormal output

Otherwise `h+a<=23`. Since `h>=0` and `a>=1`, `a<=23`. Define

`E=0`, `fraction=N<<(a-1)`, `sign=s(hi)`.

The shift is in `0..22`, and the leading bit of the result is `h+a-1<=22`. Therefore `1<=fraction<B`, with no UInt32 wrap. It represents exactly

`fraction*2^-149 = N*2^(a-1)*2^-149 = N*2^(a-150)`.

The fixed rounder's subnormal branch has `value.exponent+149=a-1>=0`; it takes a left shift, never RNE right shift. The fraction is neither zero nor `B`, so neither signed-zero nor promotion-to-minNormal subbranch applies. Negative nonzero results retain the high operand's negative sign. At the adjacent boundary `h+a=24`, section 3 gives `E=1`, including exact minNormal when `sig=B`.

## 5. Exact fixed-source proof interfaces

Hashes and source paths are in `evidence.json`; the FloatLib files are the retained fixed `0d91825727839f597fd06b22fdd038ea21480f0c`, authored by FloatLib Team under MIT.

1. Original finite decode: `A16N.raw_normal_decode` in the full-gated R16 f7f source handles every exponent `1..254`. B2's `R2W01c.target_raw_decode` requires `NormalBand`, hence exponent at least 24, and must not be reused blindly for `a<24`.
2. Exact addition: `Model.addDyadic_oppositeSign_sameExponent_largeLeft`, `largeRight`, `eq_zero`, and `addDyadic_oppositeSign_adjacentExponent_largeLeft/largeRight` from `Backends/Generic/AddDyadic/Proof.lean`. The adjacent strict-magnitude premise follows from `2B>Mlo`.
3. Exact rounding: expand `Model.NativeBinary32.roundDyadic` from `Backends/Word/Narrow/Base/Runtime.lean` using the bounds above, then use `NativeBinary32.ofUInt32_roundDyadic` from `Narrow/Agreement.lean` to reach generic `Model.roundDyadic`.
4. Original obligation: `Model.Proof.add_eq_spec` and finite `Model.Spec.add` connect decoding and exact dyadic addition. Use the existing rawModel/ExecFloat model injectivity transports to prove the new public ADD against the unchanged original obligation. This is still required, not discharged by the paper argument or finite model.
5. Existing `FastMul.fastLog2_eq` in exact B2 proves its bounded-step UInt64 search agrees with log2. Reusing that search on `N.toUInt64` can avoid the standard per-bit log2 loop, but the caller's actual code and word transport still need inspection. The original R16 `LowNormalization-probe.lean` preserves its historical NOT_COMPILED label. Its later f912 interface carrier actually **failed statement** in completed run 40186471996 (ambiguous Dyadic, redundant tactics and shift-normalization/type errors); there is no accepted low-normalization theorem to inherit from that run. The original receipt is indexed in `evidence.json`.

## 6. Actual finite diagnostic and counterexamples to unsafe extensions

`check-domain.py` checks 150,942 input pairs: 140,086 accepts, including 1,016 exact zeros, 6,096 subnormal outputs and 132,974 normal outputs. It covers all 254 normal low-exponent choices where admissible, both input orders and output signs, gaps 0/1, differences around powers of two, guard-boundary rejects and 10,000 seeded random pairs. The independent reference decodes each input as an exact integer multiple of `2^-149`, adds signed integers, then applies a general integer RNE encoder. No differences were found; the actual subprocess timeout is 5 seconds and the completed run took under one second. This finite result is not an exhaustive or Lean proof.

| Case | Inputs | Correct raw result |
|---|---|---|
| Sign follows magnitude at tied exponents | `3f800000 + bfc00000` | `bf000000` |
| Exact cancellation uses +0 | `4b800000 + cb800000` | `00000000` |
| Negative least subnormal | `80800001 + 00800000` | `80000001` |
| Largest subnormal | `00ffffff + 80800000` | `007fffff` |
| Exact minNormal boundary | `01000000 + 80800000` | `00800000` |
| `a=23`, small difference | `0b800001 + 8b800000` | `00400000` |

The excluded `3fc00000 + bf000000` has `N=2^24` and is exact but outside the stated formula's `h<=23` premise. The excluded `3fc00001 + bf000001` has odd `N=2^24+1` and needs ties-to-even rounding. Extending d=1 without its N guard would therefore be unsound. No broader domain is proposed here.
