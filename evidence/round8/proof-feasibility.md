# Round 8: existing-candidate distance-cost proof boundary

Reviewed 2026-10-08 against local HEAD `782cd10b830765bc971c04a0bb8f38280afd1a99`.
Scope: source/proof review and a proof-generation draft. No Lean execution, CI,
commit, push, wallet operation, or formal submission was performed by this review.

## Evidence identity

- **VERIFIED**: `references/round7-public-361/PROVENANCE.json` identifies public
  submission #361. The local reference files match its SHA-256 values:
  `parse.rs` = `f426f7cec777ef2ca74616eb62205d54ae0bf6938799835a1fe6024ed59b5c45`;
  `Parse.lean` = `f815bcb880d9da3c18d8fcb768f66ea2222a6348187646eb027c1cb020bb2fb0`.
- **VERIFIED**: the review used the current reference files, rather than treating
  the earlier probe2 search proof as interchangeable with #361.
- **UNKNOWN**: a new Round 8 Rust/proof pair passes official extraction,
  `LZ77.Obligation`, axiom checks, and public round trip. Source inspection and a
  generated proof draft do not establish those results.

## Smallest useful experiment

**INFERRED**: keep `walk`, `walk_t`, their signatures, the 16-slot candidate array,
the search budgets, continuation, and skip logic unchanged. Change only forward
relaxation in `rc_seq`:

| Variant | Forward relaxation | Proof impact | Performance question |
|---|---|---|---|
| A | Change the call at Rust line 1434 from `lo` to `3`; retain loop state and `lo = len + 1` | Existing theorem shape can be reused as a draft | Repeated lengths cost extra work; isolates whether omitted overlap has value |
| B | For the current interval `lo..len`, compare the current candidate with the last candidate by `dcc[dsym(dtab,dist)%32]`, use the cheaper distance and its pack | New expression branches inside a True-invariant loop; no walker proof change | Adds a bounded comparison without increasing relaxed lengths |
| C | For the current interval, choose the cheapest distance among candidates `k..min(nc,16)` | Add a totality-only helper theorem; preserve `rc_seq` signature and loop state | Bounded suffix scanning adds work; strongest distance choice among retained candidates |

**VERIFIED** source facts supporting this boundary:

- Rust `walk` lines 959–998 retains only increasing match lengths. Rust `probe`
  lines 933–956 returns zero unless a node beats its supplied `best`.
- Rust `walk_t` lines 1309–1353 uses a tail test for the same increasing-length
  policy. Rust `dp_parse` lines 1530–1557 combines the three-byte head, the short
  chain, the long chain, and a longer continuation.
- Rust `rc_seq` lines 1426–1435 partitions lengths: a current candidate receives
  the interval following the previous candidate through its own length, and the
  following candidate starts at `len + 1`.
- Rust lines 1436–1443 perform backward extension for the *current* candidate.
  B/C must retain that candidate's `dd`, `ds`, distance cost, and pack for these
  calls; the selected suffix candidate is used only in forward relaxation.

**INFERRED**: with the unchanged increasing-length candidate list, each suffix
candidate is long enough to cover the current interval. Its distance cost is the
only candidate-specific cost in that forward interval. Choosing the cheapest
suffix distance therefore weakly improves the existing local forward relaxation
under the current cost table, without increasing the number of relaxed lengths.
This does not imply monotone compressed output: changed plans alter counts,
later costs, chunk decisions, and the final encoder's actual code lengths.

## Precise Lean dependencies

| Declaration in `references/round7-public-361/Parse.lean` | Lines | What it actually proves |
|---|---:|---|
| `probe_spec` | 277–285 | Result is at most `cap`; nonzero result is strictly greater than supplied `best` |
| `walk_loop_spec`, `walk_spec` | 288–311 | Termination/safety, `best` is monotone and at most `cap` |
| `tailw_spec` | 1018–1025 | Totality of tail-word computation |
| `walk_t_loop_spec`, `walk_t_spec` | 1029–1053 | Same monotone/capped `best` postcondition; no candidate-order or match-correctness postcondition |
| `relax_seq_loop_spec`, `relax_seq_spec` | 1086–1103 | True invariant; loop measure `512 - l` |
| `rc_seq_loop_spec`, `rc_seq_spec` | 1106–1132 | True invariant; loop measure `16 - k` |
| `dp_parse_loop_spec` | 1235–1578 | Explicit binds call `walk_spec` at 1372, `walk_t_spec` at 1396, and `rc_seq_spec` at 1519 |
| `dp_parse_spec` | 1580–1590 | Totality of planning; result postcondition is True |
| `emit_loop_spec`, `emit_spec` | 6213–6278 | Rechecks planned matches and proves decode for arbitrary plan |
| `parse_spec` | 8236–8246 | Final `LZ77.Valid` result |

**VERIFIED**: `rc_seq_loop_spec` unfolds its extracted body, calls `step*`, derives
`dp_shr9 c`, and then binds the backward branch with a True postcondition. It
does not consume a theorem about candidate ordering or cost optimality. A/B are
therefore expression-level changes in an existing safety proof, although exact
extracted temporary names and branches can still require adaptation.

**INFERRED**: C's helper needs only a totality theorem. With fixed-size arrays,
explicit modulo indexing, and `while k < nc && k < 16`, its loop can use measure
`16 - k` and invariant True. Registering its theorem with `@[local step]` should
allow the existing `rc_seq_loop_spec` `step*` to consume the helper call. The exact
helper loop interface must be checked against fresh extraction before claiming
the drafted proof matches it.

## Draft generator and local checks

`scripts/make-round8-proof.py` exposes `adapt(proof: str, label: str) -> str`.
It preserves the full variant, inserts one `rc_pick_top_spec` lemma for top, and
inserts `rc_pick_suffix_loop_spec` plus `rc_pick_suffix_spec` for suffix. The
original `rc_seq_loop_spec` remains unchanged in this draft.

**INFERRED**: suffix extraction has interface
`slot.rc_pick_suffix_loop cands nc dtab dcc chosen price k` and mutable state
`(chosen, price, k)`. This is inferred from the exact Round 8 Rust helper and the
existing Round 7 extracted-loop convention, rather than observed Round 8 output.

**VERIFIED**, local Python check on 2026-10-08: syntax parsing, repeat adaptation
idempotence, unique proof declaration anchors, removal of inserted helper text
restoring the reference proof, and full-variant byte identity all passed.

| Label | UTF-8 bytes | Generated proof SHA-256 |
|---|---:|---|
| full | 404167 | `f815bcb880d9da3c18d8fcb768f66ea2222a6348187646eb027c1cb020bb2fb0` |
| top | 404514 | `db90661d955ff77cdc33f9bd939c8c260435a179ae235eef75526cbc5c1a33a4` |
| suffix | 405054 | `2363fd863754bad50e62f9734ec32ebbb80e0f425d0e3989f0ab2dfd6659f7a7` |

The table uses the reference's original newline bytes. **UNKNOWN**: helper
signatures agree with fresh Round 8 extraction, Lean compilation succeeds, the
official obligation and axiom gate pass, or any candidate improves performance.

## Higher-risk changes to defer from this experiment

- **VERIFIED**: appending shorter matches while leaving `rc_seq` unchanged omits
  their forward interval because `lo` already exceeded their length.
- **VERIFIED**: Rust `dp_parse` lines 1563–1566 selects the last candidate for
  continuation, while lines 1571–1579 use its packed token with `best` for a
  direct skip. `best` and the last candidate must remain consistent.
- **INFERRED**: changing the probe threshold to retain short matches also needs
  monotone `best = max(best,l)`, a compatible tail threshold, candidate ordering
  or full-range relaxation, and protection of the last/longest convention. Adding
  cost-table arguments to walkers changes explicit Lean bind signatures.
- **VERIFIED**: `probe_spec` is also consumed by `d_walk_loop_spec` at Lean line
  3029 and by engine D's three-byte head at line 3312. Changing `probe`'s contract
  creates a wider proof surface than changing its DP call sites.

## Completion criterion

Before any acceptance claim, verify the exact emitted Rust/proof hashes through
fresh official extraction, the original obligation, the unchanged axiom
whitelist, and public round trip. Evaluate performance with paired #361 at fixed
inputs and runner identity. Public gate, paired performance, private stage2,
online admission, and rewards remain separate outcomes.
