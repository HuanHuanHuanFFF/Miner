# R17 structural frontier: two candidates and first discriminator

Status: source/interface investigation; no performance candidate, compiler run, CI or adoption. Baseline is exact 622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58. Current entry is this directory's status.json; accepted.json records scope. Tokens and cached input UNKNOWN.

## 1. Contiguous FloatArray storage, checked narrowing

The genuinely contiguous available representation is FloatArray of **Float64**, not Float32. Fresh exact-commit GitHub fetches are saved under upstream/: Lean commit 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b, FloatArray/Basic by Leonardo de Moura/Microsoft (Apache 2.0), Float/Float32 by Leonardo de Moura and Julia M. Himmel/Amazon (Apache 2.0). FloatArray has actual size/get/uget/push logical definitions. Pinned lean.h stores sizeof(double) elements and uget returns double directly. Its mk/data operations traverse and unbox/box every element, so runtime .data is not an innocuous projection.

Fresh Float32 source still declares Float32.toFloat and Float.toFloat32 opaque, with no defining model equation. This was independently rechecked, not inherited from an R13 label. A raw-word equality check on each actual encoded value is the available sound bridge; exact old f01-d2-checked-floatarray source 5be0735a... already implements it and its manifest points to old full gate 39663131701. That gate is not current-v2 performance evidence. R2-W04's single-pass checked prepare 98cef0f2... is an existing complete proof attempt, not a new discovery here.

Potential savings: per-element float boxes and pointer loads. Complete new costs: original ofBits decode, widen, narrow, toBits and raw comparison during preparation; 8-byte storage; one narrow per read; ownership/capacity check on each push; failed-prefix cleanup plus original fallback; raw inputs retained for NaN replay; full release. No change to arithmetic precision/order is allowed. SUM has no reuse and currently no preparation array, so this adds work there.

Smallest discriminator was exact pinned API/model audit. It closes the 'free legal contiguous Float32 array' premise negatively: FloatArray requires checked narrowing; ByteArray/Basic supplies UInt8 access, not a Float32 load. Byte packing followed by ofBits reintroduces the original conversion at every read. No full FloatArray revival is proposed without a measured current preparation/pointer bottleneck sufficient to pay these costs, or a new allowed semantic interface. This does not prove every checked FloatArray implementation slow.

## 2. Selected core probe: temporal scalar-field blocks

Different mechanism from R16 A4B2: pack **consecutive k positions** in each existing column group into one record of native Float32 fields. Preserve two or ten output accumulators and the exact sequential k recurrence. Do not create A4 panels, four-row tiles, wider independent accumulators, or numerical roundtrips. Baseline B2 already proves native fields are unboxed; this changes object granularity along k, not row/column width. Locally authored probe will be R17Temporal below the untouched baseline and is not third-party algorithm provenance.

For K=4, four old B2 records plus four pointer slots request 4*(8-byte header+8-byte payload+8-byte slot)=96 bytes; one B2K4 record plus one slot requests 8+32+8=48 bytes. Four old F10 records plus slots request224 bytes; one F40 temporal record plus slot176 bytes. These are runtime request-size models, not measured allocator bytes or time. Last incomplete block must execute only existing k positions: extra zero MACs are not assumed harmless. Preparing a full-length rounded-up block also performs extra reads/conversions unless explicitly guarded; the probe will avoid this.

Necessary complete costs: exactly original valid B decodes, record construction and pack-loop control, last-block branch, retained raw A bounds and decodes, same scalar MAC count, unchanged output finish/replay and release. The B2 hot ofBits call remains per k; its spill risk is **not removed** by temporal blocking. A generalized compressed A cache can remove old wide-path A boxes but adds preparation on B2 and is a separate dependency, not counted as free savings.

Proof interface: native-field projection equals the original read at k+j; four sequential updates equal four original loop unfoldings; partial block consumes exactly n%4 valid positions; then original finish/row Prefix proofs apply. No new floating arithmetic lemma is needed. Minimal model checks exact address and per-lane operation traces, including all tails, zero dimensions and odd columns. A small actual-core Lean fragment will be delivered; its Lean/codegen status remains NOT_RUN.

Stop/continue: continue this bounded core/interface probe because it distinguishes a real lower-object representation from FloatArray's opaque bridge. Do not queue a full gate solely on byte counts. First actual selected C must show one block record, direct native fields, no intermediate B2 records/field boxes and no accidental per-step materialization. Then full timed preparation/core/fallback/release must be measured by D if the observed opportunity merits it. If preparation is a small fraction, park the route.

## Overall value boundary

Completed B2 samples place all BMM at16.142%,20.023%,19.058% of whole. A10% whole reduction requires removal of61.95%,49.94%,52.47% of **all** BMM time; even all-BMM2x yields only8.071%,10.011%,9.529%. Local byte savings do not establish that much removable time. Current dynamic pack/allocator/pointer share UNKNOWN. Neither candidate presently has evidence of a10% whole gain. A major representation investment needs either measured dominant preparation/pointer cost across wide and thin paths, or a legal way to remove per-k input decoding without expensive preparation. The separate scalar numeric-roundtrip worker owns the latter arithmetic bridge; this worker does not duplicate it.

No current confirmation inputs/results were read. Only completed R15/R16 records and pinned source were used. All mutation is within this directory.
