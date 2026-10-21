# Packed two-slot bucket feasibility

Read-only study, 2026-10-06 15:43 UTC. No candidate, generator, official source, wallet, or workflow was changed. This document describes an unimplemented design.

## Decision

**INFERRED**: a packed `u64` bucket is feasible and can retain the existing correctness-proof architecture. It cannot reuse the entire existing loop proof byte-for-byte because the head array element type changes from `U32` to `U64`. It does not reduce total zero-initialized bytes at a fixed bucket count. Its plausible benefit is adjacent slots, fewer load/store instructions and addresses, and potentially fewer cache-line fetches per cold/random probe. There is no current machine-code or paired-time evidence establishing that benefit, let alone a 2%–3% whole-compression gain.

The recommended next trigger is a positive paired result for `bucket2` followed by a controlled same-count SoA/AoS comparison. Do not implement packed storage by default during the current remaining proof/measurement window.

## Observed source and memory accounting

**VERIFIED (source inspection)**: current `bucket2` uses `head: [u32; H]` and `prev: [u32; W]`. Both reads are keyed by the same hash `a`, with the second indexed by `a % W`. Active dispatches use `H=W=32768`. `bucket_find` never reads its `_prev` argument; it constructs a one-entry virtual chain from the captured second position and reuses the original verified `find`/`walk`.

| Layout at 32768 buckets | Initialized table payload | Candidate read/store payload |
|---|---:|---:|
| Current two `u32` arrays | 262144 bytes | two 4-byte loads and two 4-byte stores |
| Packed `u64` array | 262144 bytes | one 8-byte load and one 8-byte store |

The number of allocated arrays and address calculations drops; the storage and total zeroing volume do not. A compiler may combine or vectorize both current clears. **UNKNOWN**: current machine code, emitted load/store counts, runner cache sizes, hit rates, clearing bottleneck, and measured speed effect. For cold independent hash accesses, a pair in one naturally aligned `u64` is contained in one cache line, whereas the two current arrays can require two lines. These are conditional layout properties, not a measured cache-miss reduction; the two SoA misses can overlap, and hot-table behavior may show little gain.

The 16K/8K footprint candidates genuinely reduce bytes cleared; packing at those same counts would again preserve their byte volume and change only layout/access pattern. A pack-only experiment should retain hash bits and bucket count so that layout can be attributed separately from collision changes.

## Minimal Rust design

Keep the two-value insertion result and the dummy `prev` parameter to retain the extracted state/tuple shape. Instantiate `W=1` in all three packed bucket dispatches so that the dummy table consumes four bytes. It is not read or written by insertion; `bucket_find` already ignores it. Keeping an unused full-size `prev` would erase the proposed layout benefit by retaining extra clearing/storage.

The proposed insertion body is:

```rust
pub fn bucket_insert<const H: usize, const W: usize>(
    s: &[u8], head: &mut [u64; H], _prev: &mut [u32; W],
    i: usize, mask: u32,
) -> (usize, usize) {
    let k = (be4(s, i) & mask) as u64;
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - HB)) as usize % H;
    let pair = head[a];
    let old = pair as u32;
    let older = (pair >> 32) as u32;
    let now = i as u32;
    head[a] = (old as u64).wrapping_mul(4294967296)
        .wrapping_add(now as u64);
    (old as usize, older as usize)
}
```

`bucket_run` changes only its head initialization to `[0u64; H]`, and its existing bucket dispatches become `bucket_run::<HN, 1>`. The captured pair, `bucket_find`, `find`, `walk`, and the engine control-flow remain unchanged. All ordinary/tiny paths retain their current structures. This sketch was not compiled or extracted.

Use multiplication/addition by powers of two rather than OR in the proof-oriented source: `old * 2^32 + now` is the same disjoint-half packing and permits a short modular-arithmetic proof. The eventual compiler's strength reduction and equivalence to a shift/OR sequence remain **UNKNOWN** until inspected.

**INFERRED (semantics)**: low 32 bits represent newest position and high 32 bits represent second-newest position. With equal original `H/W`, unchanged hash and insertion schedule, this implements the same two captured `u32` positions. It preserves the original truncation of positions to `u32`; adding a new `i ≤ 2^32−1` restriction is unnecessary and would weaken the original input quantifiers. The generic old implementation aliases second slots when `H≠W`, whereas a packed per-bucket table does not; token equivalence should be scoped to the actual equal-size old dispatches. Fresh correctness does not require proving optimality or token equivalence.

## Exact proof changes

The regular engine's `Submission.HeadBound` must stay untouched. Inside `namespace Bucket2`, introduce a local `HeadBound` for `Array Std.U64 N`, which shadows the regular one:

```lean
def HeadBound {N : Std.Usize} (head : Array Std.U64 N) (B : Nat) : Prop :=
  ∀ j : Nat, j < head.val.length →
    (head.val[j]!).val % (2 ^ 32) ≤ B
```

Bounding the entire packed `u64` by `B` is wrong: its older position is multiplied by `2^32`. Only the low half is needed to show the initial walk candidate is at most the current parse position. The existing verified walk checks `nx < c` before following its virtual link, so no new upper bound on the high half is needed for correctness.

Add local `HeadBound.mono`, `init`, `set`, `get`, and `update` analogues:

- `mono` is unchanged mathematics.
- `init` reduces every zero entry modulo `2^32` to zero.
- `set` requires `v.val % 2^32 ≤ B` and preserves all other entries; its list/array part is identical to the current proof.
- `get` derives `(UScalar.cast .U32 pair).val ≤ B` from the low-half invariant and `UScalar.cast_val_eq`.
- `update` uses a new low-half packing lemma, then the existing fact `i.val % 2^32 ≤ i.val ≤ B`.

The core new mathematical lemma is:

```text
low32(pack(old32, cast32(i))) = i.val % 2^32
```

For the wrapping multiply/add sketch this follows from casting/wrapping value equations, divisibility of `2^64` by `2^32`, and `(old.val * 2^32 + now.val) % 2^32 = now.val`. It should not require a new axiom, bitwise OR theorem, or any matcher/decode lemma. Its extraction-level Lean statement and successful proof are **UNKNOWN** until a temporary runner is used.

`Bucket2.insert_spec` changes the head parameter type to `Array Std.U64 H` but keeps its result shape and postcondition:

```text
returned newest position ≤ B ∧ HeadBound returned packed table B
```

Its present three-line conclusion (`HeadBound.get`, `cast_usize_le`, `HeadBound.update`) can retain that structure after the local low-half lemmas. The extra cast/shift/pack statements need extraction-aware `step` specifications. The older-position extraction only needs totality, because its value is untrusted search data. The existing `cast_usize_le` from a `U32` can still bound the returned newest `usize`.

Within the duplicated `Bucket2` loop proofs, mechanically change only head array element annotations from `Std.U32` to `Std.U64`, including the `{N}` arrays in `LazyInv` and `MainInv`; `prev` stays `U32`. Their mathematical `Dec`, `MatchAt`, insertion-cursor bounds, decreasing measures, tuple projections, and `HeadBound.mono` applications can stay structurally the same. Backward-fold/emission proofs and `Bucket2.find_spec` are unchanged. The original tuple-destructuring repairs must be retained because insertion still returns a pair.

This is reuse of proof structure, not exact proof bytes or a certified automatic replacement. Removing the dummy `prev` instead would change loop state shapes and tuple projections, requiring broader proof edits. A namespace-local packed invariant avoids generalizing the regular `HeadBound` and risking every existing regular-engine lemma.

## Expected blockers and falsifiable next test

**INFERRED**: the difficult new proof work is narrow but real: (1) formalize low-half packing/cast equations against Aeneas's exact extracted definitions; (2) make `step` carry that bound through `bucket_insert`; (3) check that replacing the head element type and keeping the dummy mutation parameter preserves the currently repaired loop tuple shapes. The algorithm/decode proof does not need a new invariant beyond the low-half head bound. The historical tuple failures are evidence that extraction details can block otherwise small structural changes.

A future authorized experiment should first inspect the current same-count SoA machine code for actual paired loads/stores and clearing, then compare a Rust-only packed diagnostic for finite token equivalence over stage1 plus existing synthetic boundaries. If there is a paired performance signal, run fresh official extraction/Lean/axiom/round-trip checks on an isolated candidate. A diagnostic speed signal is not a gate or a formal equivalence proof. No implementation was performed in this study.

Source anchors: `candidates/bucket2/parse.rs` at `bucket_insert`, `bucket_find`, `bucket_run`, and the three parse dispatches; `candidates/bucket2/Parse.lean` at regular `HeadBound` and the `Bucket2` insert/lazy/insert-loop/main-loop proofs. Inspected base source SHA256: `38bb6c7d4df093e6cedbad9651d5ee4377d75fa995106d70dce5c08585cac4db`; proof SHA256: `421c58d4695b80d25b3b17eb53d065fa5764185352491f4c1b17d32fff26a7c1`.
