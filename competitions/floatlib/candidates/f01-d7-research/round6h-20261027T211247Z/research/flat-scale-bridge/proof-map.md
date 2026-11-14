# Flat scale lookup: smallest proof chain before selector costs

Runtime is D's exact `development-flat-scale/FlatScale.lean.inc`, **82ebf77c / 10768 B**. It has **four top-level records of 128 Float32 scalar fields**; it is not an Array of F4 records. No runtime edit, 512-case proof, full candidate or CI is produced here.

## Dependency chain and exact missing premise

| Layer | Real input/output proposition | Status here |
|---|---|---|
| Existing index bound | `R2W01b.tableIndex_toNat_lt u`: `(u>>>23).toNat<512` | Already in retained B2; reused. |
| Group/slot split | group=`j>>>7`, slot=`j&&127`; group<4, slot<128, `128*group+slot=j` in Nat | New small proofs in `FlatScaleBridge.lean.inc`, **NOT_RUN**. |
| Block selector | For each g=0..3 and s<128, `pick block_g s = seed(ofNat(128*g+s))` | **Four explicit unproved premises**. Only five small discriminator leaves are written separately. |
| New lookup→old lookup | `lookup_eq_scaleAt_of_blocks`: the four premises imply `lookup u=R2W01b.scaleAt u` for every UInt32 u | Conditional bridge, **NOT_RUN**. Group bound justifies the final else=block3; slot bound excludes pick's default. |
| New converter→old | `convert_eq_old`: universal lookup equality implies `convert u=R2W01b.convert u` | Conditional rewrite, **NOT_RUN**. Old fastOK/mantissa and fallback unchanged. |
| Scalar transport | `add_eq_old`, `nativeMul_eq_old`, `mul_eq_old`, then three `*_spec_of_lookup` | Conditional rewrites to actual B2 endpoints/specs, **NOT_RUN**. No new arithmetic or NaN law. |

The old exact lookup interface is:

```lean
R2W01b.scaleAt_eq (u : UInt32) :
  R2W01b.scaleAt u = Float32.ofBits (R2W01b.scaleBits (R2W01b.tableIndex u))
```

This avoids proving numeric equality of the 512 Float32 values. The new records contain precisely the same `seed j := Float32.ofBits (scaleBits j)`, so the missing work is record selection, not floating arithmetic. In particular do not expand `seed`, `scaleBits`, native rounding, or real powers while proving field access.

The lookup theorem is stronger than needed by fastOK because it covers all raw words, including indices for invalid/nonfinite/fallback exponents. It does not change which conversions use the fast path, nor claim arbitrary raw NaN roundtrip equality. The new add/nativeMul/mul branches and original `ScalarNaN`/`LowScale` fallback follow by the exact old converter equality.

## A smaller finite helper route

After a selector-cost signal, prefer one proof-only constructor helper:

```lean
blockOfFn : (Fin 128 → Float32) → Block
pick_blockOfFn (f : Fin 128 → Float32) (i : Fin 128) :
  pick (blockOfFn f) i.val = f i
```

The helper's constructor has128 fields `f0..f127`. Prove the projection theorem once by128 bounded Nat cases, each `rfl`. Then the four existing blocks are definitionally equal to `blockOfFn (fun i => seed(ofNat(offset+i.val)))` for offsets0,128,256,384. Four constructor `rfl` equalities plus the generic projection theorem close all512 entries without four independent 128-case proofs.

No extra import or axiom is required: existing `omega` can establish a single-variable bounded-case disjunction, existing `rcases` splits it, and ordinary `rfl` checks projections. Do not use native_decide/native bitvector axioms. An available finite-case tactic could shorten source, but the explicit disjunction route uses only tactics already present in B2.

`SmallPickDiscriminator.lean.inc` writes only block0 slots0..3 and block3 slot127. These first five leaves test actual record-projection and UInt32 literal normalization without a large proof. **They have not been compiled.** If even these have a parser/elaboration issue, retain that typed goal before expanding anything.

## Source/time limits and cost boundary

The generic128-field helper and bounded projection are expected to need only several KB of source, but exact final bytes, elaboration heartbeats and proof-term memory are **UNKNOWN until generated/compiled**. Nested Nat matches and128-field constructor projection can still be expensive. Keep the helper split from final public transport, retain default limits for the first small discriminator, and collect a real failure before changing limits or proof shape. No blanket simplifier over all records/Float32 models is justified.

`source-shape-check.json` binds the literal record ranges, all128 pick branches and all512 integer group/slot decompositions. It is a static/finite check, not the missing universal Lean proof. It also reports the exact arithmetic sum of B2+runtime+current fragments; that is not a final assembled package size, and says nothing about combining with a new F8 candidate.

The old array lookup and the new record selector still need actual selected-caller comparison. Removing one boxed-table indirection can be outweighed by the128-way selector, group dispatch, field addressing, constant initialization or code size. The original table may remain live through other B2 operations; do not assume its memory/init disappears. D owns selector C/ASM and complete cost, including actual startup/steady boundaries of the fixed protocol. Prior ArrayF4 NO-GO and cross-width opaque routes are not reopened.
