# Round 3 uniform dual hash compression experiment

Prepared 2026-10-06 UTC. Two candidates were generated from the publicly disclosed submission 385 implementation, with its public entrypoint replaced so every input takes one uniform dual-hash engine. This is research for the main thread's CI; the changed source/proof pairs are **UNVERIFIED**.

## Actual reference entry and exclusion boundary

**VERIFIED by source inspection:** the reference's top `mA` comment does not describe the effective entrypoint. `parse.rs:315` has special cases for lengths 28000 and 12000, then calls `bulk_parse` at line 285. `route` at line 257 dispatches on exact lengths such as 800000, 150000, 900000, and 1300000. The final `r109_row0` through `r109_row22` wrappers select the actual FX0, FV, dual-hash, one-table, small, binary, and replay engines.

The untouched reference is preserved for provenance and is not treated as a general content-adaptive baseline. The candidate entrypoint is exactly:

```rust
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    r109_row1(input, out)
}
```

All inputs, including empty and tiny inputs, take the same `r109_row1` engine. The old routing functions remain in the source only to preserve the original proof declarations, but are unreachable from `parse`. **VERIFIED:** the generator's direct-call closure audit found neither `route`, `bulk_parse`, `format_id`, nor another `r109_row` in the candidate entrypoint's closure. The audit is a static direct-call check, not a runtime trace or official extraction result. No filename, exact file length, content signature, or adaptive class branch was added.

The reference and attribution are in `references/round3-public-385/PROVENANCE.md`, retrieved from the official source endpoint at 2026-10-06 15:21:27.038 UTC. The parser and proof were written by that submission's miner. This project's changes are the uniform entry, search parameters, and the dense3 short-key ablation.

## Candidate mechanism

The active engine is `o_a_main_part` at reference line 2119. It allocates one 131072-entry u32 table, split into independent 65536-entry short- and eight-byte-key regions. The software-pipelined scan finds a recent candidate from each region; it prefers the eight-byte match when that key agrees, otherwise the short match. Match emission rechecks bounds and bytes in `o_a_verified`/`o_a_emit_step`. It is not an arbitrary-depth chain search, a dynamic program, or an exact bit-cost parser.

Both candidates change `r109_row1` from `<10,256,8,5,32>` to `o_a_main_part::<258,258,1,63,258>` and change `O_A_LZN` from 1 to 4:

- `IH=258`: record the whole emitted match interior in both dictionaries, subject to the original input-end guard.
- `IT=258, TS=1`: dense tail insertion parameters; the head already covers an ordinary match, so this generally adds no separate tail pass.
- `ACC=63`: the literal scanner stays at step 1 on ordinary inputs; the original bounded scanner remains intact.
- `LZT=258`: consider a one-byte lazy successor for matches shorter than 258.
- `O_A_LZN=4`: after a lazy win, permit up to four further winning successor steps.

| Candidate | Short key | Minimum match | Length 3 distance cap |
| --- | ---: | ---: | ---: |
| `round3-size385-dense4` | 4 bytes | 4 | Not applicable |
| `round3-size385-dense3` | 3 bytes | 3 | 1024 |

Dense3 changes `O_A_HM4` to `0x4A7C150000000000`, `O_A_MM4` to 16777215, `O_A_MINL` to 3, and `O_A_MAX3` to 1024. Its eight-byte dictionary is unchanged. The distance cap was chosen before measurement as a general guard against length-3 matches with expensive distance codes, not as a measured optimum. The two variants isolate whether a three-byte short table recovers useful local repeats while the separate long table protects longer repeats from short-key collisions.

**INFERRED:** denser insertion and broader lazy search could reduce text output at considerable cost. The uniform engine also removes the reference's special handling for DNA, high-entropy inputs, and tiny block alphabets; aggregate size or time can worsen substantially. The large table is allocated even for tiny inputs. These are deliberate compression-boundary experiments, not asserted improvements over 385 or probe3.

## Input bounds and proof reuse

**VERIFIED by source inspection:** `o_a_ld8` returns zero when `n < 8` or the requested eight-byte load would exceed the input. `o_a_eval` and both lazy evaluators return zero when `n < 16` or `p > n-16`. The `o_a_scan` loop has the same `n >= 16` and end-position guard. Literal emission handles remaining bytes; every emitted match is checked for length 3..258, distance 1..32768, available history, available input, and byte equality. These checks are unchanged.

Both `Parse.lean` files are the complete 346357-byte original, below the 524288-byte per-file intake cap. **VERIFIED from the proof:** `EO.EA.main_part_spec` quantifies over all five const-generic parameters; `r109_row1_spec` instantiates this theorem with inferred parameters. The final `parse_spec` unfolds `slot.parse` and uses locally registered step rules, including `r109_row1_spec`. The lazy-more loop uses `slot.O_A_LZN.val - iterations` as its termination measure. Search helper specifications generally establish totality; the fixed emitter carries the decode invariant.

**INFERRED:** these shapes support keeping the complete proof unchanged after the entry and parameter changes. **UNKNOWN:** actual Aeneas extraction shape, proof automation behavior, the official obligation, axioms, and complete gate for each candidate. A copied proof is not a new acceptance receipt. No local Rust, Linux toolchain, Lean, or benchmark was run.

## Exact files and checks

Base Rust SHA256: `56b92f95a93fd8662c20dd26934fed065f812a685610d09f58d01148cfdb367f`.

Both proof SHA256: `db97b9e2c525995a63e31f6b720ff0f234b4acd2a5822663f026848dd0864d62`.

| Candidate | Rust bytes | Rust SHA256 |
| --- | ---: | --- |
| `round3-size385-dense4` | 184648 | `2d67b0d51e46a0b6e01fb8246f13ef330f8d00709042a45e989b0d4e37dade2b` |
| `round3-size385-dense3` | 184645 | `0e02459588dbcf5b5b2e1fbae28cd18e7a07be60ad7f3f127e0de56c38d8f842` |

`scripts/make-round3-size385.py` pins the original two hashes, generates only these two directories, records the direct-call closure and parameters in each `manifest.json`, and supports a read-only `--check` against exact expected bytes.

**VERIFIED:** generation and `--check` both exited 0; direct diffs show only the entrypoint, row1 const generics, `O_A_LZN`, and the four dense3 short-key constants changed. The original proof is copied byte-for-byte. The reference files were not modified.

The first falsification is a public corpus paired benchmark with dual-decoder round trip, retaining per-file size, token/output hashes, and raw timing. Multiply observed public time by 1.014402891250616 and public size by 1.0070277985275755, then compare against the full frontier in `frontier-targets.json`; this is only the requested #427 empirical proxy. A uniform variant dominated there is not promoted just because it compresses one text input well. Promising exact files still require the unchanged official gate at revision `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`, then another paired order/runner check if the timing margin is small.

Private stage2, online admission, actual Pareto position, and rewards remain **UNKNOWN**. No CI, commit, push, submission, registration, wallet action, or additional agent was initiated by this subtask.
