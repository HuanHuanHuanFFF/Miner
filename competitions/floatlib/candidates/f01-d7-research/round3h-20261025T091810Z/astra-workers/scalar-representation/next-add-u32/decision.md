# ADD one-native-UInt32-conversion feasibility

**Continue only to a small interface/normalization proof probe; do not build a full candidate yet.** This exact mechanism was already proposed in R14, with a finite model, but the timed negative ADD implementation used software RSE. The present investigation reuses the idea after the separate native-MUL field route became checkable; it is not a new discovery or a revision of c972. No active run40183711165 inputs/results were read.

## 1. Legal primitive bridge exists; a short raw-word transport is still a draft

B2 `622d8394…` contains the full-gated project theorem `R2W01c.uint32_model_eq_roundDyadic` for **every UInt32**, not only exactly representable24-bit integers. It unfolds Lean's defined UInt32 conversion model and uses fixed FloatLib's `Model.ofModel_ofInt_eq_roundDyadic`. The fixed primitive is transparent at the logical model level. No Float64 narrowing, Int64 bridge or new axiom is needed.

`UInt32NativeRound-interface.lean` supplies a short NOT_COMPILED transport through `ExecFloat.Binary.ofFloat32`, model injectivity and `toBits32` to identify the **actual** `n.toFloat32.toBits` with `NativeBinary32.roundDyadic(false,n,0)`. Official `toUInt32_ofFields`, `expField_toNat/fracField_toNat` and `*Field_ofFields_of_lt` then recover its fields once the shape is proved. The shape is explicitly a hypothesis in that small draft, not silently assumed complete.

Full-gated R14 `word-add-entry2`/`mul-cache-rse2` provide high-leading-bit normal rounding, guard/word field and exact ADD alignment components. Their normal form assumes `h>=23`. The R14 common-rounding webpage file extends this to `h<23`, low-h no-carry and a general postguard, but remains **NOT_RUN**; it cannot be promoted because the high-h parent or c972 statement passed. The next unresolved proof target is precisely the low-h normalization branch plus connection to the same field shape, then alignment/sign/zero transport to `Model.Spec.add`.

## 2. Complete mathematical fast-domain contract

For arbitrary raw words u,v, require original exponents `ex,ey in1..254` and `d=abs(ex-ey)<=7`. Let `a=min(ex,ey)`, `L=Mx*2^(ex-a)`, `R=My*2^(ey-a)`, with24-bit mantissas. Compute the signed exact integer sum and its sign/magnitude `(s,N)` using same-sign addition or an unsigned magnitude comparison and subtraction. All shifts are below32 and

`N <= (2^24-1)*(2^7+1) = 2164260735 < 2^32`.

Magnitude comparison is necessary when exponents tie; sorting by exponent alone does not identify the result sign under cancellation. **If N=0, return +0 before converting or checking the final exponent.** Normal nonzero inputs cancel exactly only with opposite signs. Raw ±0 inputs fail the initial normal guard and retain the original ADD fallback.

For N>0, one native UInt32 conversion gives midpoint fields `(em,f)`. Let the full mathematical target exponent be `E=em+a-150`. Accept only `1<=E<=254`, before masking the field; otherwise use the original ADD. Repack `(s,E,f)` explicitly, avoiding the old large modular whole-word-translation proof. The UInt32 form `(em+a-150-1)<=253` is equivalent within the bounded sum range, but its no-wrap/underflow proof remains part of implementation.

Write `h=floor(log2 N)` and conversion carry c∈{0,1}, so `em=h+c+127`. For h≤23, integer conversion is exact and c=0. Therefore c=1 implies h≥24. With a≥1, the postguard lower bound implies `h+a>=24`; the original exact sum is already in the normal rounding region. The upper postguard includes carry. For h<23 the normalized mantissa is `N<<(23-h)`; for h≥23 it is RNE with shift h−23. These produce the same fraction before and after exponent rescaling. No second underflow rounding is bypassed by an accepted path.

Explicit failure witnesses, independently checked in `screen.json`:

- Missing N=0 branch: `0x4b800000 + 0xcb800000` is +0, but midpoint exponent0 with a151 passes E=1 and naive repack yields `0x00800000`.
- Small cancellation below normal boundary: `0x0b800001 + 0x8b800000` has N=1,a23, result`0x00400000`; naive repack gives0. Correct postguard rejects.
- Allowing d8: `0x43ffffff + 0x3fffffff` has N4311744255 and wraps UInt32; exact result`0x44007fff`, forced wrapped repack`0x3ffffeff`. The exponent postguard does not repair the integer overflow.
- Missing upper exponent bound: `0x7f7fffff + 0x7f7fffff` is +Inf; preserving fraction at E255 gives NaN`0x7fffffff`.
- Tie exponents need magnitude/sign handling: `1.0 + (-1.5)` gives`0xbf000000`; using the first operand's sign because exponents tie is wrong.

Finite screen:12828 directed/random normal-input pairs,11064 pass the initial guard; that initial-guard set contains182 exact cancellations,1624 small nonzero cancellations and92 conversion-carry examples.10610 are accepted and454 fail the normal-output postguard; the small/carry counts were not separately restricted to accepted outputs. Exact integer reference, host C pack4 and proposed word arithmetic agree on all accepted cases. Worker exit0, external5s timeout, controller0.445s. These selected cases are not an exhaustive proof or pinned native execution.

## 3. Prior measured ADD cost and actual guard exposure

Only three completed R15 B2 runs were read. Each archived input independently hashes to622d. Their actual scored ADD share of whole is **36.40%,36.86%,36.65%**. Current B2 ADD normal C already uses two mantissa casts, two scale-table reads/two scale multiplies, one ADD, self-NaN guard and final toBits. This proposed route removes one cast, both table reads, both scale multiplies and native ADD; it adds sorting/alignment, sign/magnitude branches, zero handling and an output guard, and moves toBits away from tail position. Net cost is UNKNOWN. Removing all ADD would cap gain at its whole share;10% whole would require about27.1–27.5% net ADD reduction if other operations stayed fixed.

32256 source-model sampled pairs across those completed draws give accepted fractions:

|Group|R15 D|R15 A|R15 B|
|---|---:|---:|---:|
|dense|56.12%|43.62%|32.29%|
|ml|91.89%|91.65%|97.85%|
|sparse|29.43%|17.71%|50.65%|
|specials|84.24%|85.81%|82.88%|
|subnormal-named cell|81.25%|90.63%|86.52%|
|paired|84.62%|60.40%|87.45%|
|extremes|7.62%|29.20%|71.78%|

Cell names do not mean every operand is special/subnormal. This is the frozen official generator's existing Python transcription, not independently validated against Lean operands. Counts and actual measured class costs remain separate; **no time has been assigned to eligible subsets** and no future success probability is inferred. The first screen attempt incorrectly checked the verdict's incumbent hash as candidate identity; it failed before coverage. Original source/stderr are preserved, and the successful run instead checks the actual archived input plus submission name. No model operands or acceptance conditions changed.

The low-h branch is materially exposed in these counts: small nonzero cancellations alone are17.68–43.36% of all paired-cell samples; exact cancellation adds0–13.33%. Restricting the native route to the old same-sign-or-gap≥2 domain would discard these inputs. This supports proving low-h normalization rather than treating it as an irrelevant corner, while still providing no timing allocation to that subset.

The original R14 timed f958071e result (ADD1.56213, whole1.18928) remains a valid negative for its software RSE implementation, and a warning that alignment/guard costs can dominate. It is not a timing result for this native-conversion variant. The old conservative a≥24/maxexp≤252 native idea and current broader dynamic output guard share the same representation; novelty is not claimed.

A bounded source search across existing pre-R16 candidate Kernel files (excluding CI archives and current R16 sources) found only an older generic `uint32_cast_bits` helper in `f01-d2-decoder-helpers`, not a native aligned-ADD runtime. Its manifest records statement-only and runtime NONE. This is consistent with the R14 notes, but is not a proof that no implementation exists elsewhere. The new interface fragment is59 lines/2934B, not a complete candidate.

## Dependency-closed minimal probe and high-h fallback decision

The follow-up parent request is satisfied by `Probe-native-add-shape.lean`, SHA **41241a3353203ea581a365dfd4f2f6b39e35badd08030a1d4ea5b6dd32881625**, **253667B**. Its exact prefix is the247533B c972 statement-PASS source from run40182114389. It appends only the2934B raw-word transport and3198B `LowNormalization-probe.lean`, with two separator newlines. All public runtime definitions and original proofs are unchanged. The low-h component proves a draft normalized mantissa bound, the actual native word-rounder shape for h<23, actual UInt32 native field projections, and the scaled target fields under full normal-output bounds. It uses no extra import or unresolved local module.

This is **dependency-closed source, not a compiled proof**. It is not a new complete ADD implementation or a timed candidate. The remaining all-input ADD alignment/zero/sign/guard/public-spec transport is outside this probe. A statement pass of its original four specs would not audit the unused appended helper dependency cones; future owner validation must explicitly audit/replay the named new helpers too. See `probe-manifest.json`.

If low-h proof checking remains costly, the single proposed simplification is to require exact N>=2^23 and send all low N/zero cases through original ADD. Reaggregation of existing accepted counts, without new sampling or thresholds, gives:

|Group|High-h only D/A/B coverage|Loss versus full proposed domain|
|---|---|---|
|dense|48.57% /39.06% /27.34%|7.55 /4.56 /4.95 percentage points|
|ml|81.59% /77.05% /81.88%|10.30 /14.60 /15.97 points|
|paired|66.06% /41.85% /30.76%|18.55 /18.55 /56.69 points|
|specials|70.90% /73.05% /69.34%|13.35 /12.76 /13.54 points|

Same signs imply N>=2^24; opposite signs with d>=2 imply N>2^24. Thus the removed low-N region is entirely opposite-sign gap0/1. The actual implementation still must compute exact magnitude: a wrapped subtraction at equal exponents could incorrectly create a large N, so it cannot use `N>=2^23` to excuse a missing magnitude/sign proof. This high-h route remains broadly exposed but loses substantial paired inputs in one completed draw. Its net timing is UNKNOWN, and coverage is not a new confirmation set.

No complete ADD Kernel, CI request, local Lean run, changed c972 file, or new validation group was produced. A future actual ADD candidate needs its own frozen source and fresh complete validation groups. Continue with the small proof probe; retain the single high-h fallback option if actual proof feedback warrants it.
