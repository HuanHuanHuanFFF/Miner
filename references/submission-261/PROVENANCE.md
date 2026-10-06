# Public reference 261

`parse.rs` and `Parse.lean` are unmodified source downloaded from the official
[published source endpoint](https://conjectures.io/v1/competitions/deflate/submissions/261/source)
on 2026-10-06. These files were written by that submission's miner, not by this project.
They are a development control, not our original improvement or a current frontier entry.

Snapshot 22580: time 0.45899890911998886, size 36.595691428214636%; off the frontier.
Official scores use both stage1 and held-out stage2. Our CI can measure only public stage1.

The two candidates reuse its proof and change only the following plain constants:

- `hash-wide`: HB 15 → 16, HN 32768 → 65536, HS 4096 → 8192. One logical experiment: larger hash head tables.
- `probe2`: T_DEPTH, P_DEPTH and S_DEPTH 1 → 2. One logical experiment: two probes for text/prose/structured text.

The reference proof describes these table sizes and depths as free parameters.
This description is a hypothesis until the official gate checks each modified source.
