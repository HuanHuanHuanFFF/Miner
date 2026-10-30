# Public23 QPD payload feasibility

Response to the parent's23:26 file task. This is a data-format and cost
precheck, not an implemented FloatArray kernel or a request for whole-model CI.

Public23 QPb stores **2^62 ± M**, where M is the aligned input magnitude.
QPS/QPa's combined span<=15 implies each input span<=15 and M<2^39.
Both stored Nat values therefore lie strictly between0 and2^63. On the
pinned64-bit small-Nat representation, these are immediate tagged words;
there is no per-element big-Nat allocation to remove. QPa selects exactly
one of the two entries using the weight sign. It does not load both entries.

| Format | Payload layout | Scope | Real change |
|---|---|---|---|
| Dense aligned40 | 2^39 + signed aligned input | Entire existing span<=15 domain | Two Nat entries become one raw FloatArray element; still one input load per MAC; weight sign must be applied after loading. |
| Sparse aligned52 | signed32 factor in low32 bits; original index in high20 bits | Input span<=7 and index<2^20 | Can replace P plus I with one raw payload, removing the separate I load and the weight-sign-dependent P address. |
| Sparse shifted49 | mantissa24, delta4, sign1, original index20 | Entire existing span<=15 domain | One payload, but decoding restores an input variable shift per MAC that QPD currently performs once during preparation. |

The52-bit format's span<=7 guard is essential. A positive aligned factor
`(2^24-1)<<8 = 4294967040` fits32 raw bits but decodes as signed -256.
That input is legal for the old combined-span<=15 cache. Merely proving the
Float payload below2^52 does not prove the packed factor is exact.

Storage must use **Float.ofBits(payload)** and retrieve `.toBits`, with no
floating arithmetic. Numeric UInt64.toFloat is a different encoding: numeric1
has raw IEEE bits0x3ff0000000000000, not payload1. Array Float is also a
different container from FloatArray and must not be substituted silently.
A handles the logical finite raw-bit roundtrip; no such theorem is claimed here.

Cost boundary: dense old cache has16N bytes of array element slots, sparse
old cache has16I bytes for P plus8I for its UInt32 index array on64-bit Lean.
FloatArray payloads use one8-byte scalar slot per logical element. These are
payload/slot counts, not allocator measurements. Array headers, preparation,
ownership, checked indexing and output destruction still count.

The dense40 case does not yet justify a large gain: it replaces tag handling
and capacity with extra sign application. Keep it paused unless real emitted
code shows a relevant cost. Sparse52 is more substantive: old access is
I[k]→W[index]→P[2*k+weightSign], whereas one packed payload exposes index and
factor before loading W. It still needs actual checked/USize getters and a
complete-call measurement; neither tag elimination nor load count is measured.
Sparse49 must additionally repay its new per-MAC shift.

The smallest sparse52 runtime change can reuse the existing QPI result. After
the same span/density decision, read exactly the same I-indexed raw inputs as
QPD, push one indexed Float payload instead of two Nat values, and release I
for that selected row. Do not also build old P for the selected branch. Dense
and wider-span rows keep the old builder. This needs no extra raw-input scan
over the original n+I preparation, although packing/bit transport still costs
work. A one-pass metadata/count rewrite is a separate larger change and is
not required for the first discriminator.

The packed index remains an actual producer obligation. A payload<2^52 only
bounds the index below2^20, not below this dot's n. Reuse the original QPI/I9
membership facts and bounds-proved getter, or keep an explicit checked/clamped
fallback as the old QPa does. Do not replace that link with an assumed cache
well-formedness premise and call the kernel proved.

Existing R26 generated C confirms FloatArray get returns a native double,
but its get! path also carries Nat index/check overhead; it is not evidence
for the proposed payload cache's generated code. A's hash-bound
PINNED-FLOATARRAY-ACCESS.json verifies safe proof-indexed get/uget interfaces.
No current public23 generated C was available in this round's retained files.

Keep all old P/I sparsity, low/high metadata, zero fallback and original biased
terminal semantics. Dense cache still includes zero entries; sparse cache
contains only actual nonzero indices. Preparation is paid at batch1 as well
as batch8. First buy a bounded raw-payload getter/control measurement, then
complete-model cost only if one actual load or meaningful native work is gone.
Do not queue it merely because it uses a specialized array or a new name.
