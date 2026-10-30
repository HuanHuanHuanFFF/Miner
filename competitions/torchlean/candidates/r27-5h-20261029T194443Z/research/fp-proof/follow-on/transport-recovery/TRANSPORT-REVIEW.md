# Finite raw bits: the actual transport aperture is larger than52bits

Checked in the recovery starting2026-10-30T00:08:40Z. Common cutoff remains00:44:43Z. No localLean/native build, CI dispatch, newagent or toolmessage; no frozen batch9 inputs or native results were read. All new files are isolated here.

## Decision-changing finding

A52-bit limit is sufficient for a subnormal-only carrier, but it is not necessary for finite raw transport. For any unsigned wordp<2^60, the binary64 exponent is floor(p/2^52) mod2048<256. Thus every such word is finite and neverNaN. More generally the entire positive prefixp<0x7ff0000000000000 is finite. This follows from bit fields and does not rely on floating arithmetic or rounding.

Public23's original input-span<=15 gives aligned magnitudeM<2^39. LetC=2^39 andz=(-1)^inputSign*M. Then1<=C+z<2^40. With original sparse indexi<2^20, encodep=i*2^40+(C+z). It is below2^60; p>>40=i; and(p & (2^40-1))-C is exactlyz modulo2^64. Weight-sign negation therefore equals the originalQPD/QPa selection of2^62+/-M after subtracting2^62. This is a40-bit biased signed factor plus20-bit original index, with no new variable input shift perMAC.

This removes the span<=7 restriction required by the prior signed32+index20 proposal. It is a data-layout extension, not proof of a faster kernel. Both FloatArray and packedArrayNat can carry exactly the same60-bit word. The latter also remains an immediate smallNat on64-bit, so the packing benefit must not be attributed to FloatArray.

## Checks and conditions

check_aligned60.py freshly completed101020 cases:960 cases over all16 shifts and exact mantissa/index/sign endpoints,100000 fixed-seed synthetic aligned cases, and60 general39-bit endpoints. Every case checked the payload bound, exponent<=255, Python byte-level double roundtrip, index decoding, and UInt64 signed selection against the old centered cache formula. aligned60-model.json records the actual run interval and source hash. This is a finite synthetic model, not Lean, FloatArray runtime execution or a speed measurement.

The old span8 truncation witnessM=4294967040 now decodes exactly rather than-256. A separate negative control packs index1048575 for a dot of length1: the payload is finite but the index is invalid. Thus finite transport does not dischargeQPI membership or actual getter bounds. Preserve the original sparse eligibility, I9/QPI index<n proof, density and low/high metadata, zero flags, fallback and biased terminal semantics.

Aligned60Carrier.lean.inc is a small runtime draft for the codec plus same-payloadNat/Float prepare/load controls. It is NOT_COMPILED and NOT_QUEUED. Runtime Float prepare uses emptyWithCapacity/push; neither branch first constructs ArrayFloat. Index conversion and actual original input access remain to bind.

## Smaller actualLean proof interface

FinitePrefixTransportContractOnly.lean is a standalone ContractExact-only draft. Its scalar chain is prefix_exp_lt -> prefix_valid -> pinnedModel.pack_unpack_of_valid -> actualFloat.ofBits/toBits equality. It avoids the prior route through Dyadic existence, real semantics or an ExecFloat wrapper. payload60_finite and payload60_roundtrip specialize the actual positive finite prefix. The source also includes public fold/push construction, prepare_size, get! roundtrip, checkedNat get and USize uget load roots.

The pinned primary definitions support the reductions: Float.ofBits is ofModel(Model.ofBits), Model.ofBits is pack(unpack), Float.toBits is toModel.toBits, and Model.pack stores UInt64.ofBitVec(pack...). The exact pack_unpack_of_valid theorem is in the fixedFloatLib Native/Model/Representation file, not an assumed upstreamLean lemma. New elaboration is stillNOT_COMPILED; no accepted old root is inherited by the new source.

For prepare, .data/map/list are proof-only. The executable prepare is a fold of public FloatArray.push. FloatArray.get uses Nat+bound; uget uses USize+bound and its logical body is the sameArray element. The USize theorem accepts an existingUSize and actualtoNat bound, so it makes no claim that an arbitraryNat-toUSize conversion is lossless.

## Actual runtime cost frontier

Fresh pinnedLean4.34 runtime source object.cpp blob49213d7be079e11589f1efcfe880dba44622a6e7 shows:

- ofBits uses std::bit_cast and tests isnan, replacing NaN.
- toBits tests isnan and returns canonical0x7ff8000000000000, otherwise bit_cast.
- FloatArray.push directly stores a double after capacity/exclusivity checks.
- FloatArray.data allocates a genericArray and boxes everyFloat; do not execute it in preparation or a getter.
- GenericArray destruction scans every element through dec; ScalarArray destruction directly deallocates. This is one possible FloatArray advantage over immediateNat, but its full-call contribution isUNKNOWN.

Pinnedlean.h blob910ecae72a7d1c149d4ccc8111ee438c8b4551dd shows UInt64.toNat at<2^63 returns lean_box, while UInt64.ofNat has a scalar check and unbox branch. ArrayNat and FloatArray each use one8-byte payload slot on64-bit. GenericUInt64Array heap boxing is an inappropriate control for this domain.

Existing same-version oldASM contains a direct lean_float_to_bits call, so a free integer-load assumption is unjustified. The new codec's emittedC/ASM isUNKNOWN. An external call/NaN test can outweigh a tag shift; destructor savings or removal of the index dependency may still matter. Dense-only remains paused. Retain indexed60 as a conditional packing direction; first compare the two exact same-payload controls with preparation/access/destruction included if a later authorized window allocates a bounded test. No newCI is requested now.

## Evidence boundary

Pinned source/API facts: source-reviewed. Codec mathematics: paper derivation plus finite model. All newLean roots:NOT_COMPILED. Actual newFloatArray execution/native cost:UNKNOWN. Newkernel/all12 gate:NOT_IMPLEMENTED. Formal competitive adoption:UNKNOWN. Prior accepted checker roots and the priorFP23 negative cost are preserved in predecessor-HANDOFF.md and predecessor-status.json.

